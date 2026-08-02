#include "MemoScreen.h"
#include "../../logger/Logger.h"

MemoScreen::MemoScreen() {
}

void MemoScreen::begin(MemoService* memoService) {
    memoService_ = memoService;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "MEMO");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Count
    countLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(countLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(countLabel_, LV_ALIGN_CENTER, 0, -20);

    // Memo content
    memoLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(memoLabel_, lv_color_hex(0xcccccc), LV_PART_MAIN);
    lv_obj_align(memoLabel_, LV_ALIGN_CENTER, 0, 20);

    update();
    initialized_ = true;
    Logger::info("MemoScreen initialized");
}

void MemoScreen::update() {
    if (memoService_ == nullptr) return;

    int count = memoService_->getMemoCount();
    if (countLabel_ != nullptr) {
        String text = "Memos: " + String(count);
        lv_label_set_text(countLabel_, text.c_str());
    }
    if (memoLabel_ != nullptr) {
        String text;
        if (count > 0) {
            text = memoService_->getMemoTitle(0) + "\n" + memoService_->getMemoContent(0);
        } else {
            text = "No memo";
        }
        lv_label_set_text(memoLabel_, text.c_str());
    }
}

void MemoScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
    Logger::info("MemoScreen show");
}

void MemoScreen::hide() {
}

bool MemoScreen::isInitialized() const {
    return initialized_;
}
