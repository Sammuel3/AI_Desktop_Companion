#pragma once

#include <Arduino.h>

/// @brief LVGL 适配模块 — 负责 LVGL 初始化、显示 flush 回调、触摸 read 回调与 lv_timer_handler 调度。
///
/// 当前 .h 不直接引入 lvgl.h。
/// .cpp 阶段才会引入 lvgl.h，并通过 PanelContext / TouchManager 或底层驱动连接显示和触摸。
/// PSRAM 已启用，可用于 LVGL 显示缓冲。

class LVGLPort {
public:
    /// @brief 初始化 LVGL 系统（内存分配、显示驱动注册、触摸驱动注册等）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新 LVGL 任务（lv_timer_handler、显示刷新等）。
    void update();

    /// @brief 检查 LVGL 系统是否已成功初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 检查 LVGL 是否已启用（真实 LVGL 库已加载并运行）。
    /// @return true 已启用，false 未启用或仅占位。
    bool isLvglEnabled() const;

    /// @brief 获取 LVGL 屏幕宽度。
    /// @return 宽度（像素）。
    uint16_t getScreenWidth() const;

    /// @brief 获取 LVGL 屏幕高度。
    /// @return 高度（像素）。
    uint16_t getScreenHeight() const;

private:
    bool initialized_ = false;
    bool lvglEnabled_ = false;
    uint16_t screenWidth_ = 800;
    uint16_t screenHeight_ = 480;
};
