#ifndef CONTACTS_CONTROLLER_H
#define CONTACTS_CONTROLLER_H

#include "../dtos/contact-dto.hpp"
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
    return createDtoResponse(Status::CODE_200, contactService.getAllContacts());
  };

  ENDPOINT("POST", "/createContact", createContact, BODY_DTO(oatpp::Object<ContactDTO>, contactDTO)) {
    return createDtoResponse(Status::CODE_200, contactService.createContact(contactDTO));
  }

  static std::shared_ptr<ContactsController> createShared() {
    OATPP_COMPONENT(std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>,
                    objectMapper);
    return std::make_shared<ContactsController>(objectMapper);
  };
};

#include OATPP_CODEGEN_END(ApiController)

#endif
