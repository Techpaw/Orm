#pragma once

#include <string>
#include <sstream>
#include <orm/constants.hpp>
#include <orm/statements/statement.hpp>

namespace Orm {
  class JoinStatement : public Statement {
  public:
    explicit JoinStatement(JoinType type, std::string table, std::string alias) :
      type{type},
      table{std::move(table)},
      alias{std::move(alias)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;

      if (this->type == JoinType::INNER) {
        sql << "LEFT JOIN " << this->table << " ";
      }

      if (!this->alias.empty()) {
        sql << "AS " << this->alias << " ";
      }

      return sql.str();
    };
  private:
    JoinType type;
    std::string table;
    std::string alias;
  };
}