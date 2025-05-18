#ifndef HelloController_hpp
#define HelloController_hpp

#include "oatpp/web/server/api/ApiController.hpp"
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

class HelloController : public oatpp::web::server::api::ApiController
{
public:
  HelloController(OATPP_COMPONENT(
      std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>,
      objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
  {
  }
  static std::shared_ptr<HelloController> createShared(OATPP_COMPONENT(
      std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>,
      objectMapper))
  {
    return std::make_shared<HelloController>(objectMapper);
  }

  ENDPOINT("GET", "/", root)
  {
    return createResponse(Status::CODE_200, "Hi");
  }
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* HelloController_hpp */
