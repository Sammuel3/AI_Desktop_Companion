#include "MenuScreen.h"
#include "../../logger/Logger.h"

bool MenuScreen::begin() {
    // ---- Create screen ----
    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // ---- Title ----
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "MENU");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // ---- Menu Items ----
    itemWeather_ = lv_label_create(screen_);
    lv_label_set_text(itemWeather_, "Weather");
    lv_obj_set_style_text_color(itemWeather_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(itemWeather_, LV_ALIGN_CENTER, 0, -60);

    itemAlbum_ = lv_label_create(screen_);
    lv_label_set_text(itemAlbum_, "Album");
    lv_obj_set_style_text_color(itemAlbum_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(itemAlbum_, LV_ALIGN_CENTER, 0, -20);

    itemSettings_ = lv_label_create(screen_);
    lv_label_set_text(itemSettings_, "Settings");
    lv_obj_set_style_text_color(itemSettings_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(itemSettings_, LV_ALIGN_CENTER, 0, 20);

    itemAbout_ = lv_label_create(screen_);
    lv_label_set_text(itemAbout_, "About");
    lv_obj_set_style_text_color(itemAbout_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(itemAbout_, LV_ALIGN_CENTER, 0, 60);

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
