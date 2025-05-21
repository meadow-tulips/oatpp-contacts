#ifndef CONTACT_H
#define CONTACT_H

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class ContactDTO : public oatpp::DTO {
  DTO_INIT(ContactDTO, DTO)
  DTO_FIELD(oatpp::String, name);
  DTO_FIELD(oatpp::String, email);
  DTO_FIELD(oatpp::List<oatpp::String>, phoneNumbers);
};

#include OATPP_CODEGEN_END(DTO)

#endif // CONTACT_H
