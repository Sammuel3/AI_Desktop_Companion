#include "WiFiService.h"
#include <WiFi.h>

bool WiFiService::begin() {
    WiFi.mode(WIFI_STA);
    initialized_ = true;
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
            ipAddress_ = WiFi.localIP().toString();
        }
    } else {
        connected_ = false;
        ssid_.clear();
        ipAddress_ = "0.0.0.0";
    }
}

bool WiFiService::connect(const String& ssid, const String& password) {
    if (!initialized_) {
        return false;
    }
    if (ssid.length() == 0) {
        return false;
    }

    ssid_ = ssid;
    WiFi.begin(ssid.c_str(), password.c_str());
    return true;
}

void WiFiService::disconnect() {
    WiFi.disconnect();
    connected_ = false;
    ssid_.clear();
    ipAddress_ = "0.0.0.0";
}

bool WiFiService::isInitialized() const {
    return initialized_;
}

bool WiFiService::isConnected() const {
    return connected_;
}

String WiFiService::getSSID() const {
    return connected_ ? ssid_ : "";
}

String WiFiService::getIPAddress() const {
    return ipAddress_;
}
