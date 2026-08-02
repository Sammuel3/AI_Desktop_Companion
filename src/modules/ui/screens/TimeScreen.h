#pragma once

#include <lvgl.h>
#include "../UIDataProvider.h"

/// @brief 时间页面 — 显示系统当前时间。
///
/// TimeScreen 仅通过 UIDataProvider 读取数据。
/// 不直接访问 TimeService、SystemStatusManager 或任何业务 Service。

class TimeScreen {
public:
    TimeScreen();

    bool begin(UIDataProvider* provider);

    void update();
    void show();
    void hide();
    bool isInitialized() const;

private:
    UIDataProvider* provider_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* timeLabel_ = nullptr;
    bool initialized_ = false;
};
