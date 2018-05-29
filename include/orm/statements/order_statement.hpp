#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <orm/constants.hpp>
#include <orm/statements/statement.hpp>

namespace Orm {
  class OrderStatement : public Statement {
  public:
    explicit OrderStatement(std::vector<Statement> args, OrderType orderType = OrderType::ASC) :
      args{std::move(args)},
      orderType{orderType}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto it = this->args.begin();

      sql << " ORDER BY (";

      for (; it != this->args.end(); ++it) {
        sql << (*it).toSql(noAlias);

        if (std::next(it) != this->args.end() && this->args.size() > 1) {
          sql << ", ";
        }
      }

      sql << ")";

      if (this->orderType == OrderType::ASC) {
        sql << " ASC ";
      } else {
        sql << " DESC ";
      }

      return sql.str();
    };
  private:
    std::vector<Statement> args;
    OrderType orderType;
  };
}