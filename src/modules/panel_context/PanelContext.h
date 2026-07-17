#pragma once

class ESP_Panel;

/// @brief PanelContext — 统一持有 ESP_Panel 实例。
///
/// Display 和 Touch 驱动都通过 PanelContext 获取同一个 ESP_Panel，
/// 避免多个模块重复创建 ESP_Panel，也避免直接使用 extern 全局变量。

class PanelContext {
public:
    /// @brief 获取全局唯一的 ESP_Panel 实例引用。
    /// @return ESP_Panel 引用。
    static ESP_Panel& getPanel();
};
