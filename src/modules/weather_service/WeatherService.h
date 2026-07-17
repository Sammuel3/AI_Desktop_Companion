#pragma once

#include <Arduino.h>

/// @brief 天气服务模块 — 维护天气状态、温度和用于 HomeScreen 显示的天气文本。
///
/// 当前阶段先使用占位天气。
/// 后续会在 WiFi 连接后调用天气 API 获取真实天气。

class WeatherService {
public:
    /// @brief 初始化天气服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（后续天气 API 轮询等）。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief 是否已获取天气数据。
    bool hasWeatherData() const;

    /// @brief 获取天气描述文本（如 "Sunny", "Cloudy" 等）。
    String getWeatherText() const;

    /// @brief 获取温度文本（如 "25°C"）。
    String getTemperatureText() const;

    /// @brief 获取天气状态文本（用于 HomeScreen 显示）。
    String getStatusText() const;

private:
    bool initialized_ = false;
    bool hasWeatherData_ = false;
    String weatherText_ = "--";
    String temperatureText_ = "--°C";
    String statusText_ = "Weather: --";
};
