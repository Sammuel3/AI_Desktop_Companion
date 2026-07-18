#pragma once

#include <Arduino.h>

/// @brief WiFi 服务模块 — 管理 WiFi 连接状态。
///
/// WiFiService 仅负责 WiFi 连接/断开和状态查询。
/// 不负责 UI 显示、天气请求、AI 请求、OTA、WebServer、NTP 等网络业务。
/// 网络业务模块只能读取 WiFiService 状态，不直接管理 WiFi。
/// WiFi 凭证（SSID / 密码）由 ConfigService 提供。

class WiFiService {
public:
    /// @brief 初始化 WiFi 服务（设置 Wi-Fi 模式为 STA）。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（检查连接状态变化）。
    void update();

    /// @brief 连接 WiFi。
    /// @param ssid     WiFi SSID。
    /// @param password WiFi 密码。
    /// @return true 连接成功，false 失败。
    bool connect(const String& ssid, const String& password);

    /// @brief 断开 WiFi 连接。
    void disconnect();

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief WiFi 是否已连接。
    /// @return true 已连接，false 未连接。
    bool isConnected() const;

    /// @brief 获取当前连接的 SSID。
    /// @return SSID 字符串，未连接时返回空字符串。
    String getSSID() const;

    /// @brief 获取本机 IP 地址。
    /// @return IP 地址字符串（如 "192.168.1.100"），未连接时返回 "0.0.0.0"。
    String getIPAddress() const;

private:
    bool initialized_ = false;
    bool connected_ = false;
    String ssid_ = "";
    String ipAddress_ = "0.0.0.0";
};
