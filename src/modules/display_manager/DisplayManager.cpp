#include "DisplayManager.h"
#include "modules/logger/Logger.h"

bool DisplayManager::begin() {
    if (!panelDriver_.begin()) {
        Logger::error("DisplayPanelDriver initialization failed");
        initialized_ = false;
        return false;
    }
    initialized_ = true;
    brightness_ = 100;
    Logger::info("DisplayManager initialized");
    panelDriver_.fillScreen(0, 0, 0);
    return true;
}

void DisplayManager::update() {
    panelDriver_.update();
}

void DisplayManager::setBrightness(uint8_t percent) {
    if (percent > 100) {
        percent = 100;
    }
    brightness_ = percent;
    Logger::info(String("Display brightness: ") + brightness_ + "%");
}

uint8_t DisplayManager::getBrightness() const {
    return brightness_;
}

bool DisplayManager::isInitialized() const {
    return initialized_;
}

bool DisplayManager::fillScreen(uint8_t r, uint8_t g, uint8_t b) {
    return panelDriver_.fillScreen(r, g, b);
}
