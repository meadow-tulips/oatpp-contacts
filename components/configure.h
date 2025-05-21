#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <oatpp/core/Types.hpp>

class Configuration  {
        oatpp::String connectionString;
public:
        Configuration(std::string envFilePath);
        oatpp::String getConnectionString();
        void addDatabase(oatpp::String database);
};

#endif
