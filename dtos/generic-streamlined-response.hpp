
#pragma once

#include "./streamlined-response.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template <typename T>
class GenericStreamLinedResponse: public StreamLinedResponse {

    DTO_INIT(GenericStreamLinedResponse, StreamLinedResponse);
    DTO_FIELD(oatpp::Object<T>, data);
};


#include OATPP_CODEGEN_END(DTO)
