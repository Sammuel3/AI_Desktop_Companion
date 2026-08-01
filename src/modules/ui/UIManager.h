#pragma once

#include <Arduino.h>
#include "UIDataProvider.h"
#include "UIAction.h"
#include "screens/HomeScreen.h"
#include "screens/MenuScreen.h"

/// @brief UI 管理模块 — 负责 UI 生命周期管理与页面切换。
///
/// UIManager 管理 HomeScreen 和 MenuScreen 等 LVGL 页面，调度 UI 更新。
/// 不直接访问任何 Service、Hardware、Touch、Display、SystemStatusManager。

class UIManager {
public:
    /// @brief 屏幕类型枚举。
    enum class ScreenType {
        HOME,
        MENU
    };

    /// @brief 构造 UI 管理器。
    UIManager();

    /// @brief 初始化 UI 系统并创建所有页面。
    /// @param provider UIDataProvider 指针。
    /// @return true 成功。
    bool begin(UIDataProvider* provider);

    /// @brief 周期性更新 UI（刷新当前页面）。
    void update();

    /// @brief 切换到指定屏幕。
    /// @param screen 目标屏幕类型。
    void switchScreen(ScreenType screen);

    /// @brief 获取当前屏幕类型。
    /// @return 当前屏幕类型。
    ScreenType getCurrentScreen() const;

    /// @brief 获取 UIActionManager 指针。
    /// @return UIActionManager 指针。
    UIActionManager* getActionManager();

    /// @brief UI 系统是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    ScreenType currentScreen_ = ScreenType::HOME;
    UIActionManager uiActionManager_;
    HomeScreen homeScreen_;
    MenuScreen menuScreen_;
};
