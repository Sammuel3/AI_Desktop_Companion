#include "TimeService.h"
#include "modules/logger/Logger.h"

bool TimeService::begin() {
    initialized_ = true;
    timeValid_ = false;
    timeString_ = "--:--";
    dateString_ = "----/--/--";
    Logger::info("TimeService initialized");
    return true;
}

void TimeService::update() {
    // 当前保持空实现，不输出周期日志。
}

bool TimeService::isInitialized() const {
    return initialized_;
}

bool TimeService::isTimeValid() const {
    return timeValid_;
}

String TimeService::getTimeString() const {
    return timeString_;
}

String TimeService::getDateString() const {
    return dateString_;
}
