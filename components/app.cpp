#include "../controllers/contacts-controller.hpp"
#include "./app.h"



void AppComponent::registerControllers() {
    this->httpRouter.getObject()->addController(ContactsController::createShared());
}

