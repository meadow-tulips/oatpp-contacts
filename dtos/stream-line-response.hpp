#ifndef STREAMLINED_H
#define STREAMLINED_H

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

template <typename T>
class StreamLinedResponse: public oatpp::DTO {

    DTO_INIT(StreamLinedResponse, DTO);
    DTO_FIELD(Int32, status);
    DTO_FIELD(String, message);
    DTO_FIELD(oatpp::Object<T>, data);

};

#include OATPP_CODEGEN_END(DTO)

#endif
