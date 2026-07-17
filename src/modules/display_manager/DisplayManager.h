#pragma once

#include <Arduino.h>
#include "modules/display_panel_driver/DisplayPanelDriver.h"

/// @brief 显示管理模块 — 负责显示屏初始化、背光亮度控制与显示刷新调度。
///
/// 当前阶段仅定义接口，不实现具体屏幕驱动。
/// 后续将接入 JC8048W550C_I 对应显示驱动和 LVGL。

class DisplayManager {
public:
    /// @brief 初始化显示屏（供电、配置寄存器、设置默认亮度）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新（刷新显示、处理 VSYNC 等）。
    void update();

    /// @brief 设置背光亮度。
    /// @param percent 亮度百分比 (0-100)。
    void setBrightness(uint8_t percent);

    /// @brief 获取当前背光亮度百分比。
    /// @return 亮度百分比 (0-100)。
    uint8_t getBrightness() const;

    /// @brief 检查显示屏是否已成功初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 纯色填充整个屏幕。
    /// @return true 成功，false 失败。
    bool fillScreen(uint8_t r, uint8_t g, uint8_t b);

private:
    bool initialized_ = false;
    uint8_t brightness_ = 100;
    DisplayPanelDriver panelDriver_;
};
