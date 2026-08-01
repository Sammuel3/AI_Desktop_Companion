#include "UIManager.h"
#include "../logger/Logger.h"

UIManager::UIManager() {
}

bool UIManager::begin(UIDataProvider* provider, SettingsService* settings) {
    if (provider == nullptr) {
        Logger::error("UIManager: UIDataProvider is null");
        return false;
    }

    if (homeScreen_.begin(provider)) {
        Logger::info("HomeScreen registered in UIManager");
    }

    if (menuScreen_.begin(&uiActionManager_)) {
        Logger::info("MenuScreen registered in UIManager");
    }

    if (settings != nullptr && settingsScreen_.begin(settings)) {
        Logger::info("SettingsScreen registered in UIManager");
    }

    aboutScreen_.begin(provider);
    Logger::info("AboutScreen registered in UIManager");

    weatherScreen_.begin(provider);
    Logger::info("WeatherScreen registered in UIManager");

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
        case ScreenType::SETTINGS:
            settingsScreen_.update();
            break;
        case ScreenType::ABOUT:
            aboutScreen_.update();
            break;
        case ScreenType::WEATHER:
            weatherScreen_.update();
            break;
    }
}

void UIManager::switchScreen(UIManager::ScreenType screen) {
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
        case ScreenType::SETTINGS:
            settingsScreen_.hide();
            break;
        case ScreenType::ABOUT:
            aboutScreen_.hide();
            break;
        case ScreenType::WEATHER:
            weatherScreen_.hide();
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
        case ScreenType::SETTINGS:
            settingsScreen_.show();
            Logger::info("UI screen: Settings");
            break;
        case ScreenType::ABOUT:
            aboutScreen_.show();
            Logger::info("UI screen: About");
            break;
        case ScreenType::WEATHER:
            weatherScreen_.show();
            Logger::info("UI screen: Weather");
            break;
    }

    currentScreen_ = screen;
}

UIManager::ScreenType UIManager::getCurrentScreen() const {
    return currentScreen_;
}

UIActionManager* UIManager::getActionManager() {
    return &uiActionManager_;
}

bool UIManager::isInitialized() const {
    return initialized_;
}
