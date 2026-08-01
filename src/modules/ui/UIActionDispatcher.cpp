#include "UIActionDispatcher.h"
#include "UIManager.h"
#include "../logger/Logger.h"

UIActionDispatcher::UIActionDispatcher() {
}

bool UIActionDispatcher::begin(UIActionManager* actionManager, UIManager* uiManager) {
    if (actionManager == nullptr) {
        Logger::error("UIActionDispatcher: UIActionManager is null");
        return false;
    }
    if (uiManager == nullptr) {
        Logger::error("UIActionDispatcher: UIManager is null");
        return false;
    }
    actionManager_ = actionManager;
    uiManager_ = uiManager;
    initialized_ = true;
    Logger::info("UIActionDispatcher initialized");
    return true;
}

void UIActionDispatcher::update() {
    if (actionManager_ == nullptr || uiManager_ == nullptr) {
        return;
    }

    UIAction action = actionManager_->getAction();

    switch (action) {
        case UIAction::OPEN_WEATHER:
            Logger::info("Action: Weather");
            uiManager_->switchScreen(UIManager::ScreenType::WEATHER);
            break;
        case UIAction::OPEN_ALBUM:
            Logger::info("Action: Album");
            break;
        case UIAction::OPEN_SETTINGS:
            Logger::info("Action: Settings");
            uiManager_->switchScreen(UIManager::ScreenType::SETTINGS);
            break;
        case UIAction::OPEN_ABOUT:
            Logger::info("Action: About");
            uiManager_->switchScreen(UIManager::ScreenType::ABOUT);
            break;
        case UIAction::NONE:
        default:
            break;
    }

    actionManager_->clearAction();
}

bool UIActionDispatcher::isInitialized() const {
    return initialized_;
}
