#pragma once

#include <Arduino.h>

/// @brief 时间服务模块 — 基于 ESP32 系统时间提供当前时间。
///
/// TimeService 使用 configTime / getLocalTime API 获取系统时间。
/// 不负责 NTP 同步、RTC 管理、UI 显示。

class TimeService {
public:
    /// @brief 初始化时间服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（刷新系统时间）。
    void update();

    /// @brief 获取当前时间字符串。
    /// @return HH:MM 格式，无效时返回 "--:--"。
    String getTimeString() const;

    /// @brief 时间是否有效。
    /// @return true 有效，false 未同步或无效。
    bool isValid() const;

private:
    bool initialized_ = false;
    bool valid_ = false;
    String timeString_ = "00:00";
};
