#include "UIManager.h"
#include "modules/logger/Logger.h"
#include <cstring>

bool UIManager::begin() {
    initialized_ = true;
    if (homeScreen_.begin()) {
        Logger::info("HomeScreen registered in UIManager");
    }
    showHome();
    Logger::info("UIManager initialized");
    return true;
}

void UIManager::update() {
    if (std::strcmp(currentScreen_, "Home") == 0) {
        homeScreen_.update();
    }
}

void UIManager::showHome() {
    currentScreen_ = "Home";
    homeScreen_.show();
    Logger::info("UI screen: Home");
}

void UIManager::showAlbum() {
    if (std::strcmp(currentScreen_, "Home") == 0) {
        homeScreen_.hide();
    }
    currentScreen_ = "Album";
    Logger::info("UI screen: Album");
}

void UIManager::showMemo() {
    if (std::strcmp(currentScreen_, "Home") == 0) {
        homeScreen_.hide();
    }
    currentScreen_ = "Memo";
    Logger::info("UI screen: Memo");
}

void UIManager::showChat() {
    if (std::strcmp(currentScreen_, "Home") == 0) {
        homeScreen_.hide();
    }
    currentScreen_ = "Chat";
    Logger::info("UI screen: Chat");
}

const char* UIManager::getCurrentScreen() const {
    return currentScreen_;
}

bool UIManager::isInitialized() const {
    return initialized_;
}

void UIManager::setHomeTimeText(const char* text) {
    homeScreen_.setTimeText(text);
}

void UIManager::setHomeDateText(const char* text) {
    homeScreen_.setDateText(text);
}

void UIManager::setHomeWifiText(const char* text) {
    homeScreen_.setWifiText(text);
}

void UIManager::setHomeBatteryText(const char* text) {
    homeScreen_.setBatteryText(text);
}

void UIManager::setHomeWeatherText(const char* text) {
    homeScreen_.setWeatherText(text);
}
