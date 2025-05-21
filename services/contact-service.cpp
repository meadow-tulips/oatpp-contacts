#include "./contact-service.hpp"
#include <iostream>
#include <oatpp/web/protocol/http/Http.hpp>

oatpp::Object<PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>>
ContactService::getAllContacts(int page, int size) {
  // Initialize response object

  auto res =
      PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>::createShared();

  try {
    std::cout << page << " " << size << "" << std::endl;
    int nextOffset = page * size;
    auto dbResult = contactsDb->getAllContacts(size, nextOffset);

    if (!dbResult->isSuccess()) {
      // If database query fails, set the error status and message
      OATPP_LOGE("Database Error", "Query failed. Error: %s",
                 dbResult->getErrorMessage()->c_str());
      res->status = oatpp::web::protocol::http::Status::CODE_500.code;
      res->message = "Database query error";
      res->data = {};
    } else {
      // If successful, set success status and message
      res->status = oatpp::web::protocol::http::Status::CODE_200.code;
      res->message = "Success";
      res->data = dbResult->fetch<oatpp::List<oatpp::Object<ContactDTO>>>();
    }
    // Return response
    return res;
  } catch (const std::exception &e) {
    OATPP_LOGE("Service Error:", "%s", e.what());
    // If any exception occurs, set status and message accordingly
    res->status = oatpp::web::protocol::http::Status::CODE_500.code;
    res->message = "Unexpected error occurred";
    res->data = {};
    return res;
  }
};

oatpp::Object<GenericStreamLinedResponse<ContactDTO>>
ContactService::createContact(const oatpp::Object<ContactDTO> &) {

  auto _res = GenericStreamLinedResponse<ContactDTO>::createShared();

  return _res;
};
