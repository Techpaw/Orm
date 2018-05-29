#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <orm/statements/statement.hpp>
#include <orm/statements/when_statement.hpp>
#include <orm/statements/then_statement.hpp>
#include <orm/statements/else_statement.hpp>
#include <orm/statements/end_statement.hpp>

namespace Orm {
  class CaseStatement : public Statement {
  public:
    explicit CaseStatement() :
      statement{nullptr}
    {}

    explicit CaseStatement(Statement statement) :
      statement{std::make_shared<Statement>(statement)}
    {}

    CaseStatement& when(Statement statement) {
      this->addChild(WhenStatement(std::move(statement)));
      return *this;
    }

    CaseStatement& then(Statement statement) {
      this->addChild(ThenStatement(std::move(statement)));
      return *this;
    }

    CaseStatement& els(Statement statement) {
      this->addChild(ElseStatement(std::move(statement)));
      return *this;
    }

    Statement end() {
      auto newStatement = Statement();
      this->addChild(EndStatement());
      newStatement.addChild(*this);
      return newStatement;
    }

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto it = this->children.begin();

      sql << "CASE ";

      if (this->statement != nullptr) {
        sql << this->statement->toSql(noAlias) << " ";
      }

      for (; it != this->children.end(); ++it) {
        sql << (*it)->toSql(noAlias);
      }

      return sql.str();
    };
  private:
    std::shared_ptr<Statement> statement;
  };
}