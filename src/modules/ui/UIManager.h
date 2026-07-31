#pragma once

#include <Arduino.h>
#include "UIDataProvider.h"
#include "screens/HomeScreen.h"

/// @brief UI 管理模块 — 负责 UI 生命周期管理与页面切换入口。
///
/// UIManager 管理 HomeScreen 等 LVGL 页面，调度 UI 更新。

class UIManager {
public:
    /// @brief 初始化 UI 系统并创建默认页面。
    /// @param provider UIDataProvider 指针。
    /// @return true 成功。
    bool begin(UIDataProvider* provider);

    /// @brief 周期性更新 UI（刷新当前页面）。
    void update();

    /// @brief 切换到主屏幕。
    void showHome();

    /// @brief 刷新当前页面。
    void refresh();

    /// @brief 获取当前页面名称。
    /// @return 当前页面名称字符串。
    const char* getCurrentScreen() const;

    /// @brief UI 系统是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    const char* currentScreen_ = "None";
    HomeScreen homeScreen_;
};
