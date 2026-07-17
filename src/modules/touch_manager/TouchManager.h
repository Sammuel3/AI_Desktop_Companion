#pragma once

#include <Arduino.h>
#include "modules/gt911_touch_driver/GT911TouchDriver.h"

/// @brief 触摸管理模块 — 负责触摸芯片初始化、触摸状态读取与坐标管理。
///
/// 当前阶段通过 GT911TouchDriver 适配 ESP32_Display_Panel GT911 触摸驱动。

class TouchManager {
public:
    /// @brief 初始化触摸芯片（供电、配置寄存器）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新触摸状态（读取触摸点坐标和按下状态）。
    void update();

    /// @brief 检查当前是否有触摸按下。
    /// @return true 有触摸按下，false 无触摸。
    bool isTouched() const;

    /// @brief 获取当前触摸点 X 坐标。
    /// @return X 坐标值（仅在 isTouched() 为 true 时有效）。
    uint16_t getX() const;

    /// @brief 获取当前触摸点 Y 坐标。
    /// @return Y 坐标值（仅在 isTouched() 为 true 时有效）。
    uint16_t getY() const;

    /// @brief 检查触摸芯片是否已成功初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    bool touched_ = false;
    uint16_t x_ = 0;
    uint16_t y_ = 0;
    GT911TouchDriver touchDriver_;
};
