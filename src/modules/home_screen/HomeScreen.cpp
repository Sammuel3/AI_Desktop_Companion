#include "HomeScreen.h"
#include "modules/logger/Logger.h"
#include <lvgl.h>

bool HomeScreen::begin() {
    if (root_ != nullptr) {
        return true;
    }

    // Root container: 800x480, dark background
    root_ = lv_obj_create(lv_scr_act());
    lv_obj_set_size(root_, 800, 480);
    lv_obj_center(root_);
    lv_obj_set_style_bg_color(root_, lv_color_hex(0x101820), LV_PART_MAIN);
    lv_obj_set_style_border_width(root_, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(root_, 0, LV_PART_MAIN);

    // Title label
    titleLabel_ = lv_label_create(root_);
    lv_label_set_text(titleLabel_, "SmartDesktop");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(titleLabel_, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Time label (center, offset up)
    timeLabel_ = lv_label_create(root_);
    lv_label_set_text(timeLabel_, timeText_);
    lv_obj_set_style_text_color(timeLabel_, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_align(timeLabel_, LV_ALIGN_CENTER, 0, -40);

    // Date label (below time)
    dateLabel_ = lv_label_create(root_);
    lv_label_set_text(dateLabel_, dateText_);
    lv_obj_set_style_text_color(dateLabel_, lv_color_hex(0xCCCCCC), LV_PART_MAIN);
    lv_obj_align_to(dateLabel_, timeLabel_, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);

    // WiFi label (bottom left)
    wifiLabel_ = lv_label_create(root_);
    lv_label_set_text(wifiLabel_, wifiText_);
    lv_obj_set_style_text_color(wifiLabel_, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_align(wifiLabel_, LV_ALIGN_BOTTOM_LEFT, 10, -10);

    // Battery label (bottom right)
    batteryLabel_ = lv_label_create(root_);
    lv_label_set_text(batteryLabel_, batteryText_);
    lv_obj_set_style_text_color(batteryLabel_, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_align(batteryLabel_, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

    // Weather label (bottom center)
    weatherLabel_ = lv_label_create(root_);
    lv_label_set_text(weatherLabel_, weatherText_);
    lv_obj_set_style_text_color(weatherLabel_, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_align(weatherLabel_, LV_ALIGN_BOTTOM_MID, 0, -10);

    refreshLabels();

    // Default hidden
    lv_obj_add_flag(root_, LV_OBJ_FLAG_HIDDEN);

    Logger::info("HomeScreen initialized");
    return true;
}

void HomeScreen::show() {
    if (root_ == nullptr) {
        if (!begin() || root_ == nullptr) {
            Logger::error("HomeScreen show failed: root not initialized");
            return;
        }
    }
    visible_ = true;
    lv_obj_clear_flag(root_, LV_OBJ_FLAG_HIDDEN);
    refreshLabels();
    Logger::info("HomeScreen shown");
}

void HomeScreen::hide() {
    visible_ = false;
    if (root_ != nullptr) {
        lv_obj_add_flag(root_, LV_OBJ_FLAG_HIDDEN);
    }
    Logger::info("HomeScreen hidden");
}

void HomeScreen::update() {
    // 当前不输出周期日志
}

const char* HomeScreen::getName() const {
    return "Home";
}

void HomeScreen::setTimeText(const char* text) {
    timeText_ = text ? text : "--:--";
    refreshLabels();
}

void HomeScreen::setDateText(const char* text) {
    dateText_ = text ? text : "----/--/--";
    refreshLabels();
}

void HomeScreen::setWifiText(const char* text) {
    wifiText_ = text ? text : "WiFi: Disconnected";
    refreshLabels();
}

void HomeScreen::setBatteryText(const char* text) {
    batteryText_ = text ? text : "Battery: --%";
    refreshLabels();
}

void HomeScreen::setWeatherText(const char* text) {
    weatherText_ = text ? text : "Weather: --";
    refreshLabels();
}

void HomeScreen::refreshLabels() {
    if (timeLabel_ != nullptr)    { lv_label_set_text(timeLabel_, timeText_); }
    if (dateLabel_ != nullptr)    { lv_label_set_text(dateLabel_, dateText_); }
    if (wifiLabel_ != nullptr)    { lv_label_set_text(wifiLabel_, wifiText_); }
    if (batteryLabel_ != nullptr) { lv_label_set_text(batteryLabel_, batteryText_); }
    if (weatherLabel_ != nullptr) { lv_label_set_text(weatherLabel_, weatherText_); }
}
