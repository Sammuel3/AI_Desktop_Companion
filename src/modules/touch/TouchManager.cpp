#include "TouchManager.h"
#include "../logger/Logger.h"
#include "../panel_context/PanelContext.h"
#include "ESP_Panel.h"

bool TouchManager::begin() {
    ESP_Panel& panel = PanelContext::getPanel();
    ESP_PanelLcdTouch* touch = panel.getLcdTouch();
    if (touch == nullptr) {
        Logger::warn("TouchManager: GT911 touch not available");
        return false;
    }
    initialized_ = true;
    Logger::info("TouchManager initialized");
    return true;
}

void TouchManager::update() {
    if (!initialized_) {
        return;
    }

    ESP_Panel& panel = PanelContext::getPanel();
    ESP_PanelLcdTouch* touch = panel.getLcdTouch();
    if (touch == nullptr) {
        touched_ = false;
        return;
    }

    touch->readData();
    if (touch->getTouchState()) {
        TouchPoint p = touch->getPoint(0);
        touched_ = true;
        x_ = p.x;
        y_ = p.y;
    } else {
        touched_ = false;
    }
}

bool TouchManager::isTouched() const {
    return touched_;
}

int TouchManager::getX() const {
    return x_;
}

int TouchManager::getY() const {
    return y_;
}
