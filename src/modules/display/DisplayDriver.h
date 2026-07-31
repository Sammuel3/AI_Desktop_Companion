#pragma once

#include <Arduino.h>

/// @brief 显示驱动模块 — 基于 ESP32_Display_Panel 管理 JC8048W550C RGB 屏。
///
/// DisplayDriver 负责 RGB LCD 初始化、GT911 触摸初始化、背光控制。
/// 使用 ESP32_Display_Panel 库封装底层 ST7262 寄存器操作。

class DisplayDriver {
public:
    /// @brief 初始化显示驱动（LCD + 触摸 + 背光）。
    /// @return true 成功，false 失败。
    bool begin();

    /// @brief 设置背光开关。
    /// @param enable true 开启，false 关闭。
    void setBacklight(bool enable);

    /// @brief 显示驱动是否就绪（LCD 已初始化且触摸可用）。
    /// @return true 就绪，false 未就绪。
    bool isReady() const;

    /// @brief 获取屏幕宽度。
    /// @return 宽度（像素）。
    uint16_t getWidth() const;

    /// @brief 获取屏幕高度。
    /// @return 高度（像素）。
    uint16_t getHeight() const;

private:
    bool initialized_ = false;
    bool touchReady_ = false;
    uint16_t width_ = 800;
    uint16_t height_ = 480;
};
