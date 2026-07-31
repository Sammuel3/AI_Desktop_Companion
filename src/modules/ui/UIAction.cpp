#include "UIAction.h"

void UIActionManager::setAction(UIAction action) {
    currentAction_ = action;
}

UIAction UIActionManager::getAction() const {
    return currentAction_;
}

void UIActionManager::clearAction() {
    currentAction_ = UIAction::NONE;
}
