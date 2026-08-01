#pragma once

#include <lvgl.h>
#include "../UIDataProvider.h"

/// @brief 天气页面 — 显示天气信息。
///
/// WeatherScreen 仅通过 UIDataProvider 读取数据。
/// 不直接访问 WeatherService、SystemStatusManager 或任何业务 Service。

class WeatherScreen {
public:
    /// @brief 构造天气页面。
    WeatherScreen();

    /// @brief 初始化并创建 LVGL 控件。
    /// @param provider UIDataProvider 指针。
    /// @return true 成功。
    bool begin(UIDataProvider* provider);

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
    lv_obj_t* weatherLabel_ = nullptr;
    lv_obj_t* temperatureLabel_ = nullptr;
    bool initialized_ = false;
};
