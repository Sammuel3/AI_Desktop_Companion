#pragma once

#include "UIAction.h"

class UIManager;

/// @brief UI 动作分发器 — 读取 UIActionManager 中的动作并分发处理（含页面导航）。
///
/// UIActionDispatcher 依赖 UIActionManager 和 UIManager。
/// 不访问 MenuScreen、HomeScreen、LVGL 控件、TouchManager 或任何 Service。

class UIActionDispatcher {
public:
    /// @brief 构造动作分发器。
    UIActionDispatcher();

    /// @brief 初始化并绑定依赖。
    /// @param actionManager UIActionManager 指针。
    /// @param uiManager UIManager 指针。
    /// @return true 成功。
    bool begin(UIActionManager* actionManager, UIManager* uiManager);

    /// @brief 周期性读取并处理待处理动作。
    void update();

    /// @brief 是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    UIActionManager* actionManager_ = nullptr;
    UIManager* uiManager_ = nullptr;
};
