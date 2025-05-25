#ifndef CONTACT_SERVICE_H
#define CONTACT_SERVICE_H

#include "../db_clients/contacts-db.hpp"
#include "../dtos/contact-dto.hpp"
#include "../dtos/search-dto.hpp"
#include "../dtos/generic-streamlined-response.hpp"
#include "../dtos/paginated-streamlined-response.hpp"
#include <oatpp/core/macro/component.hpp>

class ContactService {

private:
  OATPP_COMPONENT(std::shared_ptr<ContactsDb>, contactsDb);

public:
  oatpp::Object<PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>>
  getAllContacts(int page = 0, int size = 10);

  oatpp::Object<GenericStreamLinedResponse<ContactDTO>>
  createContact(const oatpp::Object<ContactDTO> &);

  oatpp::Object<GenericStreamLinedResponse<ContactDTO>>
  updateContact(const oatpp::Object<ContactDTO> &);

  oatpp::Object<PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>>
  searchContact(const oatpp::Object<SearchInputDTO> &);

  oatpp::Object<GenericStreamLinedResponse<ContactDTO>>
  deleteContact(const oatpp::Object<SearchInputDTO> &);

};

#endif
