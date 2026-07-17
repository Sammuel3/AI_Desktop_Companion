#pragma once

#include <Arduino.h>

/// @brief 手机配置页服务模块 — 管理手机 Web 配置页服务状态。
///
/// 当前阶段只做占位状态。
/// 后续会在 WiFi 连接后启动 WebServer，并提供配置页、文件上传和设备设置接口。

class WebServerService {
public:
    /// @brief 初始化 Web 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief WebServer 是否正在运行。
    bool isRunning() const;

    /// @brief 获取监听端口。
    uint16_t getPort() const;

    /// @brief 获取 Web 服务状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 启动 WebServer。
    /// @return true 启动成功。
    bool start();

    /// @brief 停止 WebServer。
    void stop();

private:
    bool initialized_ = false;
    bool running_ = false;
    uint16_t port_ = 80;
    String statusText_ = "Web: Stopped";
};
