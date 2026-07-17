#pragma once

#include <Arduino.h>

/// @brief 配置服务模块 — 集中管理设备配置。
///
/// 当前阶段先保存在内存中。
/// 后续 .cpp 会使用 Preferences 将配置保存到 NVS。
/// WiFi 密码只通过 ConfigService 管理，不应硬编码在 AppController 中。
/// WiFi 密码不应输出到日志。

class ConfigService {
public:
    /// @brief 初始化配置服务（加载已有配置等）。
    /// @return true 成功。
    bool begin();

    /// @brief 加载配置（后续从 NVS 读取）。
    bool load();

    /// @brief 保存配置（后续写入 NVS）。
    bool save();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    // ---- WiFi 配置 ----
    void setWifiSsid(const char* ssid);
    void setWifiPassword(const char* password);
    String getWifiSsid() const;
    String getWifiPassword() const;
    bool hasWifiConfig() const;
    void clearWifiConfig();

    // ---- 设备配置 ----
    void setDeviceName(const char* name);
    String getDeviceName() const;
    void setBrightness(uint8_t brightness);
    uint8_t getBrightness() const;

private:
    // NVS namespace and keys
    static constexpr const char* NVS_NAMESPACE   = "smartdesk";
    static constexpr const char* KEY_WIFI_SSID    = "wifi_ssid";
    static constexpr const char* KEY_WIFI_PASSWORD = "wifi_pass";
    static constexpr const char* KEY_DEVICE_NAME  = "dev_name";
    static constexpr const char* KEY_BRIGHTNESS   = "brightness";

    bool initialized_ = false;
    String wifiSsid_ = "";
    String wifiPassword_ = "";
    String deviceName_ = "SmartDesktop";
    uint8_t brightness_ = 80;
};
