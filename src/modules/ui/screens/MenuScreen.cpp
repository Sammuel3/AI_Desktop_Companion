#include "MenuScreen.h"
#include "../../logger/Logger.h"

bool MenuScreen::begin(UIActionManager* actionManager) {
    if (actionManager == nullptr) {
        Logger::error("MenuScreen: UIActionManager is null");
        return false;
    }
    actionManager_ = actionManager;

    // ---- Create screen ----
    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // ---- Title ----
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "MENU");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // ---- Weather ----
    itemWeather_ = lv_label_create(screen_);
    lv_label_set_text(itemWeather_, "Weather");
    lv_obj_set_style_text_color(itemWeather_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(itemWeather_, LV_ALIGN_CENTER, 0, -60);
    lv_obj_add_flag(itemWeather_, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(itemWeather_, onItemClicked, LV_EVENT_CLICKED, this);

    // ---- Album ----
    itemAlbum_ = lv_label_create(screen_);
    lv_label_set_text(itemAlbum_, "Album");
    lv_obj_set_style_text_color(itemAlbum_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(itemAlbum_, LV_ALIGN_CENTER, 0, -20);
    lv_obj_add_flag(itemAlbum_, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(itemAlbum_, onItemClicked, LV_EVENT_CLICKED, this);

    // ---- Settings ----
    itemSettings_ = lv_label_create(screen_);
    lv_label_set_text(itemSettings_, "Settings");
    lv_obj_set_style_text_color(itemSettings_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(itemSettings_, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_flag(itemSettings_, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(itemSettings_, onItemClicked, LV_EVENT_CLICKED, this);

    // ---- About ----
    itemAbout_ = lv_label_create(screen_);
    lv_label_set_text(itemAbout_, "About");
    lv_obj_set_style_text_color(itemAbout_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(itemAbout_, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_flag(itemAbout_, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(itemAbout_, onItemClicked, LV_EVENT_CLICKED, this);

    Logger::info("MenuScreen initialized");
    return true;
}

void MenuScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
}

void MenuScreen::hide() {
}

void MenuScreen::update() {
}

void MenuScreen::onItemClicked(lv_event_t* event) {
    lv_obj_t* target = lv_event_get_target(event);
    MenuScreen* self = static_cast<MenuScreen*>(lv_event_get_user_data(event));
    if (self == nullptr || self->actionManager_ == nullptr) {
        return;
    }

    if (target == self->itemWeather_) {
        self->actionManager_->setAction(UIAction::OPEN_WEATHER);
        Logger::info("Menu action: OPEN_WEATHER");
    } else if (target == self->itemAlbum_) {
        self->actionManager_->setAction(UIAction::OPEN_ALBUM);
        Logger::info("Menu action: OPEN_ALBUM");
    } else if (target == self->itemSettings_) {
        self->actionManager_->setAction(UIAction::OPEN_SETTINGS);
        Logger::info("Menu action: OPEN_SETTINGS");
    } else if (target == self->itemAbout_) {
        self->actionManager_->setAction(UIAction::OPEN_ABOUT);
        Logger::info("Menu action: OPEN_ABOUT");
    }
}
