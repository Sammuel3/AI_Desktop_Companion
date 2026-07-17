#pragma once

#include <Arduino.h>

/// @brief GT911 触摸驱动适配模块 — 基于 ESP32_Display_Panel / GT911 读取触摸状态。
///
/// 当前 .h 只定义接口。
/// .cpp 阶段将使用 BoardConfig 中的 SDA/SCL/RST/INT/地址配置初始化 GT911。
/// 暂不接入 LVGL。

class GT911TouchDriver {
public:
    /// @brief 初始化 GT911 触摸芯片（I2C 配置、校准等）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新触摸状态（读取触摸点坐标和按下状态）。
    void update();

    /// @brief 检查触摸驱动是否已成功初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 检查当前是否有触摸按下。
    /// @return true 有触摸按下，false 无触摸。
    bool isTouched() const;

    /// @brief 获取当前触摸点 X 坐标。
    /// @return X 坐标值（仅在 isTouched() 为 true 时有效）。
    uint16_t getX() const;

    /// @brief 获取当前触摸点 Y 坐标。
    /// @return Y 坐标值（仅在 isTouched() 为 true 时有效）。
    uint16_t getY() const;

private:
    bool initialized_ = false;
    bool touched_ = false;
    uint16_t x_ = 0;
    uint16_t y_ = 0;
};
