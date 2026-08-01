#pragma once

#include <Arduino.h>
#include "../config/ConfigService.h"

/// @brief WiFi 服务模块 — 管理 WiFi STA 连接状态。
///
/// WiFiService 从 ConfigService 读取凭证，管理连接生命周期。
/// 不直接访问 SystemStatusManager、UIManager、Display、LVGL。

class WiFiService {
public:
    /// @brief 初始化 WiFi 服务。
    /// @param config ConfigService 指针。
    /// @return true 成功。
    bool begin(ConfigService* config);

    /// @brief 周期性更新（检查连接状态变化）。
    void update();

    /// @brief 使用 ConfigService 凭证连接 WiFi。
    /// @return true 连接请求已发送。
    bool connect();

    /// @brief WiFi 是否已连接。
    /// @return true 已连接，false 未连接。
    bool isConnected() const;

    /// @brief 获取当前连接的 SSID。
    /// @return SSID 字符串，未连接时返回空字符串。
    String getSSID() const;

private:
    ConfigService* config_ = nullptr;
    bool initialized_ = false;
    bool connected_ = false;
    String ssid_ = "";
};
