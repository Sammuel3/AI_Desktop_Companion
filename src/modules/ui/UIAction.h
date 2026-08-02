#pragma once

/// @brief UI 动作枚举 — 表示用户在菜单中触发的操作。
enum class UIAction {
    NONE,
    OPEN_WEATHER,
    OPEN_ALBUM,
    OPEN_SETTINGS,
    OPEN_NOTIFICATION,
    OPEN_TIME,
    OPEN_MEMO,
    OPEN_ABOUT
};

/// @brief UI 动作管理器 — 存储当前待处理的 UI 动作。
///
/// UIActionManager 仅负责动作的存储与查询。
/// 不执行业务逻辑、页面切换或服务调用。

class UIActionManager {
public:
    /// @brief 设置当前动作。
    /// @param action 待处理的 UI 动作。
    void setAction(UIAction action);

    /// @brief 获取当前动作。
    /// @return 当前 UI 动作。
    UIAction getAction() const;

    /// @brief 清除当前动作。
    void clearAction();

private:
    UIAction currentAction_ = UIAction::NONE;
};
