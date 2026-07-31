#pragma once

#include <Arduino.h>
#include <WebServer.h>
#include "../system_status/SystemStatusManager.h"

/// @brief Web 服务模块 — 管理 WebServer 服务状态并提供 REST API。
///
/// WebServerService 负责管理 WebServer 生命周期、注册 API 路由。
/// 不负责 WiFi 连接、OTA 上传、文件系统、UI 显示。

class WebServerService {
public:
    /// @brief 初始化 Web 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（处理 HTTP 请求）。
    void update();

    /// @brief 注入 SystemStatusManager 依赖。
    /// @param manager 系统状态管理器引用。
    void setSystemStatusManager(SystemStatusManager& manager);

    /// @brief 启动 WebServer。
    /// @return true 启动成功，false 未初始化。
    bool start();

    /// @brief 停止 WebServer。
    void stop();

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief WebServer 是否正在运行。
    /// @return true 运行中，false 已停止。
    bool isRunning() const;

private:
    /// @brief 处理 GET /api/status 请求。
    void handleStatus();

    bool initialized_ = false;
    bool running_ = false;
    WebServer* server_ = nullptr;
    SystemStatusManager* statusManager_ = nullptr;
};
