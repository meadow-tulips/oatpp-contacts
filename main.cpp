#include "./components/app.h"
#include <iostream>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/network/Server.hpp>
#include <dotenv.h>

void run() {
  AppComponent components;

  components.registerControllers();

  oatpp::network::Server server(components.serverConnectionProvider.getObject(),
                                components.serverConnectionHandler.getObject());

  auto port = components.serverConnectionProvider.getObject()
                  ->getProperty("port")
                  .toString()
                  ->c_str();
  OATPP_LOGI("Server", "Server running on %s port", port);
  server.run();
}

int main() {

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
};
