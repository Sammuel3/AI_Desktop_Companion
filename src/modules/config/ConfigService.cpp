#include "ConfigService.h"
#include "../logger/Logger.h"

bool ConfigService::begin(StorageService* storage) {
    if (storage == nullptr) {
        Logger::error("ConfigService: StorageService is null");
        return false;
    }
    storage_ = storage;
    initialized_ = true;
    Logger::info("ConfigService initialized");
    return true;
}

// ---- WiFi ----

bool ConfigService::saveWifiConfig(const String& ssid, const String& password) {
    if (!initialized_) return false;
    storage_->setString(KEY_WIFI_SSID, ssid);
    storage_->setString(KEY_WIFI_PASSWORD, password);
    Logger::info("ConfigService WiFi config saved");
    return true;
}

String ConfigService::getWifiSSID() {
    if (!initialized_) return "";
    return storage_->getString(KEY_WIFI_SSID, "");
}

String ConfigService::getWifiPassword() {
    if (!initialized_) return "";
    return storage_->getString(KEY_WIFI_PASSWORD, "");
}

bool ConfigService::hasWifiConfig() {
    if (!initialized_) return false;
    return storage_->exists(KEY_WIFI_SSID)
        && storage_->getString(KEY_WIFI_SSID, "").length() > 0;
}

// ---- Device ----

bool ConfigService::setDeviceName(const String& name) {
    if (!initialized_) return false;
    storage_->setString(KEY_DEVICE_NAME, name);
    return true;
}

String ConfigService::getDeviceName() {
    if (!initialized_) return "SmartDesktop";
    return storage_->getString(KEY_DEVICE_NAME, "SmartDesktop");
}

// ---- Display ----

bool ConfigService::setBrightness(int value) {
    if (!initialized_) return false;
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    storage_->setString(KEY_BRIGHTNESS, String(value));
    return true;
}

int ConfigService::getBrightness() {
    if (!initialized_) return 80;
    String val = storage_->getString(KEY_BRIGHTNESS, "80");
    return val.toInt();
}

// ---- Auto Connect ----

void ConfigService::setAutoConnect(bool enabled) {
    if (!initialized_) return;
    storage_->setString(KEY_AUTO_CONNECT, enabled ? "1" : "0");
}

bool ConfigService::getAutoConnect() {
    if (!initialized_) return true;
    String val = storage_->getString(KEY_AUTO_CONNECT, "1");
    return val == "1";
}

bool ConfigService::isInitialized() const {
    return initialized_;
}
