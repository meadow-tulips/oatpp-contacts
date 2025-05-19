
#ifndef CONTACTS_DB_H
#define CONTACTS_DB_H

#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

class ContactsDb : public oatpp::orm::DbClient {

public:
  ContactsDb(const std::shared_ptr<oatpp::orm::Executor> &executor)
      : oatpp::orm::DbClient(executor){};

  QUERY(getAllContacts, "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
        PARAM(oatpp::UInt32, offset), PARAM(oatpp::UInt32, limit))
};

#include OATPP_CODEGEN_END(DbClient)

#endif
