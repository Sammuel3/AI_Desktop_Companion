#include "MemoService.h"
#include "modules/logger/Logger.h"

bool MemoService::begin() {
    initialized_ = true;
    hasMemo_ = false;
    title_ = "";
    content_ = "";
    updatedAt_ = "";
    statusText_ = "Memo: Empty";
    Logger::info("MemoService initialized");
    return true;
}

void MemoService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool MemoService::isInitialized() const {
    return initialized_;
}

bool MemoService::hasMemo() const {
    return hasMemo_;
}

String MemoService::getTitle() const {
    return title_;
}

String MemoService::getContent() const {
    return content_;
}

String MemoService::getUpdatedAt() const {
    return updatedAt_;
}

String MemoService::getStatusText() const {
    return statusText_;
}

void MemoService::setMemo(const char* title, const char* content, const char* updatedAt) {
    title_ = title ? title : "";
    content_ = content ? content : "";
    updatedAt_ = updatedAt ? updatedAt : "";
    hasMemo_ = (title_.length() > 0 || content_.length() > 0);
    statusText_ = hasMemo_ ? "Memo: Ready" : "Memo: Empty";
    Logger::info("MemoService memo updated");
}

void MemoService::clearMemo() {
    hasMemo_ = false;
    title_ = "";
    content_ = "";
    updatedAt_ = "";
    statusText_ = "Memo: Empty";
    Logger::info("MemoService memo cleared");
}
