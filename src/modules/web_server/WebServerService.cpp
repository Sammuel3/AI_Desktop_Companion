#include "WebServerService.h"
#include "../logger/Logger.h"

WebServerService::WebServerService() {
}

bool WebServerService::begin() {
    initialized_ = true;
    running_ = false;
    Logger::info("WebServerService initialized");
    return true;
}

void WebServerService::update() {
}

bool WebServerService::start() {
    if (!initialized_) {
        return false;
    }
    running_ = true;
    Logger::info("WebServerService started");
    return true;
}

void WebServerService::stop() {
    running_ = false;
    Logger::info("WebServerService stopped");
}

bool WebServerService::isRunning() const {
    return running_;
}

String WebServerService::getStatusJson() const {
    String json = "{";
    json += "\"service\":\"webserver\",";
    json += "\"running\":" + String(running_ ? "true" : "false");
    json += "}";
    return json;
}

bool WebServerService::isInitialized() const {
    return initialized_;
}
