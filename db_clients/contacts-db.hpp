
#pragma once

#include "../dtos/contact-dto.hpp"
#include <filesystem>
#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

class ContactsDb : public oatpp::orm::DbClient {
public:
  ContactsDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
      : oatpp::orm::DbClient(executor) {
    try {
      oatpp::orm::SchemaMigration migration(executor);
      std::filesystem::path sqlMigrationFile =
          std::filesystem::current_path() / "sql" / "001_init.sql";

      migration.addFile(1, oatpp::String(sqlMigrationFile.generic_string()));
      migration.migrate();
      auto version = executor->getSchemaVersion();

      OATPP_LOGD("Contacts DB", "Migration - OK. Version = %ld", version);
    } catch (const std::exception &e) {
      OATPP_LOGE("Migration Error", "Error during Migration: %s", e.what());
    } catch (...) {
      OATPP_LOGE("Migration Error", "Unknown error during Migration");
      // Optionally log a stack trace or additional information
    }
  };
  QUERY(getAllContacts,
        "SELECT name, email, \"phoneNumbers\" FROM contacts LIMIT :limit "
        "OFFSET :offset", // select * from contacts
        PARAM(oatpp::UInt32, limit), PARAM(oatpp::UInt32, offset));
  QUERY(createContact,
        "INSERT into contacts (name, email, \"phoneNumbers\") VALUES "
        "(:contact.name, :contact.email, :contact.phoneNumbers) RETURNING *",
        PARAM(oatpp::Object<ContactDTO>, contact));
  QUERY(updateContact,
        "UPDATE contacts set name=:contact.name, email=:contact.email, "
        "\"phoneNumbers\"=:contact.phoneNumbers WHERE name=:contact.name "
        "RETURNING *",
        PARAM(oatpp::Object<ContactDTO>, contact));

  QUERY(searchContact,
        "SELECT * from contacts WHERE name % :name ORDER BY similarity(name, "
        ":name) DESC",
        PARAM(oatpp::String, name));

  QUERY(deleteContact, "DELETE from contacts where LOWER(name) = LOWER(:name) RETURNING *",
        PARAM(oatpp::String, name));
};

#include OATPP_CODEGEN_END(DbClient)
