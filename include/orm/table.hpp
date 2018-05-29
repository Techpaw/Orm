#pragma once

#include <vector>
#include <memory>
#include <orm/exceptions.hpp>
#include <orm/statements/all.hpp>

namespace Orm {
  template<typename TableClass>
  class Table {
  public:
    explicit Table(std::string alias = "") :
      alias{std::move(alias)},
      rootStatement{}
    {}

    template<typename T>
    void addField(std::string name, std::string defaultValue = "") {
      if (std::is_same<T, bool>::value) {
        this->fields[name] = std::make_shared<Field>(name, Type::BOOLEAN, defaultValue);
      } else if (std::is_same<T, int>::value) {
        this->fields[name] = std::make_shared<Field>(name, Type::INTEGER, defaultValue);
      } else if (std::is_same<T, std::string>::value) {
        this->fields[name] = std::make_shared<Field>(name, Type::STRING, defaultValue);
      } else {
        throw Exceptions::InvalidFieldType();
      }
    }

    Statement operator[](std::string name) {
      auto newStatement = Statement();
      newStatement.addChild<FieldStatement>(FieldStatement(this->getNameOrAlias(), name));
      return newStatement;
    }

    Statement operator()(Statement statement) {
      auto newStatement = Statement();
      auto groupStatement = GroupStatement(std::move(statement));
      newStatement.addChild(groupStatement);
      return newStatement;
    }

    Statement aggregate(std::string name, std::vector<Statement> args = {}) {
      auto newStatement = Statement();
      auto aggregateStatement = AggregateFunctionStatement(std::move(name), std::move(args));
      newStatement.addChild(aggregateStatement);
      return newStatement;
    }

    Statement literal(std::string value) {
      std::stringstream stream;
      auto newStatement = Statement();
      stream << "'" << value << "'";
      auto literalStatement = LiteralStatement(stream.str());
      newStatement.addChild(literalStatement);
      return newStatement;
    }

    Statement literal(int value) {
      auto newStatement = Statement();
      auto literalStatement = LiteralStatement(std::to_string(value));
      newStatement.addChild(literalStatement);
      return newStatement;
    }

    Statement literal(double value) {
      auto newStatement = Statement();
      auto literalStatement = LiteralStatement(std::to_string(value));
      newStatement.addChild(literalStatement);
      return newStatement;
    }

    Statement literal(bool value) {
      auto newStatement = Statement();
      auto literalStatement = LiteralStatement(value ? "TRUE" : "FALSE");
      newStatement.addChild(literalStatement);
      return newStatement;
    }

    Statement function(std::string name, std::vector<Statement> args = {}) {
      auto newStatement = Statement();
      auto functionStatement = FunctionStatement(std::move(name), std::move(args));
      newStatement.addChild(functionStatement);
      return newStatement;
    }

    CaseStatement cse(Statement statement) {
      return CaseStatement(std::move(statement));
    }

    TableClass& select(std::vector<Statement> args = {}) {
      auto selectStatement = SelectStatement(std::move(args), this->getName(), this->getAlias());
      this->rootStatement.addChild(selectStatement);
      return this->instance();
    }

    TableClass& where(Statement statement) {
      auto whereStatement = WhereStatement(std::move(statement));
      this->rootStatement.addChild(whereStatement);
      return this->instance();
    }

    TableClass& innerJoin(Table& table) {
      auto joinStatement = JoinStatement(JoinType::INNER, table.getName(), table.getAlias());
      this->rootStatement.addChild(joinStatement);
      return this->instance();
    }

    TableClass& leftJoin() {
      auto joinStatement = JoinStatement(JoinType::LEFT, this->getName(), this->getAlias());
      this->rootStatement.addChild(joinStatement);
      return this->instance();
    }

    TableClass& on(Statement statement) {
      auto onStatement = OnStatement(std::move(statement));
      this->rootStatement.addChild(onStatement);
      return this->instance();
    }

    TableClass& order(std::vector<Statement> args, OrderType orderType = OrderType::ASC) {
      auto orderStatement = OrderStatement(std::move(args), orderType);
      this->rootStatement.addChild(orderStatement);
      return this->instance();
    }

    TableClass& group(std::vector<Statement> args) {
      auto groupByStatement = GroupByStatement(std::move(args));
      this->rootStatement.addChild(groupByStatement);
      return this->instance();
    }

    TableClass& limit(Statement statement) {
      auto limitStatement = LimitStatement(std::move(statement));
      this->rootStatement.addChild(limitStatement);
      return this->instance();
    }

