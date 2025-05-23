#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class SearchInputDTO: public oatpp::DTO {

    DTO_INIT(SearchInputDTO, DTO);
    DTO_FIELD(oatpp::String, name);
};


#include OATPP_CODEGEN_END(DTO)
