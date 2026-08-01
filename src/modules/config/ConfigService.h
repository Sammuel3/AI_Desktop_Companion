#pragma once

#include <Arduino.h>
#include "../storage/StorageService.h"

/// @brief 配置服务模块 — 基于 StorageService 管理设备配置。
///
/// ConfigService 封装常用配置项的读写，通过 StorageService 持久化。
/// 不直接访问 Preferences、WiFiService、DisplayDriver 或硬件。

class ConfigService {
public:
    /// @brief 初始化配置服务（加载已有配置）。
    /// @param storage StorageService 指针。
    /// @return true 成功。
    bool begin(StorageService* storage);

    // ---- WiFi 配置 ----

    /// @brief 保存 WiFi 配置。
    /// @param ssid WiFi SSID。
    /// @param password WiFi 密码。
    /// @return true 保存成功。
    bool saveWifiConfig(const String& ssid, const String& password);

    /// @brief 获取 WiFi SSID。
    /// @return SSID 字符串。
    String getWifiSSID();

    /// @brief 获取 WiFi 密码。
    /// @return 密码字符串。
    String getWifiPassword();

    /// @brief 是否有已保存的 WiFi 配置。
    /// @return true 有配置，false 无配置。
    bool hasWifiConfig();

    // ---- 设备配置 ----

    /// @brief 设置设备名称。
    /// @param name 设备名称。
    /// @return true 保存成功。
    bool setDeviceName(const String& name);

    /// @brief 获取设备名称。
    /// @return 设备名称字符串。
    String getDeviceName();

    // ---- 显示配置 ----

    /// @brief 设置亮度值。
    /// @param value 亮度（0-100）。
    /// @return true 保存成功。
    bool setBrightness(int value);

    /// @brief 获取亮度值。
    /// @return 亮度（0-100）。
    int getBrightness();

    // ---- WiFi 自动连接 ----

    /// @brief 设置 WiFi 自动连接开关。
    /// @param enabled true 启用。
    void setAutoConnect(bool enabled);

    /// @brief 获取 WiFi 自动连接状态。
    /// @return true 已启用。
    bool getAutoConnect();

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    static constexpr const char* KEY_WIFI_SSID      = "wifi_ssid";
    static constexpr const char* KEY_WIFI_PASSWORD  = "wifi_password";
    static constexpr const char* KEY_DEVICE_NAME    = "device_name";
    static constexpr const char* KEY_BRIGHTNESS     = "brightness";
    static constexpr const char* KEY_AUTO_CONNECT   = "wifi_auto_connect";

    StorageService* storage_ = nullptr;
    bool initialized_ = false;
};
