#pragma once

#include <Arduino.h>

/// @brief 单个 WiFi 扫描结果信息。
struct WiFiNetworkInfo {
    String ssid;
    int32_t rssi;
    bool encrypted;
};

/// @brief WiFi 服务模块 — 负责 WiFi 状态维护和后续联网连接。
///
/// 当前阶段只提供占位状态。
/// 后续将接入 WiFi 配置、连接和断线重连。
/// connect() 用于连接指定 WiFi，密码应来自配置模块，不应硬编码。
/// scanNetworks() 用于扫描附近 WiFi，最多保存 10 个结果。

class WiFiService {
public:
    /// @brief 初始化 WiFi 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（连接状态检查、重连等）。
    void update();

    /// @brief 连接到指定 WiFi 网络。
    /// @param ssid     WiFi SSID。
    /// @param password WiFi 密码。
    /// @return true 连接成功，false 失败。
    bool connect(const char* ssid, const char* password);

    /// @brief 扫描附近 WiFi 网络。
    /// @return 实际扫描到的网络数量。
    int scanNetworks();

    /// @brief 获取上次扫描结果的数量。
    int getNetworkCount() const;

    /// @brief 获取指定索引的扫描结果。
    /// @param index 结果索引 (0 ~ getNetworkCount()-1)。
    /// @return WiFiNetworkInfo，越界时返回空结果。
    WiFiNetworkInfo getNetworkInfo(int index) const;

    /// @brief 清除扫描结果。
    void clearScanResults();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief WiFi 是否已连接。
    bool isConnected() const;

    /// @brief 获取 WiFi 状态文本（用于 HomeScreen 显示）。
    String getStatusText() const;

    /// @brief 获取本机 IP 地址字符串。
    String getLocalIpString() const;

    /// @brief 获取当前连接的 SSID。
    String getSsid() const;

private:
    bool initialized_ = false;
    bool connected_ = false;
    String statusText_ = "WiFi: Disconnected";
    String localIpString_ = "0.0.0.0";
    String ssid_ = "";
    unsigned long lastReconnectAttempt_ = 0;

    static constexpr int MAX_SCAN_RESULTS = 10;
    WiFiNetworkInfo scanResults_[MAX_SCAN_RESULTS];
    int networkCount_ = 0;
};
