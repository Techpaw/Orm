#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <orm/statements/statement.hpp>

namespace Orm {
  class InsertStatement : public Statement {
  public:
    explicit InsertStatement(
      std::vector<Statement> fields,
      std::vector<Statement> values,
      std::string table
    ) :
      fields{std::move(fields)},
      values{std::move(values)},
      table{std::move(table)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto fieldsIt = this->fields.begin();
      auto valuesIt = this->values.begin();

      sql << "INSERT INTO " << this->table << " (";

      for (; fieldsIt != this->fields.end(); ++fieldsIt) {
        sql << (*fieldsIt).toSql(true);

        if (std::next(fieldsIt) != this->fields.end() && this->fields.size() > 1) {
          sql << ", ";
        }
      }

      sql << " ) VALUES (";

      for (; valuesIt != this->values.end(); ++valuesIt) {
        sql << (*valuesIt).toSql(true);

        if (std::next(valuesIt) != this->values.end() && this->values.size() > 1) {
          sql << ", ";
        }
      }

      sql << " ) ";

      return sql.str();
    };
  private:
    std::vector<Statement> fields;
    std::vector<Statement> values;
    std::string table;
  };
}