#include "TimeScreen.h"
#include "../../logger/Logger.h"

TimeScreen::TimeScreen() {
}

bool TimeScreen::begin(UIDataProvider* provider) {
    if (provider == nullptr) {
        Logger::error("TimeScreen: UIDataProvider is null");
        return false;
    }
    provider_ = provider;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "TIME");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Time display
    timeLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(timeLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(timeLabel_, LV_ALIGN_CENTER, 0, 0);

    update();
    initialized_ = true;
    Logger::info("TimeScreen initialized");
    return true;
}

void TimeScreen::update() {
    if (provider_ != nullptr && timeLabel_ != nullptr) {
        lv_label_set_text(timeLabel_, provider_->getTime().c_str());
    }
}

void TimeScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
    Logger::info("TimeScreen show");
}

void TimeScreen::hide() {
}

bool TimeScreen::isInitialized() const {
    return initialized_;
}
