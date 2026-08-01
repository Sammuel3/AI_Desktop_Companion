#pragma once

#include <Arduino.h>

/// @brief 通知服务模块 — 管理系统临时通知消息。
///
/// NotificationService 仅负责通知消息的缓存与查询。
/// 不访问 UI、LVGL、SystemStatusManager 或任何业务 Service。

class NotificationService {
public:
    /// @brief 构造通知服务。
    NotificationService();

    /// @brief 初始化通知服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 发送通知。
    /// @param message 通知消息内容。
    void notify(const String& message);

    /// @brief 获取当前通知消息。
    /// @return 消息字符串，无通知时返回 ""。
    String getMessage() const;

    /// @brief 是否有待处理通知。
    /// @return true 有通知。
    bool hasNotification() const;

    /// @brief 清除当前通知。
    void clear();

    /// @brief 是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    bool available_ = false;
    String message_ = "";
};
