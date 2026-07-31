#pragma once

#include <Arduino.h>

/// @brief 触摸管理模块 — 提供统一的触摸状态查询接口。
///
/// TouchManager 不直接初始化 GT911 硬件。
/// 触摸硬件由 DisplayDriver 通过 ESP32_Display_Panel 统一管理。
/// TouchManager 通过 PanelContext 读取已初始化的触摸数据。

class TouchManager {
public:
    /// @brief 初始化触摸管理器（检测触摸硬件是否就绪）。
    /// @return true 触摸可用，false 不可用。
    bool begin();

    /// @brief 周期性更新触摸状态。
    void update();

    /// @brief 当前是否有触摸按下。
    /// @return true 有触摸，false 无触摸。
    bool isTouched() const;

    /// @brief 获取当前触摸点 X 坐标。
    /// @return X 坐标（仅在 isTouched() 为 true 时有效）。
    int getX() const;

    /// @brief 获取当前触摸点 Y 坐标。
    /// @return Y 坐标（仅在 isTouched() 为 true 时有效）。
    int getY() const;

private:
    bool initialized_ = false;
    bool touched_ = false;
    int x_ = 0;
    int y_ = 0;
};
