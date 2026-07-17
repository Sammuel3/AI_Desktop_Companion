#include "SDCardService.h"
#include "modules/logger/Logger.h"

bool SDCardService::begin() {
    initialized_ = true;
    mounted_ = false;
    cardAvailable_ = false;
    statusText_ = "SD: Not mounted";
    totalBytes_ = 0;
    usedBytes_ = 0;
    Logger::info("SDCardService initialized");
    return true;
}

void SDCardService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool SDCardService::isInitialized() const {
    return initialized_;
}

bool SDCardService::isMounted() const {
    return mounted_;
}

bool SDCardService::isCardAvailable() const {
    return cardAvailable_;
}

String SDCardService::getStatusText() const {
    return statusText_;
}

uint64_t SDCardService::getTotalBytes() const {
    return totalBytes_;
}

uint64_t SDCardService::getUsedBytes() const {
    return usedBytes_;
}
