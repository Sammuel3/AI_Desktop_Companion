#include "ConfigService.h"
#include "modules/logger/Logger.h"
#include <Preferences.h>

bool ConfigService::begin() {
    initialized_ = true;
    load();
    Logger::info("ConfigService initialized");
    return true;
}

bool ConfigService::load() {
    Preferences prefs;
    prefs.begin(NVS_NAMESPACE, true);
    wifiSsid_     = prefs.getString(KEY_WIFI_SSID, "");
    wifiPassword_ = prefs.getString(KEY_WIFI_PASSWORD, "");
    deviceName_   = prefs.getString(KEY_DEVICE_NAME, "SmartDesktop");
    brightness_   = prefs.getUChar(KEY_BRIGHTNESS, 80);
    prefs.end();

    if (brightness_ > 100) {
        brightness_ = 80;
    }

    Logger::info("ConfigService loaded");
    return true;
}

bool ConfigService::save() {
    Preferences prefs;
    prefs.begin(NVS_NAMESPACE, false);
    prefs.putString(KEY_WIFI_SSID, wifiSsid_);
    prefs.putString(KEY_WIFI_PASSWORD, wifiPassword_);
    prefs.putString(KEY_DEVICE_NAME, deviceName_);
    prefs.putUChar(KEY_BRIGHTNESS, brightness_);
    prefs.end();

    Logger::info("ConfigService saved");
    return true;
}

bool ConfigService::isInitialized() const {
    return initialized_;
}

void ConfigService::setWifiSsid(const char* ssid) {
    wifiSsid_ = ssid ? ssid : "";
}

void ConfigService::setWifiPassword(const char* password) {
    wifiPassword_ = password ? password : "";
}

String ConfigService::getWifiSsid() const {
    return wifiSsid_;
}

String ConfigService::getWifiPassword() const {
    return wifiPassword_;
}

bool ConfigService::hasWifiConfig() const {
    return wifiSsid_.length() > 0;
}

void ConfigService::clearWifiConfig() {
    wifiSsid_ = "";
    wifiPassword_ = "";
}

void ConfigService::setDeviceName(const char* name) {
    deviceName_ = (name && name[0] != '\0') ? name : "SmartDesktop";
}

String ConfigService::getDeviceName() const {
    return deviceName_;
}

void ConfigService::setBrightness(uint8_t brightness) {
    if (brightness > 100) {
        brightness = 100;
    }
    brightness_ = brightness;
}

uint8_t ConfigService::getBrightness() const {
    return brightness_;
}
