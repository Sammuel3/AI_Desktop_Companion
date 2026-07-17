#include "AlbumService.h"
#include "modules/logger/Logger.h"

bool AlbumService::begin() {
    initialized_ = true;
    hasImages_ = false;
    imageCount_ = 0;
    currentIndex_ = -1;
    currentImagePath_ = "";
    statusText_ = "Album: No images";
    Logger::info("AlbumService initialized");
    return true;
}

void AlbumService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool AlbumService::isInitialized() const {
    return initialized_;
}

bool AlbumService::hasImages() const {
    return hasImages_;
}

int AlbumService::getImageCount() const {
    return imageCount_;
}

int AlbumService::getCurrentIndex() const {
    return currentIndex_;
}

String AlbumService::getCurrentImagePath() const {
    return currentImagePath_;
}

String AlbumService::getStatusText() const {
    return statusText_;
}

void AlbumService::nextImage() {
    if (!hasImages_) {
        return;
    }
    currentIndex_ = (currentIndex_ + 1) % imageCount_;
}

void AlbumService::previousImage() {
    if (!hasImages_) {
        return;
    }
    currentIndex_ = (currentIndex_ - 1 + imageCount_) % imageCount_;
}
