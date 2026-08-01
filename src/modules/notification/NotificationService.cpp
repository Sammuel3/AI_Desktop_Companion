#include "NotificationService.h"
#include "../logger/Logger.h"

NotificationService::NotificationService() {
}

bool NotificationService::begin() {
    initialized_ = true;
    available_ = false;
    message_ = "";
    Logger::info("NotificationService initialized");
    return true;
}

void NotificationService::update() {
}

void NotificationService::notify(const String& message) {
    message_ = message;
    available_ = true;
    Logger::info(String("Notification: ") + message);
}

String NotificationService::getMessage() const {
    return message_;
}

bool NotificationService::hasNotification() const {
    return available_;
}

void NotificationService::clear() {
    available_ = false;
    message_ = "";
}

bool NotificationService::isInitialized() const {
    return initialized_;
}
