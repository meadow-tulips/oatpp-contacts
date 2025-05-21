#ifndef CONTACT_SERVICE_H
#define CONTACT_SERVICE_H

#include "../db_clients/contacts-db.hpp"
#include "../dtos/contact-dto.hpp"
#include "../dtos/paginated-streamlined-response.hpp"
#include "../dtos/generic-streamlined-response.hpp"
#include <oatpp/core/macro/component.hpp>

class ContactService {

private:
  OATPP_COMPONENT(std::shared_ptr<ContactsDb>, contactsDb);

public:
  oatpp::Object<PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>> getAllContacts(int page = 0,
                                                             int size = 10);

  oatpp::Object<GenericStreamLinedResponse<ContactDTO>> createContact(const oatpp::Object<ContactDTO> &);
};

#endif
