#pragma once

#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <orm/constants.hpp>

namespace Orm {
  class Field {
  public:
    explicit Field(std::string name, Type type, std::string defaultValue):
      name{std::move(name)},
      type{type},
      defaultValue{std::move(defaultValue)}
    {}

    void setValue(std::string value) {
      this->fieldValue = std::move(value);
    }

    std::string getName() {
      return this->name;
    }

    template<typename T>
    T getValue() {
      return boost::lexical_cast<T>(this->value());
    }
  private:
    std::string name;
    std::string fieldValue;
    std::string defaultValue;
    Type type;

    std::string value() {
      if (this->fieldValue.empty()) {
        return this->defaultValue;
      }

      return this->fieldValue;
    }
  };
}