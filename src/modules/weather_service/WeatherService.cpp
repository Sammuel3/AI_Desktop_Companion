#include "WeatherService.h"

bool WeatherService::begin() {
    initialized_ = true;
    return true;
}

void WeatherService::update() {
}

void WeatherService::refresh(const String& weather,
                              float temperature,
                              const String& icon,
                              const String& updateTime) {
    weather_ = weather;
    temperature_ = temperature;
    weatherIcon_ = icon;
    updateTime_ = updateTime;
    weatherValid_ = true;
}

bool WeatherService::isInitialized() const {
    return initialized_;
}

bool WeatherService::isWeatherValid() const {
    return weatherValid_;
}

String WeatherService::getWeather() const {
    if (!weatherValid_) {
        return "--";
    }
    return weather_;
}

float WeatherService::getTemperature() const {
    if (!weatherValid_) {
        return 0.0f;
    }
    return temperature_;
}

String WeatherService::getWeatherIcon() const {
    if (!weatherValid_) {
        return "";
    }
    return weatherIcon_;
}

String WeatherService::getUpdateTime() const {
    if (!weatherValid_) {
        return "";
    }
    return updateTime_;
}
