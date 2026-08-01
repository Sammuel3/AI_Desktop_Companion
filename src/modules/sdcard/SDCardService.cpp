#include "SDCardService.h"
#include "../logger/Logger.h"

bool SDCardService::begin() {
    initialized_ = true;
    mounted_ = false;
    totalBytes_ = 0;
    usedBytes_ = 0;
    Logger::info("SDCardService initialized");
    return true;
}

void SDCardService::update() {
}

bool SDCardService::isMounted() const {
    return mounted_;
}

uint64_t SDCardService::getTotalBytes() const {
    return totalBytes_;
}

uint64_t SDCardService::getUsedBytes() const {
    return usedBytes_;
}

bool SDCardService::isInitialized() const {
    return initialized_;
}
