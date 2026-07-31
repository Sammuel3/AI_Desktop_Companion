#include "WebServerService.h"
#include "../logger/Logger.h"

bool WebServerService::begin() {
    initialized_ = true;
    running_ = false;
    return true;
}

void WebServerService::update() {
    if (running_ && server_ != nullptr) {
        server_->handleClient();
    }
}

void WebServerService::setSystemStatusManager(SystemStatusManager& manager) {
    statusManager_ = &manager;
}

bool WebServerService::start() {
    if (!initialized_) {
        return false;
    }
    if (running_) {
        return true;
    }

    server_ = new WebServer(80);
    server_->on("/api/status", [this]() {
        handleStatus();
    });
    server_->begin();
    running_ = true;
    Logger::info("WebServerService started on port 80");
    Logger::info("REST API: GET /api/status");
    return true;
}

void WebServerService::stop() {
    if (server_ != nullptr) {
        server_->stop();
        delete server_;
        server_ = nullptr;
    }
    running_ = false;
    Logger::info("WebServerService stopped");
}

bool WebServerService::isInitialized() const {
    return initialized_;
}

bool WebServerService::isRunning() const {
    return running_;
}

void WebServerService::handleStatus() {
    if (statusManager_ == nullptr) {
        server_->send(503, "application/json",
            "{\"error\":\"SystemStatusManager not available\"}");
        return;
    }

    SystemStatus status = statusManager_->getStatus();

    String json = "{";
    json += "\"wifiConnected\":" + String(status.wifiConnected ? "true" : "false") + ",";
    json += "\"batteryLevel\":" + String(status.batteryLevel) + ",";
    json += "\"weather\":\"" + status.weather + "\",";
    json += "\"temperature\":" + String(status.temperature, 1) + ",";
    json += "\"currentTime\":\"" + status.currentTime + "\",";
    json += "\"webServerRunning\":" + String(status.webServerRunning ? "true" : "false");
    json += "}";

    server_->send(200, "application/json", json);
}
