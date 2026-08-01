#include "AboutScreen.h"
#include "../../logger/Logger.h"

AboutScreen::AboutScreen() {
}

void AboutScreen::begin(UIDataProvider* provider) {
    provider_ = provider;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "ABOUT");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Device Name
    deviceLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(deviceLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(deviceLabel_, LV_ALIGN_CENTER, 0, -20);

    // Version
    versionLabel_ = lv_label_create(screen_);
    lv_label_set_text(versionLabel_, "Version 1.0");
    lv_obj_set_style_text_color(versionLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(versionLabel_, LV_ALIGN_CENTER, 0, 20);

    update();
    initialized_ = true;
    Logger::info("AboutScreen initialized");
}

void AboutScreen::update() {
    if (provider_ != nullptr && deviceLabel_ != nullptr) {
        String devText = "Device: " + provider_->getDeviceName();
        lv_label_set_text(deviceLabel_, devText.c_str());
    }
}

void AboutScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
    Logger::info("AboutScreen show");
}

void AboutScreen::hide() {
}

bool AboutScreen::isInitialized() const {
    return initialized_;
}
