#include "HomeScreen.h"
#include "../../logger/Logger.h"

bool HomeScreen::begin(UIDataProvider* provider) {
    if (provider == nullptr) {
        Logger::error("HomeScreen: UIDataProvider is null");
        return false;
    }
    provider_ = provider;

    // ---- Create screen ----
    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // ---- Title ----
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "AI Desktop Companion");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // ---- Time ----
    timeLabel_ = lv_label_create(screen_);
    lv_label_set_text(timeLabel_, provider_->getTimeText().c_str());
    lv_obj_set_style_text_color(timeLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(timeLabel_, LV_ALIGN_CENTER, 0, -40);

    // ---- Weather ----
    weatherLabel_ = lv_label_create(screen_);
    lv_label_set_text(weatherLabel_, provider_->getWeatherText().c_str());
    lv_obj_set_style_text_color(weatherLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(weatherLabel_, LV_ALIGN_CENTER, -60, 40);

    // ---- Temperature ----
    temperatureLabel_ = lv_label_create(screen_);
    lv_label_set_text(temperatureLabel_, provider_->getTemperatureText().c_str());
    lv_obj_set_style_text_color(temperatureLabel_, lv_color_hex(0xffaa00), LV_PART_MAIN);
    lv_obj_align(temperatureLabel_, LV_ALIGN_CENTER, 60, 40);

    // ---- Battery ----
    batteryLabel_ = lv_label_create(screen_);
    lv_label_set_text(batteryLabel_, provider_->getBatteryText().c_str());
    lv_obj_set_style_text_color(batteryLabel_, lv_color_hex(0x00ff88), LV_PART_MAIN);
    lv_obj_align(batteryLabel_, LV_ALIGN_CENTER, 0, 80);

    // ---- WiFi ----
    wifiLabel_ = lv_label_create(screen_);
    lv_label_set_text(wifiLabel_, provider_->getWifiText().c_str());
    lv_obj_set_style_text_color(wifiLabel_, lv_color_hex(0x8888ff), LV_PART_MAIN);
    lv_obj_align(wifiLabel_, LV_ALIGN_BOTTOM_MID, 0, -20);

    // ---- Activate screen ----
    lv_scr_load(screen_);

    Logger::info("HomeScreen initialized");
    return true;
}

void HomeScreen::update() {
    if (provider_ == nullptr) {
        return;
    }

    lv_label_set_text(timeLabel_, provider_->getTimeText().c_str());
    lv_label_set_text(weatherLabel_, provider_->getWeatherText().c_str());
    lv_label_set_text(temperatureLabel_, provider_->getTemperatureText().c_str());
    lv_label_set_text(batteryLabel_, provider_->getBatteryText().c_str());
    lv_label_set_text(wifiLabel_, provider_->getWifiText().c_str());
}
