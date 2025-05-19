#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <oatpp/core/Types.hpp>

class Configuration {
private:
  static oatpp::String host;
  oatpp::String database_connection_string;
public:
  Configuration(std::string env_file_name = "./.env");
  void attachDatabaseString(oatpp::String database_name);
  oatpp::String getConnectionString();
};

#endif
