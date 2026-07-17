#include "WeatherService.h"
#include "modules/logger/Logger.h"

bool WeatherService::begin() {
    initialized_ = true;
    hasWeatherData_ = false;
    weatherText_ = "--";
    temperatureText_ = "--°C";
    statusText_ = "Weather: --";
    Logger::info("WeatherService initialized");
    return true;
}

void WeatherService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool WeatherService::isInitialized() const {
    return initialized_;
}

bool WeatherService::hasWeatherData() const {
    return hasWeatherData_;
}

String WeatherService::getWeatherText() const {
    return weatherText_;
}

String WeatherService::getTemperatureText() const {
    return temperatureText_;
}

String WeatherService::getStatusText() const {
    return statusText_;
}
