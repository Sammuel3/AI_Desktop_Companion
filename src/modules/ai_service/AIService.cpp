#include "AIService.h"
#include "modules/logger/Logger.h"

bool AIService::begin() {
    initialized_ = true;
    busy_ = false;
    hasReply_ = false;
    lastPrompt_ = "";
    lastReply_ = "";
    statusText_ = "AI: Idle";
    Logger::info("AIService initialized");
    return true;
}

void AIService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool AIService::isInitialized() const {
    return initialized_;
}

bool AIService::isBusy() const {
    return busy_;
}

bool AIService::hasReply() const {
    return hasReply_;
}

String AIService::getLastPrompt() const {
    return lastPrompt_;
}

String AIService::getLastReply() const {
    return lastReply_;
}

String AIService::getStatusText() const {
    return statusText_;
}

bool AIService::sendMessage(const char* message) {
    if (!initialized_ || busy_) {
        return false;
    }
    if (message == nullptr || message[0] == '\0') {
        return false;
    }
    lastPrompt_ = message;
    busy_ = false;
    hasReply_ = true;
    lastReply_ = "AI placeholder reply";
    statusText_ = "AI: Reply ready";
    Logger::info("AIService placeholder reply ready");
    return true;
}

void AIService::clearConversation() {
    busy_ = false;
    hasReply_ = false;
    lastPrompt_ = "";
    lastReply_ = "";
    statusText_ = "AI: Idle";
    Logger::info("AIService conversation cleared");
}
