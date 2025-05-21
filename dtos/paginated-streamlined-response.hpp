#pragma once

#include "./streamlined-response.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template <typename T>
class PaginatedStreamLinedResponse: public StreamLinedResponse {

    DTO_INIT(PaginatedStreamLinedResponse, StreamLinedResponse);
    DTO_FIELD(oatpp::List<T>, data);
};


#include OATPP_CODEGEN_END(DTO)
