#include "UIManager.h"
#include "../logger/Logger.h"

bool UIManager::begin(UIDataProvider* provider) {
    if (provider == nullptr) {
        Logger::error("UIManager: UIDataProvider is null");
        return false;
    }

    if (homeScreen_.begin(provider)) {
        Logger::info("HomeScreen registered in UIManager");
    }
    showHome();

    initialized_ = true;
    Logger::info("UIManager initialized");
    return true;
}

void UIManager::update() {
    homeScreen_.update();
}

void UIManager::showHome() {
    currentScreen_ = "Home";
    Logger::info("UI screen: Home");
}

void UIManager::refresh() {
    homeScreen_.update();
    Logger::info("UI refresh triggered");
}

const char* UIManager::getCurrentScreen() const {
    return currentScreen_;
}

bool UIManager::isInitialized() const {
    return initialized_;
}
