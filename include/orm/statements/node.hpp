#pragma once

#include <string>
#include <sstream>
#include <list>
#include <memory>

namespace Orm {
  class Node : public std::enable_shared_from_this<Node> {
  public:
    template <typename T>
    void addChild(const T& node) {
      this->children.push_back(std::make_shared<T>(node));
    }

    virtual std::string toSql(bool noAlias = false) {
      std::stringstream sql;
      auto it = this->children.begin();

      for (; it != this->children.end(); ++it) {
        sql << (*it)->toSql(noAlias);
      }

      return sql.str();
    }
  protected:
    std::list<std::shared_ptr<Node>> children;
  };
}