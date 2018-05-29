#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <orm/statements/statement.hpp>

namespace Orm {
  class UpdateStatement : public Statement {
  public:
    explicit UpdateStatement(std::vector<Statement> args, std::string table, std::string alias) :
      args{std::move(args)},
      table{std::move(table)},
      alias{std::move(alias)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto it = this->args.begin();

      if (!this->alias.empty()) {
        sql << "UPDATE " << this->table << " " << this->alias << " SET ";
      } else {
        sql << "UPDATE " << this->table << " SET (";
      };

      for (; it != this->args.end(); ++it) {
        sql << (*it).toSql(true);

        if (std::next(it) != this->args.end() && this->args.size() > 1) {
          sql << ", ";
        }
      }

      sql << " ";

      return sql.str();
    };
  private:
    std::vector<Statement> args;
    std::string table;
    std::string alias;
  };
}