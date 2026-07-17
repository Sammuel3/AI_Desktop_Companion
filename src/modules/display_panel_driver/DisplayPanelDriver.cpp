#include "DisplayPanelDriver.h"
#include "modules/logger/Logger.h"

bool DisplayPanelDriver::begin() {
    if (!realDriver_.begin()) {
        Logger::error("ESP32DisplayPanelDriver initialization failed");
        initialized_ = false;
        return false;
    }
    initialized_ = true;
    width_ = realDriver_.getWidth();
    height_ = realDriver_.getHeight();
    Logger::info("DisplayPanelDriver initialized with ESP32DisplayPanelDriver");
    return true;
}

void DisplayPanelDriver::update() {
    realDriver_.update();
}

bool DisplayPanelDriver::isInitialized() const {
    return initialized_;
}

uint16_t DisplayPanelDriver::getWidth() const {
    return width_;
}

uint16_t DisplayPanelDriver::getHeight() const {
    return height_;
}

bool DisplayPanelDriver::fillScreen(uint8_t r, uint8_t g, uint8_t b) {
    if (!initialized_) {
        Logger::error("DisplayPanelDriver fillScreen failed: not initialized");
        return false;
    }
    return realDriver_.fillScreen(r, g, b);
}
