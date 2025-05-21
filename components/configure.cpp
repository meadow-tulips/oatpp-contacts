
#include <dotenv.h>
#include "./configure.h"

Configuration::Configuration(std::string envFilePath) {
    dotenv::init(envFilePath.c_str());
    oatpp::String host("localhost");
    auto port = dotenv::getenv("port");
    auto user = dotenv::getenv("user");
    auto password = dotenv::getenv("password");
    connectionString = "postgresql://" + user + ":" + password + "@" + host + ":" + port;
}

oatpp::String Configuration::getConnectionString() {
    return connectionString;
}


void Configuration::addDatabase(oatpp::String database)
{

    connectionString = connectionString + "/" + database;
}
