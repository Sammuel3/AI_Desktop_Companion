#include "SettingsService.h"
#include "../logger/Logger.h"

SettingsService::SettingsService() {
}

bool SettingsService::begin(ConfigService* config) {
    if (config == nullptr) {
        Logger::error("SettingsService: ConfigService is null");
        return false;
    }
    configService_ = config;

    brightness_ = configService_->getBrightness();
    deviceName_ = configService_->getDeviceName();
    autoConnect_ = configService_->getAutoConnect();

    initialized_ = true;
    Logger::info("SettingsService initialized");
    return true;
}

void SettingsService::update() {
}

// ---- Brightness ----

void SettingsService::setBrightness(int value) {
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    brightness_ = value;
    if (configService_ != nullptr) {
        configService_->setBrightness(value);
    }
}

int SettingsService::getBrightness() const {
    return brightness_;
}

// ---- Device Name ----

void SettingsService::setDeviceName(const String& name) {
    deviceName_ = name;
    if (configService_ != nullptr) {
        configService_->setDeviceName(name);
    }
}

String SettingsService::getDeviceName() const {
    return deviceName_;
}

// ---- Auto Connect ----

void SettingsService::setAutoConnect(bool enabled) {
    autoConnect_ = enabled;
    if (configService_ != nullptr) {
        configService_->setAutoConnect(enabled);
    }
}

bool SettingsService::isAutoConnectEnabled() const {
    return autoConnect_;
}

bool SettingsService::isInitialized() const {
    return initialized_;
}
