#include "AIService.h"

bool AIService::begin() {
    initialized_ = true;
    return true;
}

void AIService::update() {
}

bool AIService::request(const String& input) {
    input_ = input;
    busy_ = false;
    responseValid_ = false;
    response_ = "";
    return true;
}

bool AIService::isInitialized() const {
    return initialized_;
}

bool AIService::isBusy() const {
    return busy_;
}

bool AIService::isResponseValid() const {
    return responseValid_;
}

String AIService::getResponse() const {
    if (!responseValid_) {
        return "";
    }
    return response_;
}

void AIService::clearResponse() {
    response_.clear();
    responseValid_ = false;
}
