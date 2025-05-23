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
ContactService::createContact(const oatpp::Object<ContactDTO> &_contact) {

  auto res = GenericStreamLinedResponse<ContactDTO>::createShared();

  try {

    auto dbResult = contactsDb->createContact(_contact);

    if (!dbResult->isSuccess()) {

      OATPP_LOGE("Database Error", "Query failed. Error: %s",
                 dbResult->getErrorMessage()->c_str());
      res->status = oatpp::web::protocol::http::Status::CODE_500.code;
      res->message = dbResult->getErrorMessage();
      res->data = nullptr;
    } else {
      // If successful, set success status and message
      res->status = oatpp::web::protocol::http::Status::CODE_200.code;
      res->message = "Success";
      auto addedList =
          dbResult->fetch<oatpp::List<oatpp::Object<ContactDTO>>>();
      res->data = addedList[0];
    }

  } catch (const std::exception &e) {
    OATPP_LOGE("Exception Found", "Query failed. Error: %s", e.what());
    res->status = oatpp::web::protocol::http::Status::CODE_500.code;
    res->message = "Unexpected error occurred";
    res->data = nullptr;
  }
  return res;
};

oatpp::Object<GenericStreamLinedResponse<ContactDTO>>
ContactService::updateContact(const oatpp::Object<ContactDTO> &_contact) {

  auto res = GenericStreamLinedResponse<ContactDTO>::createShared();

  try {

    auto dbResult = contactsDb->updateContact(_contact);

    if (!dbResult->isSuccess()) {

      OATPP_LOGE("Database Error", "Query failed. Error: %s",
                 dbResult->getErrorMessage()->c_str());
      res->status = oatpp::web::protocol::http::Status::CODE_500.code;
      res->message = dbResult->getErrorMessage();
      res->data = nullptr;
    } else {
      // If successful, set success status and message
      res->status = oatpp::web::protocol::http::Status::CODE_200.code;
      res->message = "Success";
      auto addedList =
          dbResult->fetch<oatpp::List<oatpp::Object<ContactDTO>>>();
      res->data = addedList[0];
    }

  } catch (const std::exception &e) {
    OATPP_LOGE("Exception Found", "Query failed. Error: %s", e.what());
    res->status = oatpp::web::protocol::http::Status::CODE_500.code;
    res->message = "Unexpected error occurred";
    res->data = nullptr;
  }
  return res;
};

oatpp::Object<PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>>
ContactService::searchContact(
    const oatpp::Object<SearchInputDTO> &searchInputDTO) {
  auto res =
      PaginatedStreamLinedResponse<oatpp::Object<ContactDTO>>::createShared();
  std::cout << "InputStart-" << static_cast<std::string>(searchInputDTO->name)
            << "-Input" << std::endl;
  try {
    auto dbResult = contactsDb->searchContact(searchInputDTO->name);

    if (!dbResult->isSuccess()) {
      res->status = oatpp::web::protocol::http::Status::CODE_500.code;
      res->message = dbResult->getErrorMessage();
    } else {

      res->status = oatpp::web::protocol::http::Status::CODE_200.code;
      res->message = "Success";
      res->data = dbResult->fetch<oatpp::List<oatpp::Object<ContactDTO>>>();
    }

  } catch (std::exception &e) {
    OATPP_LOGE("Search Exception", "%s", e.what());
    res->message = "Unexpected error occurred";
    res->data = {};
    res->status = oatpp::web::protocol::http::Status::CODE_500.code;
  }

  return res;
};

oatpp::Object<GenericStreamLinedResponse<ContactDTO>>
ContactService::deleteContact(
    const oatpp::Object<SearchInputDTO> &searchInputDTO) {

  auto res = GenericStreamLinedResponse<ContactDTO>::createShared();
  res->data = nullptr;

  try {
    auto dbResult = contactsDb->deleteContact(searchInputDTO->name);
    if (!dbResult->isSuccess()) {
      res->status = oatpp::web::protocol::http::Status::CODE_500.code;
      res->message = dbResult->getErrorMessage();
    } else {
      auto deletedContactList =
          dbResult->fetch<oatpp::List<oatpp::Object<ContactDTO>>>();
      if (deletedContactList->size() > 0) {
        res->status = oatpp::web::protocol::http::Status::CODE_200.code;
        res->message = "Successfully deleted contact";
      } else {
        res->status = oatpp::web::protocol::http::Status::CODE_400.code;
        res->message = "No contact found!";
      }
    }
  } catch (std::exception &e) {

    res->message = "Unexpected error occurred";
    res->status = oatpp::web::protocol::http::Status::CODE_500.code;
  }

  return res;
}
