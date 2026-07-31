#pragma once

#include <lvgl.h>
#include "../UIDataProvider.h"

/// @brief 主页面 — 基于 LVGL 显示设备状态概览。
///
/// HomeScreen 仅从 UIDataProvider 获取格式化文本，不直接访问任何业务 Service。

class HomeScreen {
public:
    /// @brief 初始化主页面并创建 LVGL 控件。
    /// @param provider UIDataProvider 指针。
    /// @return true 成功。
    bool begin(UIDataProvider* provider);

    /// @brief 周期性刷新显示数据。
    void update();

private:
    UIDataProvider* provider_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* timeLabel_ = nullptr;
    lv_obj_t* weatherLabel_ = nullptr;
    lv_obj_t* temperatureLabel_ = nullptr;
    lv_obj_t* batteryLabel_ = nullptr;
    lv_obj_t* wifiLabel_ = nullptr;
};
