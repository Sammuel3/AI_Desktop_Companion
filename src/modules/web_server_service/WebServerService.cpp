#include "WebServerService.h"
#include "modules/logger/Logger.h"

bool WebServerService::begin() {
    initialized_ = true;
    running_ = false;
    port_ = 80;
    statusText_ = "Web: Stopped";
    Logger::info("WebServerService initialized");
    return true;
}

void WebServerService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool WebServerService::isInitialized() const {
    return initialized_;
}

bool WebServerService::isRunning() const {
    return running_;
}

uint16_t WebServerService::getPort() const {
    return port_;
}

String WebServerService::getStatusText() const {
    return statusText_;
}

bool WebServerService::start() {
    if (!initialized_) {
        return false;
    }
    running_ = true;
    statusText_ = "Web: Running";
    Logger::info("WebServerService started placeholder");
    return true;
}

void WebServerService::stop() {
    running_ = false;
    statusText_ = "Web: Stopped";
    Logger::info("WebServerService stopped placeholder");
}
