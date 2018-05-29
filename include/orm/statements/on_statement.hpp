#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <orm/statements/statement.hpp>

namespace Orm {
  class OnStatement : public Statement {
  public:
    explicit OnStatement(Statement statement) :
      statement{std::make_shared<Statement>(statement)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      sql << "ON (" << this->statement->toSql(noAlias) << ") ";
      return sql.str();
    };
  private:
    std::shared_ptr<Statement> statement;
  };
}