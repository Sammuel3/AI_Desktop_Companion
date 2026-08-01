#pragma once

#include <Arduino.h>

/// @brief 电源状态枚举。
enum class PowerState {
    ACTIVE,
    SLEEPING
};

/// @brief 电源管理模块 — 管理设备电源生命周期与亮度控制。
///
/// PowerManager 仅管理电源状态和亮度值。
/// 不直接访问 DisplayDriver、LVGL、TouchManager、WiFiService 或硬件 GPIO。

class PowerManager {
public:
    /// @brief 初始化电源管理器。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（当前为空，保留用于兼容）。
    void update();

    /// @brief 设置亮度等级。
    /// @param level 亮度值（0-100），自动 clamp。
    void setBrightness(int level);

    /// @brief 获取当前亮度。
    /// @return 亮度值（0-100）。
    int getBrightness() const;

    /// @brief 进入休眠模式。
    void enterSleep();

    /// @brief 从休眠模式唤醒。
    void wakeUp();

    /// @brief 是否处于休眠状态。
    /// @return true 休眠中，false 活跃。
    bool isSleeping() const;

    /// @brief 模块是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    PowerState state_ = PowerState::ACTIVE;
    int brightness_ = 80;
};
