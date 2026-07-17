#include "WiFiService.h"
#include "modules/logger/Logger.h"
#include <WiFi.h>

bool WiFiService::begin() {
    initialized_ = true;
    WiFi.mode(WIFI_STA);
    connected_ = false;
    statusText_ = "WiFi: Disconnected";
    localIpString_ = "0.0.0.0";
    ssid_ = "";
    lastReconnectAttempt_ = 0;
    Logger::info("WiFiService initialized");
    return true;
}

bool WiFiService::connect(const char* ssid, const char* password) {
    if (ssid == nullptr || ssid[0] == '\0') {
        Logger::error("WiFi connect failed: empty SSID");
        return false;
    }

    ssid_ = ssid;
    statusText_ = "WiFi: Connecting";
    Logger::info(String("WiFi connecting to: ") + ssid_);

    WiFi.begin(ssid, password);

    // Wait up to 10 seconds for connection
    for (int i = 0; i < 100; i++) {
        delay(100);
        if (WiFi.status() == WL_CONNECTED) {
            connected_ = true;
            localIpString_ = WiFi.localIP().toString();
            statusText_ = "WiFi: Connected";
            Logger::info(String("WiFi connected, IP: ") + localIpString_);
            return true;
        }
    }

    connected_ = false;
    localIpString_ = "0.0.0.0";
    statusText_ = "WiFi: Failed";
    Logger::warn("WiFi connect timeout");
    return false;
}

void WiFiService::update() {
    if (!initialized_) {
        return;
    }

    if (WiFi.status() == WL_CONNECTED) {
        if (!connected_) {
            connected_ = true;
            localIpString_ = WiFi.localIP().toString();
            statusText_ = "WiFi: Connected";
        }
    } else {
        if (connected_) {
            Logger::warn("WiFi disconnected");
        }
        connected_ = false;
        localIpString_ = "0.0.0.0";
        if (ssid_.length() == 0) {
            statusText_ = "WiFi: Disconnected";
        } else {
            statusText_ = "WiFi: Disconnected";
        }
    }
}

bool WiFiService::isInitialized() const {
    return initialized_;
}

bool WiFiService::isConnected() const {
    return connected_;
}

String WiFiService::getStatusText() const {
    return statusText_;
}

String WiFiService::getLocalIpString() const {
    return localIpString_;
}

String WiFiService::getSsid() const {
    return ssid_;
}

int WiFiService::scanNetworks() {
    if (!initialized_) {
        return 0;
    }

    clearScanResults();
    statusText_ = "WiFi: Scanning";
    Logger::info("WiFi scan started");

    int found = WiFi.scanNetworks();
    if (found <= 0) {
        networkCount_ = 0;
        statusText_ = connected_ ? "WiFi: Connected" : "WiFi: Disconnected";
        Logger::warn("WiFi scan found no networks");
        return 0;
    }

    int count = found < MAX_SCAN_RESULTS ? found : MAX_SCAN_RESULTS;
    for (int i = 0; i < count; i++) {
        scanResults_[i].ssid      = WiFi.SSID(i);
        scanResults_[i].rssi      = WiFi.RSSI(i);
        scanResults_[i].encrypted = WiFi.encryptionType(i) != WIFI_AUTH_OPEN;
    }
    networkCount_ = count;

    statusText_ = connected_ ? "WiFi: Connected" : "WiFi: Disconnected";
    Logger::info(String("WiFi scan found: ") + networkCount_);
    return networkCount_;
}

int WiFiService::getNetworkCount() const {
    return networkCount_;
}

WiFiNetworkInfo WiFiService::getNetworkInfo(int index) const {
    if (index < 0 || index >= networkCount_) {
        return { "", 0, false };
    }
    return scanResults_[index];
}

void WiFiService::clearScanResults() {
    networkCount_ = 0;
    for (int i = 0; i < MAX_SCAN_RESULTS; i++) {
        scanResults_[i].ssid      = "";
        scanResults_[i].rssi      = 0;
        scanResults_[i].encrypted = false;
    }
}
