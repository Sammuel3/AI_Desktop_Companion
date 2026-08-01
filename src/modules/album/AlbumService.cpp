#include "AlbumService.h"
#include "../logger/Logger.h"
#include <FS.h>
#include <SD.h>

bool AlbumService::begin(SDCardService* sdCard) {
    if (sdCard == nullptr) {
        Logger::error("AlbumService: SDCardService is null");
        return false;
    }
    sdCard_ = sdCard;
    initialized_ = true;
    images_.clear();
    currentIndex_ = 0;
    Logger::info("AlbumService initialized");
    return true;
}

void AlbumService::update() {
}

bool AlbumService::scanImages() {
    if (!initialized_ || sdCard_ == nullptr) {
        return false;
    }
    if (!sdCard_->isMounted()) {
        Logger::warn("AlbumService: SD card not mounted");
        return false;
    }

    images_.clear();
    currentIndex_ = 0;

    File root = SD.open(ALBUM_DIR);
    if (!root) {
        Logger::warn(String("AlbumService: failed to open ") + ALBUM_DIR);
        return false;
    }
    if (!root.isDirectory()) {
        Logger::warn(String("AlbumService: ") + ALBUM_DIR + " is not a directory");
        root.close();
        return false;
    }

    File file = root.openNextFile();
    while (file) {
        if (!file.isDirectory()) {
            String name = file.name();
            if (isImageFile(name)) {
                String path = String(ALBUM_DIR) + "/" + name;
                images_.push_back(path);
            }
        }
        file.close();
        file = root.openNextFile();
    }
    root.close();

    Logger::info(String("AlbumService: found ") + String(images_.size()) + " images");
    return true;
}

int AlbumService::getImageCount() const {
    return static_cast<int>(images_.size());
}

String AlbumService::getImagePath(int index) const {
    if (index < 0 || index >= static_cast<int>(images_.size())) {
        return "";
    }
    return images_[index];
}

String AlbumService::getCurrentImagePath() const {
    if (images_.empty()) {
        return "";
    }
    return images_[currentIndex_];
}

void AlbumService::nextImage() {
    if (images_.size() <= 1) {
        return;
    }
    currentIndex_++;
    if (currentIndex_ >= static_cast<int>(images_.size())) {
        currentIndex_ = 0;
    }
}

void AlbumService::previousImage() {
    if (images_.size() <= 1) {
        return;
    }
    if (currentIndex_ == 0) {
        currentIndex_ = static_cast<int>(images_.size()) - 1;
    } else {
        currentIndex_--;
    }
}

bool AlbumService::isInitialized() const {
    return initialized_;
}

bool AlbumService::isImageFile(const String& name) const {
    static const char* extensions[] = {".jpg", ".jpeg", ".png"};
    for (const char* ext : extensions) {
        if (name.endsWith(ext)) {
            return true;
        }
    }
    return false;
}
