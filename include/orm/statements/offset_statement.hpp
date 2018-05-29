#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <orm/statements/statement.hpp>

namespace Orm {
  class OffsetStatement : public Statement {
  public:
    explicit OffsetStatement(Statement statement) :
      statement{std::make_shared<Statement>(statement)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      sql << " OFFSET " << this->statement->toSql(noAlias) << " ";
      return sql.str();
    };
  private:
    std::shared_ptr<Statement> statement;
  };
}