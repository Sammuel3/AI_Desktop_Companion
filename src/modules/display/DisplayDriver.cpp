#include "DisplayDriver.h"
#include "../logger/Logger.h"
#include "../panel_context/PanelContext.h"
#include "ESP_Panel.h"

bool DisplayDriver::begin() {
    Logger::info("DisplayDriver begin");

    ESP_Panel& panel = PanelContext::getPanel();
    panel.init();
    panel.begin();

    if (panel.getLcd() == nullptr) {
        Logger::error("DisplayDriver: LCD init failed");
        return false;
    }

    if (panel.getBacklight() != nullptr) {
        panel.getBacklight()->on();
        panel.getBacklight()->setBrightness(100);
    }

    touchReady_ = (panel.getLcdTouch() != nullptr);
    if (touchReady_) {
        Logger::info("DisplayDriver: GT911 touch ready");
    } else {
        Logger::warn("DisplayDriver: GT911 touch not detected");
    }

    initialized_ = true;
    Logger::info("DisplayDriver initialized (JC8048W550C / ST7262)");
    return true;
}

void DisplayDriver::setBacklight(bool enable) {
    ESP_Panel& panel = PanelContext::getPanel();
    if (panel.getBacklight() != nullptr) {
        if (enable) {
            panel.getBacklight()->on();
        } else {
            panel.getBacklight()->off();
        }
    }
}

bool DisplayDriver::isReady() const {
    return initialized_ && touchReady_;
}

uint16_t DisplayDriver::getWidth() const {
    return width_;
}

uint16_t DisplayDriver::getHeight() const {
    return height_;
}
