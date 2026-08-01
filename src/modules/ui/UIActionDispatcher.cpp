#include "UIActionDispatcher.h"
#include "../logger/Logger.h"

UIActionDispatcher::UIActionDispatcher() {
}

bool UIActionDispatcher::begin(UIActionManager* actionManager) {
    if (actionManager == nullptr) {
        Logger::error("UIActionDispatcher: UIActionManager is null");
        return false;
    }
    actionManager_ = actionManager;
    initialized_ = true;
    Logger::info("UIActionDispatcher initialized");
    return true;
}

void UIActionDispatcher::update() {
    if (actionManager_ == nullptr) {
        return;
    }

    UIAction action = actionManager_->getAction();

    switch (action) {
        case UIAction::OPEN_WEATHER:
            Logger::info("Action: Weather");
            break;
        case UIAction::OPEN_ALBUM:
            Logger::info("Action: Album");
            break;
        case UIAction::OPEN_SETTINGS:
            Logger::info("Action: Settings");
            break;
        case UIAction::OPEN_ABOUT:
            Logger::info("Action: About");
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
