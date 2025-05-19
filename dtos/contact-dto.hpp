#ifndef CONTACT_H
#define CONTACT_H

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "./stream-line-response.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
class ContactDTO :public oatpp::DTO {

    DTO_INIT(ContactDTO, oatpp::DTO);
    DTO_FIELD(oatpp::String, name);
    DTO_FIELD(oatpp::String, email);
    DTO_FIELD(oatpp::String, phoneNumber);

};

#include OATPP_CODEGEN_END(DTO)

#endif
