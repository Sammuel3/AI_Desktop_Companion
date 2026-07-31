#pragma once

#include "UIAction.h"

/// @brief UI 动作分发器 — 读取 UIActionManager 中的动作并执行。
///
/// UIActionDispatcher 仅依赖 UIActionManager。
/// 不访问 MenuScreen、HomeScreen、LVGL 控件、TouchManager 或业务 Service。

class UIActionDispatcher {
public:
    /// @brief 初始化并绑定 UIActionManager。
    /// @param actionManager UIActionManager 指针。
    /// @return true 成功。
    bool begin(UIActionManager* actionManager);

    /// @brief 周期性读取并处理待处理动作。
    void update();

private:
    UIActionManager* actionManager_ = nullptr;
};
