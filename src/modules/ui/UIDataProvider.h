#pragma once

#include <Arduino.h>
#include "../system_status/SystemStatusManager.h"

/// @brief UI 数据提供层 — 从 SystemStatusManager 读取状态并格式化为 UI 就绪的文本。
///
/// UIDataProvider 仅访问 SystemStatusManager，不直接访问任何业务 Service。
/// 负责数据格式化，不负责 LVGL 控件创建或 UI 布局。

class UIDataProvider {
public:
    /// @brief 初始化并绑定 SystemStatusManager。
    /// @param statusManager SystemStatusManager 指针。
    /// @return true 成功。
    bool begin(SystemStatusManager* statusManager);

    /// @brief 从 SystemStatusManager 刷新缓存数据。
    void update();

    /// @brief 获取格式化的电池文本。
    /// @return 如 "80%"。
    String getBatteryText();

    /// @brief 获取格式化的天气描述文本。
    /// @return 如 "Sunny"。
    String getWeatherText();

    /// @brief 获取格式化的温度文本。
    /// @return 如 "26.5°C"。
    String getTemperatureText();

    /// @brief 获取格式化的时间文本。
    /// @return 如 "14:30"。
    String getTimeText();

    /// @brief 获取格式化的 WiFi 状态文本。
    /// @return "WiFi: Connected" 或 "WiFi: Disconnected"。
    String getWifiText();

private:
    SystemStatusManager* statusManager_ = nullptr;
    SystemStatus cachedStatus_;
};
