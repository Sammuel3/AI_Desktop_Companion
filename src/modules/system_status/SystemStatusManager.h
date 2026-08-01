#pragma once

#include <Arduino.h>

/// @brief 系统状态数据结构。
struct SystemStatus {
    bool wifiConnected = false;
    int batteryLevel = 100;
    bool charging = false;
    String weather = "Unknown";
    float temperature = 0.0f;
    String currentTime = "--:--";
    bool webServerRunning = false;
};

/// @brief 系统状态管理模块 — 集中管理系统各模块的运行状态。
///
/// SystemStatusManager 负责汇总各服务模块状态，提供统一状态查询接口。
/// 只能被动接收数据，不主动访问任何 Service、Display、LVGL、Touch 或硬件。

class SystemStatusManager {
public:
    /// @brief 构造系统状态管理器。
    SystemStatusManager();

    /// @brief 初始化系统状态管理器（设置默认值）。
    void begin();

    /// @brief 周期性更新（保留）。
    void update();

    /// @brief 设置 WiFi 连接状态。
    void setWifiStatus(bool connected);

    /// @brief 设置电池电量。
    void setBatteryLevel(int level);

    /// @brief 设置充电状态。
    void setCharging(bool charging);

    /// @brief 设置当前时间。
    void setTime(const String& time);

    /// @brief 设置天气信息。
    void setWeather(const String& weather, float temperature);

    /// @brief 设置 WebServer 运行状态。
    void setWebServerStatus(bool running);

    /// @brief WiFi 是否已连接。
    bool isWifiConnected() const;

    /// @brief 获取电池电量。
    int getBatteryLevel() const;

    /// @brief 是否正在充电。
    bool isCharging() const;

    /// @brief 获取当前时间。
    String getTime() const;

    /// @brief 获取天气描述。
    String getWeather() const;

    /// @brief 获取温度。
    float getTemperature() const;

    /// @brief 获取完整的系统状态快照。
    SystemStatus getStatus() const;

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    SystemStatus status_;
};
