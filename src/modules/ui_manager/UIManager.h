#pragma once

#include "modules/home_screen/HomeScreen.h"

/// @brief 界面管理模块 — 负责界面初始化、页面切换与 UI 更新调度。
///
/// 当前阶段仅定义接口，不实现真实 UI。
/// 后续将接入 LVGL，并管理 Home、Album、Memo、Chat 等页面。

class UIManager {
public:
    /// @brief 初始化 UI 系统（LVGL 初始化、默认页面创建等）。
    /// @return true 初始化成功，false 失败。
    bool begin();

    /// @brief 周期性更新 UI（LVGL 任务处理、动画刷新等）。
    void update();

    /// @brief 切换到主屏幕页面。
    void showHome();

    /// @brief 切换到相册页面。
    void showAlbum();

    /// @brief 切换到备忘录页面。
    void showMemo();

    /// @brief 切换到聊天页面。
    void showChat();

    /// @brief 获取当前页面的名称。
    /// @return 当前页面名称字符串（如 "Home", "Album" 等）。
    const char* getCurrentScreen() const;

    /// @brief 检查 UI 系统是否已成功初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 转发设置 HomeScreen 时间文本。
    void setHomeTimeText(const char* text);

    /// @brief 转发设置 HomeScreen 日期文本。
    void setHomeDateText(const char* text);

    /// @brief 转发设置 HomeScreen WiFi 状态文本。
    void setHomeWifiText(const char* text);

    /// @brief 转发设置 HomeScreen 电池状态文本。
    void setHomeBatteryText(const char* text);

    /// @brief 转发设置 HomeScreen 天气状态文本。
    void setHomeWeatherText(const char* text);

private:
    bool initialized_ = false;
    const char* currentScreen_ = "None";
    HomeScreen homeScreen_;
};
