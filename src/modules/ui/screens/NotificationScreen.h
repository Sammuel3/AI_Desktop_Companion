#pragma once

#include <lvgl.h>
#include "../UIDataProvider.h"

/// @brief 通知页面 — 显示系统通知。
///
/// NotificationScreen 仅通过 UIDataProvider 读取数据。
/// 不直接访问 NotificationService 或任何业务 Service。

class NotificationScreen {
public:
    NotificationScreen();

    bool begin(UIDataProvider* provider);

    void update();
    void show();
    void hide();
    bool isInitialized() const;

private:
    UIDataProvider* provider_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* countLabel_ = nullptr;
    lv_obj_t* messageLabel_ = nullptr;
    bool initialized_ = false;
};
