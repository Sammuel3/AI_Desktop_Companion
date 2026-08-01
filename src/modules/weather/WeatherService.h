#pragma once

#include <Arduino.h>

/// @brief 天气服务模块 — 维护天气数据。
///
/// WeatherService 仅负责保存和提供天气信息。
/// 当前阶段使用占位数据，保留未来 API 接入扩展点。
/// 不负责 WiFi、HTTP 请求、JSON 解析、UI 显示。

class WeatherService {
public:
    /// @brief 初始化天气服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 获取天气描述。
    /// @return 天气字符串，无效时返回 "--"。
    String getWeather() const;

    /// @brief 获取温度。
    /// @return 温度值（摄氏度）。
    float getTemperature() const;

    /// @brief 天气数据是否有效。
    /// @return true 有效，false 无效。
    bool isWeatherValid() const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    bool valid_ = false;
    String weather_ = "Unknown";
    float temperature_ = 0.0f;
};
