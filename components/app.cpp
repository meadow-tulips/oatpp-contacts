#include "../controllers/helloworld.hpp"
#include "./app.h"



void AppComponent::registerControllers() {
    this->httpRouter.getObject()->addController(HelloController::createShared());
}

