#include "./components/app.h"
#include "./components/database.h"
#include <dotenv.h>
#include <iostream>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/network/Server.hpp>
#include <csignal>
#include <iostream>
#include <execinfo.h>
#include <unistd.h>

void signalHandler(int signum) {
  void *array[10];
  size_t size;

  size = backtrace(array, 10);
  std::cerr << "Error: signal " << signum << ":\n";
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

void run() {
  AppComponent components;
  DatabaseComponent databaseComponents;


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
  signal(SIGSEGV, signalHandler); // segmentation fault
  signal(SIGABRT, signalHandler); // abort
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
};
