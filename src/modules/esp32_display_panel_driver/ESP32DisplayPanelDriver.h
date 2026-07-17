#pragma once

#include <Arduino.h>

/// @brief ESP32_Display_Panel 显示驱动适配模块 — 基于 ESP32_Display_Panel 驱动 JC8048W550-C3774 RGB 屏。
///
/// 当前 .h 只定义接口，不直接引入 ESP32_Display_Panel。
/// .cpp 阶段才会引入真实库并创建面板对象。
/// 后续将使用 BoardConfig 中的官方 RGB 引脚和时序参数。

class ESP32DisplayPanelDriver {
public:
    /// @brief 初始化 ESP32_Display_Panel 显示驱动（创建 RGB 面板、配置时序等）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新（帧刷新、VSYNC 同步等）。
    void update();

    /// @brief 检查显示驱动是否已成功初始化。
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
};
