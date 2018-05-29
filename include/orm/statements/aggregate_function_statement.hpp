#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <orm/statements/statement.hpp>
#include <orm/statements/function_statement.hpp>

namespace Orm {
  class AggregateFunctionStatement : public Statement {
  public:
    explicit AggregateFunctionStatement(std::string name, std::vector<Statement> args = {}) :
      name{std::move(name)},
      args{std::move(args)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;

      if (this->args.empty()) {
        sql << this->name << "(*) ";
      } else {
        sql << FunctionStatement(this->name, this->args).toSql(noAlias);
      }

      return sql.str();
    }
  private:
    std::string name;
    std::vector<Statement> args;
  };
}