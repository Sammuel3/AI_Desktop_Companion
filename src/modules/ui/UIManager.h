#pragma once

#include <Arduino.h>
#include "UIDataProvider.h"
#include "UIAction.h"
#include "../settings/SettingsService.h"
#include "../album/AlbumService.h"
#include "../memo/MemoService.h"
#include "screens/HomeScreen.h"
#include "screens/MenuScreen.h"
#include "screens/SettingsScreen.h"
#include "screens/AboutScreen.h"
#include "screens/WeatherScreen.h"
#include "screens/AlbumScreen.h"
#include "screens/TimeScreen.h"
#include "screens/MemoScreen.h"

/// @brief UI 管理模块 — 负责 UI 生命周期管理与页面切换。
///
/// UIManager 管理所有 LVGL 页面，调度 UI 更新。
/// 不直接访问任何 Service、Hardware、Touch、Display、SystemStatusManager。

class UIManager {
public:
    /// @brief 屏幕类型枚举。
    enum class ScreenType {
        HOME,
        MENU,
        SETTINGS,
        ABOUT,
        WEATHER,
        ALBUM,
        TIME,
        MEMO
    };

    /// @brief 构造 UI 管理器。
    UIManager();

    /// @brief 初始化 UI 系统并创建所有页面。
    /// @param provider UIDataProvider 指针。
    /// @param settings SettingsService 指针。
    /// @param album AlbumService 指针（可选）。
    /// @return true 成功。
    bool begin(UIDataProvider* provider, SettingsService* settings, AlbumService* album = nullptr, MemoService* memo = nullptr);

    /// @brief 周期性更新 UI（刷新当前页面）。
    void update();

    /// @brief 切换到指定屏幕。
    void switchScreen(ScreenType screen);

    /// @brief 获取当前屏幕类型。
    ScreenType getCurrentScreen() const;

    /// @brief 获取 UIActionManager 指针。
    UIActionManager* getActionManager();

    /// @brief UI 系统是否已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    ScreenType currentScreen_ = ScreenType::HOME;
    UIActionManager uiActionManager_;
    HomeScreen homeScreen_;
    MenuScreen menuScreen_;
    SettingsScreen settingsScreen_;
    AboutScreen aboutScreen_;
    WeatherScreen weatherScreen_;
    AlbumScreen albumScreen_;
    MemoScreen memoScreen_;
    TimeScreen timeScreen_;
};
