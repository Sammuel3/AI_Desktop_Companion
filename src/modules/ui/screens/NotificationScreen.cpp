#include "NotificationScreen.h"
#include "../../logger/Logger.h"

NotificationScreen::NotificationScreen() {
}

bool NotificationScreen::begin(UIDataProvider* provider) {
    if (provider == nullptr) {
        Logger::error("NotificationScreen: UIDataProvider is null");
        return false;
    }
    provider_ = provider;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "NOTIFICATIONS");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Count
    countLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(countLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(countLabel_, LV_ALIGN_CENTER, 0, -20);

    // Message
    messageLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(messageLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(messageLabel_, LV_ALIGN_CENTER, 0, 20);

    update();
    initialized_ = true;
    Logger::info("NotificationScreen initialized");
    return true;
}

void NotificationScreen::update() {
    if (provider_ == nullptr) return;

    if (countLabel_ != nullptr) {
        String text = "Count: " + String(provider_->getNotificationCount());
        lv_label_set_text(countLabel_, text.c_str());
    }
    if (messageLabel_ != nullptr) {
        String msg = provider_->getNotificationMessage();
        if (msg.length() == 0) {
            msg = "No notifications";
        }
        lv_label_set_text(messageLabel_, msg.c_str());
    }
}

void NotificationScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
    Logger::info("NotificationScreen show");
}

void NotificationScreen::hide() {
}

bool NotificationScreen::isInitialized() const {
    return initialized_;
}
