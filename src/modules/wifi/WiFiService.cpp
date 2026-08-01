#include "WiFiService.h"
#include "../logger/Logger.h"
#include <WiFi.h>

bool WiFiService::begin(ConfigService* config) {
    if (config == nullptr) {
        Logger::error("WiFiService: ConfigService is null");
        return false;
    }
    config_ = config;
    WiFi.mode(WIFI_STA);
    initialized_ = true;
    ssid_ = config_->getWifiSSID();
    Logger::info("WiFiService initialized");
    return true;
}

void WiFiService::update() {
    if (!initialized_) {
        return;
    }

    if (WiFi.status() == WL_CONNECTED) {
        if (!connected_) {
            connected_ = true;
            ssid_ = WiFi.SSID();
            Logger::info(String("WiFi connected: ") + ssid_);
        }
    } else {
        connected_ = false;
    }
}

bool WiFiService::connect() {
    if (!initialized_ || config_ == nullptr) {
        return false;
    }
    String ssid = config_->getWifiSSID();
    String password = config_->getWifiPassword();
    if (ssid.length() == 0) {
        Logger::warn("WiFiService: no SSID configured");
        return false;
    }
    WiFi.begin(ssid.c_str(), password.c_str());
    Logger::info(String("WiFi connecting to: ") + ssid);
    return true;
}

bool WiFiService::isConnected() const {
    return connected_;
}

String WiFiService::getSSID() const {
    return connected_ ? ssid_ : "";
}
