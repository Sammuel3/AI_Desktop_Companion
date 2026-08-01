#include "TimeService.h"
#include "../logger/Logger.h"
#include <sys/time.h>

bool TimeService::begin() {
    initialized_ = true;
    valid_ = false;
    timeString_ = "00:00";
    Logger::info("TimeService initialized");
    return true;
}

void TimeService::update() {
    if (!initialized_) {
        return;
    }

    struct tm timeInfo;
    if (getLocalTime(&timeInfo)) {
        char buf[6];
        snprintf(buf, sizeof(buf), "%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min);
        timeString_ = String(buf);
        valid_ = true;
    } else {
        valid_ = false;
    }
}

String TimeService::getTimeString() const {
    if (!valid_) {
        return "--:--";
    }
    return timeString_;
}

bool TimeService::isValid() const {
    return valid_;
}
