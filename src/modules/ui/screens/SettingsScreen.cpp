#include "SettingsScreen.h"
#include "../../logger/Logger.h"

bool SettingsScreen::begin(SettingsService* settings) {
    if (settings == nullptr) {
        Logger::error("SettingsScreen: SettingsService is null");
        return false;
    }
    settings_ = settings;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "SETTINGS");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Brightness
    brightnessLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(brightnessLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(brightnessLabel_, LV_ALIGN_CENTER, 0, -40);

    // Device Name
    deviceLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(deviceLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(deviceLabel_, LV_ALIGN_CENTER, 0, 0);

    // Auto Connect
    autoConnectLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(autoConnectLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(autoConnectLabel_, LV_ALIGN_CENTER, 0, 40);

    // Initial values
    update();

    Logger::info("SettingsScreen initialized");
    return true;
}

void SettingsScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
}

void SettingsScreen::hide() {
}

void SettingsScreen::update() {
    if (settings_ == nullptr) return;

    String brightText = "Brightness: " + String(settings_->getBrightness());
    lv_label_set_text(brightnessLabel_, brightText.c_str());

    String devText = "Device: " + settings_->getDeviceName();
    lv_label_set_text(deviceLabel_, devText.c_str());

    String autoText = "Auto WiFi: ";
    autoText += settings_->isAutoConnectEnabled() ? "ON" : "OFF";
    lv_label_set_text(autoConnectLabel_, autoText.c_str());
}
