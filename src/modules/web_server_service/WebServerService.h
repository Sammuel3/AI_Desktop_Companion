#pragma once

#include <Arduino.h>

/// @brief Web 服务模块 — 管理 WebServer 服务状态。
///
/// WebServerService 仅负责管理服务状态、提供启动/停止接口。
/// 不负责 HTTP 路由、HTML 页面、WiFi 连接、REST API、JSON 解析、OTA 上传、文件系统、UI 显示。

class WebServerService {
public:
    /// @brief 初始化 Web 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

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
    bool initialized_ = false;
    bool running_ = false;
};
