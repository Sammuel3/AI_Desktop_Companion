#pragma once

#include <Arduino.h>
#include "../system_status/SystemStatusManager.h"
#include "../notification/NotificationService.h"

/// @brief UI 数据提供层 — 从 SystemStatusManager 读取状态，提供格式化与原始数据接口。
///
/// UIDataProvider 仅访问 SystemStatusManager，不直接访问任何业务 Service。
/// 不负责 LVGL 控件创建、UI 布局、DisplayDriver 或 TouchManager。

class UIDataProvider {
public:
    /// @brief 构造 UI 数据提供器。
    UIDataProvider();

    /// @brief 初始化并绑定 SystemStatusManager。
    /// @param status SystemStatusManager 指针。
    /// @return true 成功。
    bool begin(SystemStatusManager* status);

    /// @brief 周期性更新（缓存状态用于格式化输出）。
    void update();

    // ---- 直接数据转发 (new) ----

    /// @brief 获取当前时间字符串。
    String getTime() const;

    /// @brief 获取天气描述。
    String getWeather() const;

    /// @brief 获取温度。
    float getTemperature() const;

    /// @brief 获取电池电量。
    int getBatteryLevel() const;

    /// @brief 是否正在充电。
    bool isCharging() const;

    /// @brief WiFi 是否已连接。
    bool isWifiConnected() const;

    /// @brief 获取设备名称。
    String getDeviceName() const;

    /// @brief 注入 NotificationService 依赖。
    void setNotificationService(NotificationService* notification);

    /// @brief 是否有待处理通知。
    bool hasNotification() const;

    /// @brief 获取通知数量。
    int getNotificationCount() const;

    /// @brief 获取最新通知消息。
    String getNotificationMessage() const;

    // ---- 格式化文本 (backward compatible) ----

    /// @brief 获取格式化的电池文本。
    String getBatteryText();

    /// @brief 获取格式化的天气描述文本。
    String getWeatherText();

    /// @brief 获取格式化的温度文本。
    String getTemperatureText();

    /// @brief 获取格式化的时间文本。
    String getTimeText();

    /// @brief 获取格式化的 WiFi 状态文本。
    String getWifiText();

    /// @brief 是否已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    SystemStatusManager* status_ = nullptr;
    NotificationService* notification_ = nullptr;
    SystemStatus cachedStatus_;
};
