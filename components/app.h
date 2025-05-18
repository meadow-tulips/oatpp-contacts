#ifndef APP_COMPONENT_H
#define APP_COMPONENT_H

#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>

class AppComponent {

public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([]{
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([]{

        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);

        std::shared_ptr<oatpp::web::server::HttpConnectionHandler> _httpConnectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(httpRouter);

        return _httpConnectionHandler;

    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([]{
        std::shared_ptr<oatpp::network::ServerConnectionProvider> _scp = oatpp::network::tcp::server::ConnectionProvider::createShared({ "0.0.0.0", 9000, oatpp::network::Address::IP_4});
        return _scp;
    }());


    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>, objectMapper)([] {
            auto jsonMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            return jsonMapper;
        }());

    void registerControllers();

};



#endif
