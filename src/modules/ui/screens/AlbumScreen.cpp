#include "AlbumScreen.h"
#include "../../logger/Logger.h"

AlbumScreen::AlbumScreen() {
}

bool AlbumScreen::begin(AlbumService* albumService) {
    if (albumService == nullptr) {
        Logger::error("AlbumScreen: AlbumService is null");
        return false;
    }
    albumService_ = albumService;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "ALBUM");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Image status
    imageLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(imageLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(imageLabel_, LV_ALIGN_CENTER, 0, -20);

    // Current path
    pathLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(pathLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(pathLabel_, LV_ALIGN_CENTER, 0, 20);

    update();
    initialized_ = true;
    Logger::info("AlbumScreen initialized");
    return true;
}

void AlbumScreen::update() {
    if (albumService_ == nullptr) return;

    if (imageLabel_ != nullptr) {
        int count = albumService_->getImageCount();
        String text = "Images: " + String(count);
        lv_label_set_text(imageLabel_, text.c_str());
    }
    if (pathLabel_ != nullptr) {
        String path = albumService_->getCurrentImagePath();
        if (path.length() == 0) {
            path = "(no image)";
        }
        lv_label_set_text(pathLabel_, path.c_str());
    }
}

void AlbumScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
    Logger::info("AlbumScreen show");
}

void AlbumScreen::hide() {
}

bool AlbumScreen::isInitialized() const {
    return initialized_;
}
