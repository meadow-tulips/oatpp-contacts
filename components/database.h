#pragma once
#include <filesystem>
#include <oatpp/core/macro/component.hpp>
#include "../db_clients/contacts-db.hpp"
#include "./configure.h"

class DatabaseComponent {

    OATPP_CREATE_COMPONENT(std::shared_ptr<ContactsDb>, contactsDb)([]{
        std::filesystem::path envFilePath = std::filesystem::current_path()/".env";
        Configuration configuration(envFilePath);
        configuration.addDatabase("oatpp_contacts");
        auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(configuration.getConnectionString());

        auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider, 10, std::chrono::seconds(5));

        auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

        return std::make_shared<ContactsDb>(executor);
    }());
};
