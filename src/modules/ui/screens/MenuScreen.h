#pragma once

#include <lvgl.h>

/// @brief 菜单页面 — 基于 LVGL 显示导航菜单。
///
/// MenuScreen 仅负责菜单页面布局与显示。
/// 不访问任何业务 Service、SystemStatusManager 或触摸硬件。

class MenuScreen {
public:
    /// @brief 初始化菜单页面并创建 LVGL 控件。
    /// @return true 成功。
    bool begin();

    /// @brief 显示菜单页面（加载 LVGL 屏幕）。
    void show();

    /// @brief 隐藏菜单页面。
    void hide();

    /// @brief 周期性更新（当前为空）。
    void update();

private:
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* itemWeather_ = nullptr;
    lv_obj_t* itemAlbum_ = nullptr;
    lv_obj_t* itemSettings_ = nullptr;
    lv_obj_t* itemAbout_ = nullptr;
};
