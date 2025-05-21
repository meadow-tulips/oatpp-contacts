#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class StreamLinedResponse:public oatpp::DTO {

  DTO_INIT(StreamLinedResponse, DTO);
  DTO_FIELD(oatpp::Int32, status);
  DTO_FIELD(oatpp::String, message);
};

#include OATPP_CODEGEN_END(DTO)

