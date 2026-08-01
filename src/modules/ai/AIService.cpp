#include "AIService.h"
#include "../logger/Logger.h"

AIService::AIService() {
}

bool AIService::begin() {
    initialized_ = true;
    lastResponse_ = "";
    Logger::info("AIService initialized");
    return true;
}

void AIService::update() {
    // reserved
}

bool AIService::request(const String& prompt) {
    if (!initialized_) {
        return false;
    }
    lastResponse_ = "AI response placeholder";
    Logger::info("AI request processed");
    return true;
}

String AIService::getLastResponse() const {
    return lastResponse_;
}

bool AIService::isInitialized() const {
    return initialized_;
}
