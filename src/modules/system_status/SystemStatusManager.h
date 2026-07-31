#pragma once

#include <Arduino.h>

/// @brief 系统状态数据结构。
struct SystemStatus {
    bool wifiConnected = false;
    int batteryLevel = 0;
    String weather = "";
    float temperature = 0.0f;
    String currentTime = "";
    bool webServerRunning = false;
};

/// @brief 系统状态管理模块 — 集中管理系统各模块的运行状态。
///
/// SystemStatusManager 负责汇总各服务模块状态，提供统一状态查询接口。
/// 不负责数据采集、网络通信、UI 显示。

class SystemStatusManager {
public:
    /// @brief 初始化系统状态管理器。
    void begin();

    /// @brief 设置 WiFi 连接状态。
    /// @param connected 是否已连接。
    void setWifiStatus(bool connected);

    /// @brief 设置电池电量。
    /// @param level 电量百分比（0-100）。
    void setBatteryLevel(int level);

    /// @brief 设置天气信息。
    /// @param weather 天气描述。
    /// @param temperature 温度（摄氏度）。
    void setWeather(const String& weather, float temperature);

    /// @brief 设置当前时间。
    /// @param time 时间字符串。
    void setTime(const String& time);

    /// @brief 设置 WebServer 运行状态。
    /// @param running 是否正在运行。
    void setWebServerStatus(bool running);

    /// @brief 获取完整的系统状态快照。
    /// @return 当前系统状态。
    SystemStatus getStatus() const;

private:
    SystemStatus status_;
};
