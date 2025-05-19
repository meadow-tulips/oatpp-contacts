#ifndef CONTACTS_CONTROLLER_H
#define CONTACTS_CONTROLLER_H

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include "../dtos/contact-dto.hpp"
#include "../dtos/stream-line-response.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class ContactsController:public oatpp::web::server::api::ApiController {

public:
    ContactsController(OATPP_COMPONENT(std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>, objectMapper)): oatpp::web::server::api::ApiController(objectMapper) {};

    static std::shared_ptr<ContactsController> createShared() {
       OATPP_COMPONENT(std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>, objectMapper);
       return std::make_shared<ContactsController>(objectMapper);
    };

    ENDPOINT("GET", "/contacts", getAllContacts) {


        return createResponse(Status::CODE_200, "Hi");
    };

};

#include OATPP_CODEGEN_END(ApiController)

#endif
