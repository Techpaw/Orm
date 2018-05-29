#pragma once

#include <string>
#include <sstream>
#include <orm/statements/statement.hpp>

namespace Orm {
  class LiteralStatement : public Statement {
  public:
    explicit LiteralStatement(std::string value) : value{std::move(value)} {}

    std::string toSql(bool noAlias = false) override {
      return this->value;
    }

  private:
    std::string value;
  };
}