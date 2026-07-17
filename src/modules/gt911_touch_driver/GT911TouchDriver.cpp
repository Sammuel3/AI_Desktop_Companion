#include "GT911TouchDriver.h"
#include "modules/logger/Logger.h"
#include "modules/panel_context/PanelContext.h"
#include "ESP_Panel.h"

bool GT911TouchDriver::begin() {
    ESP_Panel& panel = PanelContext::getPanel();

    if (panel.getLcdTouch() == nullptr) {
        Logger::error("GT911 touch not available");
        initialized_ = false;
        return false;
    }

    initialized_ = true;
    touched_ = false;
    x_ = 0;
    y_ = 0;
    Logger::info("GT911TouchDriver initialized");
    return true;
}

void GT911TouchDriver::update() {
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

bool GT911TouchDriver::isInitialized() const {
    return initialized_;
}

bool GT911TouchDriver::isTouched() const {
    return touched_;
}

uint16_t GT911TouchDriver::getX() const {
    return x_;
}

uint16_t GT911TouchDriver::getY() const {
    return y_;
}
