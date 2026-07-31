#include "StorageService.h"
#include "../logger/Logger.h"

bool StorageService::begin() {
    initialized_ = preferences_.begin(NAMESPACE, false);
    if (initialized_) {
        Logger::info("StorageService initialized (NVS)");
    } else {
        Logger::error("StorageService failed to open NVS");
    }
    return initialized_;
}

bool StorageService::setString(const String& key, const String& value) {
    if (!initialized_) {
        return false;
    }
    size_t written = preferences_.putString(key.c_str(), value);
    return written > 0;
}

String StorageService::getString(const String& key, const String& defaultValue) {
    if (!initialized_) {
        return defaultValue;
    }
    return preferences_.getString(key.c_str(), defaultValue);
}

bool StorageService::exists(const String& key) {
    if (!initialized_) {
        return false;
    }
    return preferences_.isKey(key.c_str());
}
