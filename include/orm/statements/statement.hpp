#pragma once

#include <string>
#include <sstream>
#include <orm/constants.hpp>
#include <orm/statements/node.hpp>
#include <orm/statements/statement.hpp>
#include <orm/statements/comparison_operator.hpp>

namespace Orm {
  class Statement : public Node {
  public:
    explicit Statement() = default;

    Statement operator-(const Statement statement) {
      return this->defineOperator(statement, " - ");
    }

    Statement operator+(const Statement statement) {
      return this->defineOperator(statement, " + ");
    }

    Statement operator&&(const Statement &statement) {
      return this->defineOperator(statement, " AND ");
    }

    Statement operator||(const Statement &statement) {
      return this->defineOperator(statement, " OR ");
    }

    Statement operator==(const Statement &statement) {
      return this->defineOperator(statement, " = ");
    }

    Statement operator=(const Statement &statement) {
      return this->defineOperator(statement, " = ");
    }

    Statement operator!=(const Statement statement) {
      return this->defineOperator(statement, " <> ");
    }

    Statement operator<=(const Statement statement) {
      return this->defineOperator(statement, " <= ");
    }

    Statement operator<(const Statement statement) {
      return this->defineOperator(statement, " < ");
    }

    Statement operator>=(const Statement statement) {
      return this->defineOperator(statement, " >= ");
    }

    Statement operator>(const Statement statement) {
      return this->defineOperator(statement, " > ");
    }

    void clear() {
      this->children.clear();
    }
  private:
    Statement defineOperator(const Statement& statement, std::string op) {
      auto newStatement = Statement();
      auto operatorStatement = ComparisonOperator(std::move(op));

      operatorStatement.addChild<Statement>(*this);
      operatorStatement.addChild<Statement>(statement);
      newStatement.addChild<ComparisonOperator>(operatorStatement);

      return newStatement;
    }
  };
}