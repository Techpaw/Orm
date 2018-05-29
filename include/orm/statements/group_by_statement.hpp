#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <orm/statements/statement.hpp>

namespace Orm {
  class GroupByStatement : public Statement {
  public:
    explicit GroupByStatement(std::vector<Statement> args) :
        args{std::move(args)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto it = this->args.begin();

      sql << " GROUP BY (";

      for (; it != this->args.end(); ++it) {
        sql << (*it).toSql(noAlias);

        if (std::next(it) != this->args.end() && this->args.size() > 1) {
          sql << ", ";
        }
      }

      sql << ") ";

      return sql.str();
    };
  private:
    std::vector<Statement> args;
  };
}