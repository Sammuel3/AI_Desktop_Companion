#include "UIEventManager.h"
#include "../logger/Logger.h"

bool UIEventManager::begin(TouchManager* touchManager, UIManager* uiManager) {
    if (touchManager == nullptr) {
        Logger::error("UIEventManager: TouchManager is null");
        return false;
    }
    if (uiManager == nullptr) {
        Logger::error("UIEventManager: UIManager is null");
        return false;
    }

    touchManager_ = touchManager;
    uiManager_ = uiManager;
    wasTouched_ = false;

    Logger::info("UIEventManager initialized");
    return true;
}

void UIEventManager::update() {
    if (touchManager_ == nullptr || uiManager_ == nullptr) {
        return;
    }

    bool isTouched = touchManager_->isTouched();

    // Rising edge detection — switch on touch press, not hold
    if (isTouched && !wasTouched_) {
        ScreenType current = uiManager_->getCurrentScreen();
        if (current == ScreenType::HOME) {
            uiManager_->switchScreen(ScreenType::MENU);
        } else {
            uiManager_->switchScreen(ScreenType::HOME);
        }
    }

    wasTouched_ = isTouched;
}
