#pragma once

#include <lvgl.h>
#include "../UIDataProvider.h"

/// @brief 关于页面 — 显示设备信息。
///
/// AboutScreen 仅通过 UIDataProvider 读取数据。
/// 不访问 ConfigService、StorageService、WiFiService 或任何业务 Service。

class AboutScreen {
public:
    /// @brief 构造关于页面。
    AboutScreen();

    /// @brief 初始化并创建 LVGL 控件。
    /// @param provider UIDataProvider 指针。
    void begin(UIDataProvider* provider);

    /// @brief 刷新显示数据。
    void update();

    /// @brief 显示页面。
    void show();

    /// @brief 隐藏页面。
    void hide();

    /// @brief 是否已初始化。
    bool isInitialized() const;

private:
    UIDataProvider* provider_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* deviceLabel_ = nullptr;
    lv_obj_t* versionLabel_ = nullptr;
    bool initialized_ = false;
};
