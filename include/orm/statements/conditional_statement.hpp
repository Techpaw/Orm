#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <orm/constants.hpp>
#include <orm/statements/statement.hpp>

namespace Orm {
  class ConditionalStatement : public Statement {
  public:
    explicit ConditionalStatement(ConditionType conditionType, Statement statement) :
      conditionType{conditionType},
      statement{std::make_shared<Statement>(statement)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;

      if (this->conditionType == ConditionType::OR) {
        sql << "OR ";
      } else {
        sql << "AND ";
      }

      sql << this->statement->toSql(noAlias);

      return sql.str();
    };
  private:
    ConditionType conditionType;
    std::shared_ptr<Statement> statement;
  };
}