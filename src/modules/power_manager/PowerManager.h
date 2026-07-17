#pragma once

#include <Arduino.h>

/// @brief 电源管理模块 — 维护屏幕开关、用户活动时间和休眠请求状态。
///
/// 当前阶段只做占位状态。
/// 后续会接入触摸活动、BLE/WiFi 距离判断、DisplayManager 背光控制和 ESP32 sleep。

class PowerManager {
public:
    /// @brief 初始化电源管理模块。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（检查空闲超时等）。
    void update();

    /// @brief 模块是否已初始化。
    bool isInitialized() const;

    /// @brief 屏幕是否亮着。
    bool isScreenOn() const;

    /// @brief 是否有休眠请求。
    bool isSleepRequested() const;

    /// @brief 获取电源状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 通知有用户活动（触摸或按键），重置空闲计时。
    void notifyUserActivity();

    /// @brief 请求休眠。
    void requestSleep();

    /// @brief 取消休眠请求。
    void cancelSleepRequest();

    /// @brief 设置屏幕开关状态。
    /// @param on true 开启屏幕，false 关闭屏幕。
    void setScreenOn(bool on);

private:
    bool initialized_ = false;
    bool screenOn_ = true;
    bool sleepRequested_ = false;
    unsigned long lastUserActivityMs_ = 0;
    String statusText_ = "Power: Awake";
};
