#pragma once

#include <lvgl.h>
#include "../../settings/SettingsService.h"

/// @brief 设置页面 — 基于 LVGL 显示和管理用户设置。
///
/// SettingsScreen 通过 SettingsService 读写配置并持久化到 ConfigService。
/// 不直接访问任何业务 Service 或硬件。

class SettingsScreen {
public:
    /// @brief 初始化设置页面并创建 LVGL 控件。
    /// @param settings SettingsService 指针。
    /// @return true 成功。
    bool begin(SettingsService* settings);

    /// @brief 显示页面。
    void show();

    /// @brief 隐藏页面。
    void hide();

    /// @brief 周期性刷新显示数据。
    void update();

private:
    SettingsService* settings_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* brightnessLabel_ = nullptr;
    lv_obj_t* deviceLabel_ = nullptr;
    lv_obj_t* autoConnectLabel_ = nullptr;
};
