#include "WeatherScreen.h"
#include "../../logger/Logger.h"

WeatherScreen::WeatherScreen() {
}

bool WeatherScreen::begin(UIDataProvider* provider) {
    if (provider == nullptr) {
        Logger::error("WeatherScreen: UIDataProvider is null");
        return false;
    }
    provider_ = provider;

    screen_ = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_, lv_color_hex(0x1a1a2e), LV_PART_MAIN);

    // Title
    titleLabel_ = lv_label_create(screen_);
    lv_label_set_text(titleLabel_, "WEATHER");
    lv_obj_set_style_text_color(titleLabel_, lv_color_hex(0x00d4ff), LV_PART_MAIN);
    lv_obj_align(titleLabel_, LV_ALIGN_TOP_MID, 0, 20);

    // Weather description
    weatherLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(weatherLabel_, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(weatherLabel_, LV_ALIGN_CENTER, 0, -20);

    // Temperature
    temperatureLabel_ = lv_label_create(screen_);
    lv_obj_set_style_text_color(temperatureLabel_, lv_color_hex(0xffaa00), LV_PART_MAIN);
    lv_obj_align(temperatureLabel_, LV_ALIGN_CENTER, 0, 20);

    update();
    initialized_ = true;
    Logger::info("WeatherScreen initialized");
    return true;
}

void WeatherScreen::update() {
    if (provider_ == nullptr) return;

    if (weatherLabel_ != nullptr) {
        String w = "Weather: " + provider_->getWeather();
        lv_label_set_text(weatherLabel_, w.c_str());
    }
    if (temperatureLabel_ != nullptr) {
        String t = "Temperature: " + String(provider_->getTemperature(), 1) + "C";
        lv_label_set_text(temperatureLabel_, t.c_str());
    }
}

void WeatherScreen::show() {
    if (screen_ != nullptr) {
        lv_scr_load(screen_);
    }
    Logger::info("WeatherScreen show");
}

void WeatherScreen::hide() {
}

bool WeatherScreen::isInitialized() const {
    return initialized_;
}
