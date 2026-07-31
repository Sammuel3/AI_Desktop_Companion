#include "WebServerService.h"

bool WebServerService::begin() {
    initialized_ = true;
    running_ = false;
    return true;
}

void WebServerService::update() {
}

bool WebServerService::start() {
    if (!initialized_) {
        return false;
    }
    running_ = true;
    return true;
}

void WebServerService::stop() {
    running_ = false;
}

bool WebServerService::isInitialized() const {
    return initialized_;
}

bool WebServerService::isRunning() const {
    return running_;
}
