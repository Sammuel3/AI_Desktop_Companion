#include "WeatherService.h"
#include "../logger/Logger.h"

bool WeatherService::begin() {
    initialized_ = true;
    weather_ = "Unknown";
    temperature_ = 0.0f;
    valid_ = false;
    Logger::info("WeatherService initialized");
    return true;
}

void WeatherService::update() {
}

String WeatherService::getWeather() const {
    if (!valid_) {
        return "--";
    }
    return weather_;
}

float WeatherService::getTemperature() const {
    return temperature_;
}

bool WeatherService::isWeatherValid() const {
    return valid_;
}

bool WeatherService::isInitialized() const {
    return initialized_;
}
