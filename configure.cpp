#include "./configure.hpp"
#include <dotenv.h>

oatpp::String Configuration::host = dotenv::getenv("host");

Configuration::Configuration(std::string env_file_name) {
  dotenv::init(env_file_name.c_str());
  oatpp::String port = dotenv::getenv("port");
  oatpp::String user = dotenv::getenv("user");
  oatpp::String password = dotenv::getenv("password");

  database_connection_string = "postgresql://" + user + ":" + password + "@" +
                               Configuration::host + ":" + port;
}

void Configuration::attachDatabaseString(oatpp::String database_name) {
  database_connection_string + "/" + database_name;
}

oatpp::String Configuration::getConnectionString() {
  return database_connection_string;
}
