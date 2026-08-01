#pragma once

#include <Arduino.h>

/// @brief Web 服务模块 — 管理 HTTP Server 生命周期。
///
/// WebServerService 负责服务器启动/停止和状态管理。
/// 当前为框架占位，不包含真实 HTTP 实现。
/// 不访问 WiFiService、SystemStatusManager、UIManager、LVGL 或任何业务 Service。

class WebServerService {
public:
    /// @brief 构造 Web 服务。
    WebServerService();

    /// @brief 初始化 Web 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 启动服务器（占位）。
    /// @return true 成功。
    bool start();

    /// @brief 停止服务器。
    void stop();

    /// @brief 服务器是否正在运行。
    /// @return true 运行中。
    bool isRunning() const;

    /// @brief 获取服务状态 JSON。
    /// @return JSON 状态字符串。
    String getStatusJson() const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    bool running_ = false;
};
