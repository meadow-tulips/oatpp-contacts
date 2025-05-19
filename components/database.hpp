#ifndef DATABASE_H
#define DATABASE_H
#include "../configure.hpp"
#include "../db/contacts-db.hpp"
#include <oatpp-postgresql/ConnectionProvider.hpp>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/component.hpp>

class DatabaseComponent {
public:
  OATPP_CREATE_COMPONENT(std::shared_ptr<ContactsDb>, contactsDb)
  ([] {
    Configuration _configuration;
    _configuration.attachDatabaseString("contacts");
    auto connectionProvider =
        std::make_shared<oatpp::postgresql::ConnectionProvider>(
            _configuration.getConnectionString());
    /* Create database-specific ConnectionPool */
    auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(
        connectionProvider, 10, std::chrono::seconds(5));

    /* Create database-specific Executor */
    auto executor =
        std::make_shared<oatpp::postgresql::Executor>(connectionPool);

    /* Create MyClient database client */
    return std::make_shared<ContactsDb>(executor);
  }());
};

#endif
