#pragma once

#include <lvgl.h>
#include "../UIAction.h"

/// @brief 菜单页面 — 基于 LVGL 显示导航菜单，支持点击触发 UIAction。
///
/// MenuScreen 仅依赖 UIActionManager，不访问任何业务 Service、SystemStatusManager 或触摸硬件。

class MenuScreen {
public:
    /// @brief 初始化菜单页面并创建 LVGL 控件。
    /// @param actionManager UIActionManager 指针。
    /// @return true 成功。
    bool begin(UIActionManager* actionManager);

    /// @brief 显示菜单页面（加载 LVGL 屏幕）。
    void show();

    /// @brief 隐藏菜单页面。
    void hide();

    /// @brief 周期性更新（当前为空）。
    void update();

private:
    /// @brief LVGL 点击事件回调。
    static void onItemClicked(lv_event_t* event);

    UIActionManager* actionManager_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* itemWeather_ = nullptr;
    lv_obj_t* itemAlbum_ = nullptr;
    lv_obj_t* itemSettings_ = nullptr;
    lv_obj_t* itemAbout_ = nullptr;
};
