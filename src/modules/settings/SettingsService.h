#pragma once

#include <Arduino.h>
#include "../config/ConfigService.h"

/// @brief 设置服务模块 — 用户设置管理，基于 ConfigService 持久化。
///
/// SettingsService 封装常用用户设置的读写，通过 ConfigService 持久化。
/// 不访问 UI、LVGL、直接存储或任何硬件。

class SettingsService {
public:
    /// @brief 构造设置服务。
    SettingsService();

    /// @brief 初始化设置服务。
    /// @param config ConfigService 指针。
    /// @return true 成功。
    bool begin(ConfigService* config);

    /// @brief 周期性更新。
    void update();

    /// @brief 设置亮度。
    /// @param value 亮度值（0-100），自动 clamp。
    void setBrightness(int value);

    /// @brief 获取亮度。
    /// @return 亮度值。
    int getBrightness() const;

    /// @brief 设置设备名称。
    /// @param name 设备名称。
    void setDeviceName(const String& name);

    /// @brief 获取设备名称。
    /// @return 设备名称字符串。
    String getDeviceName() const;

    /// @brief 设置 WiFi 自动连接。
    /// @param enabled true 启用。
    void setAutoConnect(bool enabled);

    /// @brief 是否启用 WiFi 自动连接。
    /// @return true 已启用。
    bool isAutoConnectEnabled() const;

    /// @brief 是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    ConfigService* configService_ = nullptr;
    bool initialized_ = false;
    int brightness_ = 80;
    String deviceName_ = "SmartDesktop";
    bool autoConnect_ = true;
};
