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

    if (menuScreen_.begin()) {
        Logger::info("MenuScreen registered in UIManager");
    }

    switchScreen(ScreenType::HOME);

    initialized_ = true;
    Logger::info("UIManager initialized");
    return true;
}

void UIManager::update() {
    switch (currentScreen_) {
        case ScreenType::HOME:
            homeScreen_.update();
            break;
        case ScreenType::MENU:
            menuScreen_.update();
            break;
    }
}

void UIManager::switchScreen(ScreenType screen) {
    if (currentScreen_ == screen) {
        return;
    }

    // Hide current screen
    switch (currentScreen_) {
        case ScreenType::HOME:
            homeScreen_.hide();
            break;
        case ScreenType::MENU:
            menuScreen_.hide();
            break;
    }

    // Show target screen
    switch (screen) {
        case ScreenType::HOME:
            homeScreen_.show();
            Logger::info("UI screen: Home");
            break;
        case ScreenType::MENU:
            menuScreen_.show();
            Logger::info("UI screen: Menu");
            break;
    }

    currentScreen_ = screen;
}

ScreenType UIManager::getCurrentScreen() const {
    return currentScreen_;
}

bool UIManager::isInitialized() const {
    return initialized_;
}
