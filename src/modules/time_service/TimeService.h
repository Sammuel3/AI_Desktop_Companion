#pragma once

#include <Arduino.h>

/// @brief 时间服务模块 — 维护当前时间和日期字符串。
///
/// 当前阶段使用占位时间。
/// 后续将接入 WiFi / NTP 获取真实时间。

class TimeService {
public:
    /// @brief 初始化时间服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（后续 NTP 同步等）。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief 时间是否有效（已同步或手动设置）。
    bool isTimeValid() const;

    /// @brief 获取当前时间字符串（HH:MM 格式）。
    String getTimeString() const;

    /// @brief 获取当前日期字符串（YYYY/MM/DD 格式）。
    String getDateString() const;

private:
    bool initialized_ = false;
    bool timeValid_ = false;
    String timeString_ = "--:--";
    String dateString_ = "----/--/--";
};
