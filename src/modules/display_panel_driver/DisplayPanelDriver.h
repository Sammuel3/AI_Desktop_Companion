#pragma once

#include <Arduino.h>
#include "modules/esp32_display_panel_driver/ESP32DisplayPanelDriver.h"

/// @brief 显示面板底层驱动模块 — 负责 LCD 面板初始化和基础绘制接口。
///
/// 当前阶段通过 ESP32DisplayPanelDriver 适配 ESP32_Display_Panel 真实显示库。
/// 后续将接入 JC8048W550C_I / ST7262 RGB 屏真实硬件。

class DisplayPanelDriver {
public:
    /// @brief 初始化 LCD 面板（供电、配置 RGB 时序、分配帧缓冲等）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新（VSYNC 同步、帧刷新等）。
    void update();

    /// @brief 检查 LCD 面板是否已成功初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 获取面板宽度。
    /// @return 宽度（像素）。
    uint16_t getWidth() const;

    /// @brief 获取面板高度。
    /// @return 高度（像素）。
    uint16_t getHeight() const;

    /// @brief 纯色填充整个屏幕。
    /// @param r 红色分量 (0-255)。
    /// @param g 绿色分量 (0-255)。
    /// @param b 蓝色分量 (0-255)。
    /// @return true 填充成功，false 失败。
    bool fillScreen(uint8_t r, uint8_t g, uint8_t b);

private:
    bool initialized_ = false;
    uint16_t width_ = 800;
    uint16_t height_ = 480;
    ESP32DisplayPanelDriver realDriver_;
};
