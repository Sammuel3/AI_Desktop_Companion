#include "AlbumService.h"

bool AlbumService::begin() {
    initialized_ = true;
    return true;
}

void AlbumService::update() {
}

bool AlbumService::nextImage() {
    if (!albumReady_ || imageCount_ <= 1) {
        return false;
    }

    currentIndex_++;
    if (currentIndex_ >= imageCount_) {
        currentIndex_ = 0;
    }
    return true;
}

bool AlbumService::previousImage() {
    if (!albumReady_ || imageCount_ <= 1) {
        return false;
    }

    if (currentIndex_ == 0) {
        currentIndex_ = imageCount_ - 1;
    } else {
        currentIndex_--;
    }
    return true;
}

bool AlbumService::selectImage(size_t index) {
    if (!albumReady_ || index >= imageCount_) {
        return false;
    }

    currentIndex_ = index;
    return true;
}

bool AlbumService::isInitialized() const {
    return initialized_;
}

bool AlbumService::isAlbumReady() const {
    return albumReady_;
}

size_t AlbumService::getImageCount() const {
    return imageCount_;
}

size_t AlbumService::getCurrentIndex() const {
    return currentIndex_;
}

String AlbumService::getCurrentImagePath() const {
    if (!albumReady_) {
        return "";
    }
    return currentImagePath_;
}
