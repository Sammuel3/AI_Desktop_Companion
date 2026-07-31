#pragma once

#include "../touch/TouchManager.h"
#include "UIManager.h"

/// @brief UI 事件管理器 — 连接 TouchManager 输入与 UIManager 页面切换。
///
/// UIEventManager 监听触摸事件并触发页面切换。
/// 不直接访问 GT911 硬件、LVGL 控件或业务 Service。

class UIEventManager {
public:
    /// @brief 初始化并绑定 TouchManager 和 UIManager。
    /// @param touchManager TouchManager 指针。
    /// @param uiManager UIManager 指针。
    /// @return true 成功。
    bool begin(TouchManager* touchManager, UIManager* uiManager);

    /// @brief 周期性检查触摸事件并触发页面切换。
    void update();

private:
    TouchManager* touchManager_ = nullptr;
    UIManager* uiManager_ = nullptr;
    bool wasTouched_ = false;
};
