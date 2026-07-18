#include "TimeService.h"

bool TimeService::begin() {
    initialized_ = true;
    return true;
}

void TimeService::update() {
}

void TimeService::refresh(const String& timeString, const String& dateString) {
    timeString_ = timeString;
    dateString_ = dateString;
    timeValid_ = true;
}

bool TimeService::isInitialized() const {
    return initialized_;
}

bool TimeService::isTimeValid() const {
    return timeValid_;
}

String TimeService::getTimeString() const {
    if (!timeValid_) {
        return "--:--";
    }
    return timeString_;
}

String TimeService::getDateString() const {
    if (!timeValid_) {
        return "----/--/--";
    }
    return dateString_;
}
