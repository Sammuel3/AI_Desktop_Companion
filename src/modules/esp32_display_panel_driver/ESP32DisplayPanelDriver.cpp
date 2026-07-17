#include "ESP32DisplayPanelDriver.h"
#include "modules/logger/Logger.h"
#include "ESP_Panel.h"
#include "modules/panel_context/PanelContext.h"

bool ESP32DisplayPanelDriver::begin() {
    Logger::info("ESP32DisplayPanelDriver begin");

    ESP_Panel& panel = PanelContext::getPanel();

    // ESP_Panel::init() and begin() return void in v1.1.1
    panel.init();
    panel.begin();

    // Use getLcd() as fallback success indicator
    if (panel.getLcd() == nullptr) {
        Logger::error("ESP_Panel init failed");
        return false;
    }

    if (panel.getBacklight() != nullptr) {
        panel.getBacklight()->on();
        panel.getBacklight()->setBrightness(100);
    }

    initialized_ = true;
    width_ = 800;
    height_ = 480;
    Logger::info("ESP32DisplayPanelDriver initialized");
    return true;
}

void ESP32DisplayPanelDriver::update() {
    // 当前为空实现，不输出周期日志，避免刷屏。
}

bool ESP32DisplayPanelDriver::isInitialized() const {
    return initialized_;
}

uint16_t ESP32DisplayPanelDriver::getWidth() const {
    return width_;
}

uint16_t ESP32DisplayPanelDriver::getHeight() const {
    return height_;
}

bool ESP32DisplayPanelDriver::fillScreen(uint8_t r, uint8_t g, uint8_t b) {
    if (!initialized_) {
        Logger::error("ESP32DisplayPanelDriver fillScreen failed: not initialized");
        return false;
    }

    ESP_Panel& panel = PanelContext::getPanel();

    if (panel.getLcd() == nullptr) {
        Logger::error("ESP32DisplayPanelDriver fillScreen failed: LCD not available");
        return false;
    }

    uint16_t color565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

    // Allocate one row buffer from PSRAM
    uint16_t *rowBuf = (uint16_t *)ps_malloc(width_ * sizeof(uint16_t));
    if (rowBuf == nullptr) {
        Logger::error("ESP32DisplayPanelDriver fillScreen failed: no memory");
        return false;
    }

    for (int i = 0; i < width_; i++) {
        rowBuf[i] = color565;
    }

    // drawBitmap uses exclusive end coordinates [x_start, x_end) × [y_start, y_end)
    // delegates to esp_lcd_panel_draw_bitmap which uses [x1, x2) × [y1, y2)
    for (int row = 0; row < height_; row++) {
        panel.getLcd()->drawBitmap(0, row, width_, row + 1, rowBuf);
    }

    free(rowBuf);
    Logger::info("ESP32DisplayPanelDriver fillScreen done");
    return true;
}
