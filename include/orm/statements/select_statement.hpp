#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <orm/statements/statement.hpp>

namespace Orm {
  class SelectStatement : public Statement {
  public:
    explicit SelectStatement(
      std::vector<Statement> args,
      std::string table,
      std::string alias
    ) :
      args{std::move(args)},
      table{std::move(table)},
      alias{std::move(alias)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto it = this->args.begin();

      sql << "SELECT ";

      if (this->args.empty()) {
        sql << " * ";
      } else {
        sql << "(";
      }

      for (; it != this->args.end(); ++it) {
        sql << (*it).toSql(noAlias);

        if (std::next(it) != this->args.end() && this->args.size() > 1) {
          sql << ", ";
        }
      }

      if (!this->args.empty()) {
        sql << ") ";
      }

      sql << "FROM " << this->table << " ";

      if (!this->alias.empty()) {
        sql << "AS " << this->alias << " ";
      }

      return sql.str();
    };
  private:
    std::vector<Statement> args;
    std::string table;
    std::string alias;
  };
}