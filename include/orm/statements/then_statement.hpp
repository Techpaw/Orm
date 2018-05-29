#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <orm/statements/statement.hpp>

namespace Orm {
  class ThenStatement : public Statement {
  public:
    explicit ThenStatement(Statement statement) :
        statement{std::make_shared<Statement>(statement)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;

      sql << "THEN (" << this->statement->toSql(noAlias) << ") ";

      return sql.str();
    };
  private:
    std::shared_ptr<Statement> statement;
  };
}