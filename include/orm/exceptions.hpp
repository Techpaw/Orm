#pragma once

#include <string>

namespace Orm {
  namespace Exceptions {
    class ExecutionError : public std::exception {
    public:
      explicit ExecutionError(std::string description = "") :
        description{std::move(description)}
      {}

      const char* what() const throw () {
        return this->description.c_str();
      }
    private:
      std::string description;
    };

    class ConnectionFailed : public std::exception {
    public:
      const char* what() const throw () {
        return "Database connection failed";
      }
    };

    class InvalidFieldType : public std::exception {
    public:
      const char* what() const throw () {
        return "Type is not allowed";
      }
    };
  }
}