    TableClass& offset(Statement statement) {
      auto offsetStatement = OffsetStatement(std::move(statement));
      this->rootStatement.addChild(offsetStatement);
      return this->instance();
    }

    TableClass& update(std::vector<Statement> args) {
      auto updateStatement = UpdateStatement(std::move(args), this->getName(), this->getAlias());
      this->rootStatement.addChild(updateStatement);
      return this->instance();
    }

    TableClass& insert(std::vector<Statement> fields, std::vector<Statement> values) {
      auto insertStatement = InsertStatement(std::move(fields), std::move(values), this->getName());
      this->rootStatement.addChild(insertStatement);
      return this->instance();
    }

    std::string toSql() {
      return this->rootStatement.toSql();
    }

    std::string getNameOrAlias() {
      if (!this->alias.empty()) {
        return this->alias;
      }

      return this->getName();
    }

    std::string getAlias() {
      return this->alias;
    }

    std::shared_ptr<Field>& f(std::string name) {
      return this->fields[name];
    }

    template <typename T>
    T v(std::string name) {
      return this->f(name)->template getValue<T>();
    }

    TableClass& create() {
      auto it = this->fields.begin();
      std::vector<Statement> fields;
      std::vector<Statement> values;

      for (; it != this->fields.end(); ++it) {
        if ((*it).second->getName() == this->getId() ||
            (*it).second->template getValue<std::string>().empty()) {
          continue;
        }

        fields.push_back(this->operator[]((*it).second->getName()));
        values.push_back(this->literal((*it).second->template getValue<std::string>()));
      }

      this->rootStatement.clear();
      auto xx = this->insert(fields, values).execute();

      return this->instance();
    }

    TableClass& save() {
      auto it = this->fields.begin();
      std::vector<Statement> statements;
      std::vector<Statement> values;

      for (; it != this->fields.end(); ++it) {
        if ((*it).second->getName() == this->getId() ||
            (*it).second->template getValue<std::string>().empty()) {
          continue;
        }

        auto left = this->operator[]((*it).second->getName());
        auto right = this->literal((*it).second->template getValue<std::string>());

        statements.push_back(left = right);
      }

      this->rootStatement.clear();

      auto p = this->update(statements)
          .where(this->operator[](this->getId()) == this->literal(this->v<int>(this->getId())))
          .execute();

      return this->instance();
    }

    TableClass first() {
      try {
        auto newTable = TableClass(this->alias);
        pqxx::work work(*Connection::getInstance().getConnection());
        pqxx::result results = work.exec(this->toSql());
        work.commit();

        if (results.empty()) {
          return newTable;
        }

        auto it = results[0].begin();

        for (; it != results[0].end(); ++it) {
          auto ppp = (*it).name();
          auto finderIt = this->fields.find((*it).name());
          std::string value((*it).c_str());

          if (finderIt != this->fields.end()) {
            newTable.template f((*it).name())->setValue(value);
          } else {
            newTable.template addField<std::string>((*it).name());
            newTable.template f((*it).name())->setValue(value);
          }
        }

        this->rootStatement.clear();

        return newTable;
      } catch (const std::exception &e) {
        throw Exceptions::ExecutionError(e.what());
      }
    }

    std::vector<TableClass> execute() {
      try {
        std::vector<TableClass> result;
        pqxx::work work(*Connection::getInstance().getConnection());
        pqxx::result results = work.exec(this->toSql());
        work.commit();

        auto rowsIt = results.begin();

        for (; rowsIt != results.end(); ++rowsIt) {
          auto colsIt = (*rowsIt).begin();
          auto newTable = TableClass(this->alias);

          for (; colsIt != (*rowsIt).end(); ++colsIt) {
            auto finderIt = this->fields.find((*colsIt).name());
            std::string value((*colsIt).c_str());

            if (finderIt != this->fields.end()) {
              newTable.template f((*colsIt).name())->setValue(value);
            } else {
              newTable.template addField<std::string>((*colsIt).name());
              newTable.template f((*colsIt).name())->setValue(value);
            }
          }

          if (!results.empty()) {
            result.push_back(newTable);
          }
        }

        this->rootStatement.clear();

        return result;
      } catch (const std::exception &e) {
        throw Exceptions::ExecutionError(e.what());
      }
    }

    virtual std::string getName() = 0;
    virtual std::string getId() = 0;
    virtual void setFields() = 0;
    virtual TableClass& instance() = 0;
  private:
    Statement rootStatement;
    std::map<std::string, std::shared_ptr<Field>> fields;
    std::string alias;
  };
}