#pragma once

#include "modules/screen_base/ScreenBase.h"

struct _lv_obj_t;
typedef struct _lv_obj_t lv_obj_t;

/// @brief 主页面模块 — 显示时间、日期、WiFi、电量、天气等概览信息。
///
/// 使用 LVGL 控件创建和更新主页面布局。
/// .h 使用 lv_obj_t 前置声明，避免暴露 LVGL 头文件。
/// .cpp 阶段才会 include lvgl.h。

class HomeScreen : public ScreenBase {
public:
    bool begin() override;
    void show() override;
    void hide() override;
    void update() override;
    const char* getName() const override;

    void setTimeText(const char* text);
    void setDateText(const char* text);
    void setWifiText(const char* text);
    void setBatteryText(const char* text);
    void setWeatherText(const char* text);

private:
    void refreshLabels();

    const char* timeText_     = "--:--";
    const char* dateText_     = "----/--/--";
    const char* wifiText_     = "WiFi: Disconnected";
    const char* batteryText_  = "Battery: --%";
    const char* weatherText_  = "Weather: --";

    lv_obj_t* root_         = nullptr;
    lv_obj_t* titleLabel_   = nullptr;
    lv_obj_t* timeLabel_    = nullptr;
    lv_obj_t* dateLabel_    = nullptr;
    lv_obj_t* wifiLabel_    = nullptr;
    lv_obj_t* batteryLabel_ = nullptr;
    lv_obj_t* weatherLabel_ = nullptr;
};
