#pragma once

#include <string>
#include <sstream>
#include <orm/statements/statement.hpp>

namespace Orm {
  class EndStatement : public Statement {
  public:
    explicit EndStatement() = default;

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;

      sql << "END ";

      return sql.str();
    };
  };
}