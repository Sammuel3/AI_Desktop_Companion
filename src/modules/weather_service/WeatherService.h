#pragma once

#include <Arduino.h>

/// @brief 天气服务模块 — 维护天气数据。
///
/// WeatherService 仅负责保存和提供天气信息。
/// 不负责 WiFi、HTTP 请求、JSON 解析、UI 显示、定时同步。
/// 网络模块通过 refresh() 更新天气数据。

class WeatherService {
public:
    /// @brief 初始化天气服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 刷新天气数据。
    /// @param weather     天气描述（如 "Sunny", "Cloudy"）。
    /// @param temperature 温度（摄氏度）。
    /// @param icon        天气图标或类型标识。
    /// @param updateTime  数据更新时间字符串。
    void refresh(const String& weather,
                 float temperature,
                 const String& icon,
                 const String& updateTime);

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 天气数据是否有效。
    /// @return true 有效，false 无效。
    bool isWeatherValid() const;

    /// @brief 获取天气描述。
    /// @return 天气字符串，无效时返回 "--"。
    String getWeather() const;

    /// @brief 获取温度。
    /// @return 温度值（摄氏度），无效时返回 0.0f。
    float getTemperature() const;

    /// @brief 获取天气图标/类型标识。
    /// @return 图标字符串，无效时返回 ""。
    String getWeatherIcon() const;

    /// @brief 获取数据更新时间。
    /// @return 更新时间字符串，无效时返回 ""。
    String getUpdateTime() const;

private:
    bool initialized_ = false;
    bool weatherValid_ = false;
    String weather_ = "--";
    float temperature_ = 0.0f;
    String weatherIcon_ = "";
    String updateTime_ = "";
};
