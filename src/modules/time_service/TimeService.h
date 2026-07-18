#pragma once

#include <Arduino.h>

/// @brief 时间服务模块 — 维护当前时间和日期。
///
/// TimeService 不关心时间来源（NTP / RTC / APP 等）。
/// 外部模块通过 refresh() 触发时间更新，TimeService 仅负责存储和提供时间数据。
/// 当前阶段为占位实现，时间字符串返回默认值。

class TimeService {
public:
    /// @brief 初始化时间服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（内部状态维护）。
    void update();

    /// @brief 刷新时间数据。
    ///
    /// 由外部时间源调用，触发时间字符串更新。
    /// 当前占位实现。
    void refresh(const String& timeString, const String& dateString);

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 时间是否有效（已由外部时间源更新）。
    /// @return true 有效，false 无效。
    bool isTimeValid() const;

    /// @brief 获取当前时间字符串。
    /// @return HH:MM 格式的时间字符串（如 "14:30"），无效时返回 "--:--"。
    String getTimeString() const;

    /// @brief 获取当前日期字符串。
    /// @return YYYY/MM/DD 格式的日期字符串（如 "2026/07/18"），无效时返回 "----/--/--"。
    String getDateString() const;

private:
    bool initialized_ = false;
    bool timeValid_ = false;
    String timeString_ = "--:--";
    String dateString_ = "----/--/--";
};
