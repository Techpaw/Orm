#pragma once

#include <string>
#include <sstream>
#include <orm/statements/statement.hpp>

namespace Orm {
  class FieldStatement : public Statement {
  public:
    explicit FieldStatement(
      std::string table,
      std::string name
    ):
      table{std::move(table)},
      name{std::move(name)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;

      if (noAlias) {
        sql << this->name;
      } else {
        sql << this->table << "." << this->name;
      }

      return sql.str();
    }
  private:
    std::string table;
    std::string name;
  };
}