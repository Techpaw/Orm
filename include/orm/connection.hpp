#pragma once

#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include <orm/exceptions.hpp>

namespace Orm {
  class Connection {
  public:
    explicit Connection() = default;
    Connection(Connection const&) = delete;
    void operator=(Connection const&) = delete;

    static Connection& getInstance(
      std::string host = "",
      std::string port = "",
      std::string database = "",
      std::string username = "",
      std::string password = ""
    ) {
      static Connection instance;
      return instance;
    }

    void establish(
      std::string host,
      std::string port,
      std::string database,
      std::string username = "",
      std::string password = ""
    ) {
      std::stringstream ss;
      ss << "dbname = " << database << " ";
      ss << "hostaddr = " << host << " ";
      ss << "port = " << port << " ";

      if (!username.empty()) {
        ss << "user = " << username << " ";
      }

      if (!password.empty()) {
        ss << "password = " << password << " ";
      }

      this->connection = std::make_shared<pqxx::connection>(ss.str());

      if (!this->connection->is_open()) {
        throw Exceptions::ConnectionFailed();
      }
    }

    std::shared_ptr<pqxx::connection>& getConnection() {
      return this->connection;
    }
  private:
    std::shared_ptr<pqxx::connection> connection;
  };
}