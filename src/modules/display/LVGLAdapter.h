#pragma once

#include <Arduino.h>

/// @brief LVGL 适配模块 — 负责 LVGL 初始化、显示缓冲管理与渲染调度。
///
/// LVGLAdapter 绑定 DisplayDriver，创建 PSRAM 绘制缓冲，
/// 注册 flush / touch 回调，调度 lv_timer_handler。

class LVGLAdapter {
public:
    /// @brief 初始化 LVGL 系统（内存分配、显示驱动注册、触摸驱动注册）。
    /// @return true 成功，false 失败。
    bool begin();

    /// @brief 周期性更新 LVGL 任务（lv_timer_handler）。
    void update();

    /// @brief LVGL 是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    uint16_t screenWidth_ = 800;
    uint16_t screenHeight_ = 480;
};
