#pragma once

#include <string>
#include <sstream>
#include <orm/statements/node.hpp>

namespace Orm {
  class ComparisonOperator : public Node {
  public:
    explicit ComparisonOperator(std::string comparisonOperator) :
      comparisonOperator{std::move(comparisonOperator)}
    {}

    std::string toSql(bool noAlias = false) override {
      std::stringstream sql;
      auto it = this->children.begin();

      for (; it != this->children.end(); ++it) {
        if(it == this->children.begin() || it == this->children.end()) {
          sql << (*it)->toSql(noAlias);
        } else {
          sql << this->comparisonOperator << (*it)->toSql(noAlias);
        }
      }

      return sql.str();
    }

  private:
    std::string comparisonOperator;
  };
}