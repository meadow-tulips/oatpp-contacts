#ifndef CONTACTS_CONTROLLER_H
#define CONTACTS_CONTROLLER_H

#include "../dtos/contact-dto.hpp"
#include "../dtos/search-dto.hpp"
#include "../services/contact-service.hpp"
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

class ContactsController : public oatpp::web::server::api::ApiController {
private:
  ContactService contactService;

public:
  ContactsController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>,
      objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper){};

  ENDPOINT("GET", "/contacts", getAllContacts) {
    auto response = contactService.getAllContacts();
    Status status(response->status, response->message->c_str());

    return createDtoResponse(status, response);
  };

  ENDPOINT("POST", "/createContact", createContact,
           BODY_DTO(oatpp::Object<ContactDTO>, contactDTO)) {
    auto response = contactService.createContact(contactDTO);
    Status status(response->status, response->message->c_str());
    return createDtoResponse(status, response);
  }

  ENDPOINT("PUT", "/updateContact", updateContact,
           BODY_DTO(oatpp::Object<ContactDTO>, contactDTO)) {
    auto response = contactService.updateContact(contactDTO);
    Status status(response->status, response->message->c_str());
    return createDtoResponse(status, response);
  }

  ENDPOINT("POST", "/searchContact", searchContact,
           BODY_DTO(oatpp::Object<SearchInputDTO>, searchInput)) {
    auto response = contactService.searchContact(searchInput);
    Status status(response->status, response->message->c_str());
    return createDtoResponse(status, response);
  }

  ENDPOINT("DELETE", "/deleteContact", deleteContact,
           BODY_DTO(oatpp::Object<SearchInputDTO>, searchInput)) {
    auto response = contactService.deleteContact(searchInput);
    Status status(response->status, response->message->c_str());

    return createDtoResponse(status, response);
  };

  static std::shared_ptr<ContactsController> createShared() {
    OATPP_COMPONENT(std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>,
                    objectMapper);
    return std::make_shared<ContactsController>(objectMapper);
  };
};

#include OATPP_CODEGEN_END(ApiController)

#endif
