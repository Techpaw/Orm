#pragma once

#include <string>
#include <sstream>
#include <memory>
#include <orm/statements/statement.hpp>

namespace Orm {
  class GroupStatement : public Statement {
  public:
    explicit GroupStatement(Statement statement) {
      this->statement = std::make_shared<Statement>(statement);
    }

    std::string toSql(bool noAlias = false) {
      std::stringstream sql;
      sql << "(" << this->statement->toSql(noAlias) << ") ";
      return sql.str();
    }
  private:
    std::shared_ptr<Statement> statement;
  };
}