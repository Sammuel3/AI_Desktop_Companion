#pragma once

#include <Arduino.h>

/// @brief OTA 升级服务模块 — 维护 OTA 升级服务状态、升级进度和启用状态。
///
/// 当前阶段只做占位状态。
/// 后续会在 WiFi 连接后接入 ArduinoOTA 或 Web OTA。
/// OTA 不应在未联网或未授权时自动开启。

class OTAService {
public:
    /// @brief 初始化 OTA 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（处理 OTA 请求等）。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief OTA 是否已启用。
    bool isEnabled() const;

    /// @brief 是否正在 OTA 升级中。
    bool isUpdating() const;

    /// @brief 获取升级进度（0-100）。
    uint8_t getProgress() const;

    /// @brief 获取 OTA 状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 设置 OTA 启用状态。
    /// @param enabled true 启用，false 禁用。
    void setEnabled(bool enabled);

private:
    bool initialized_ = false;
    bool enabled_ = false;
    bool updating_ = false;
    uint8_t progress_ = 0;
    String statusText_ = "OTA: Disabled";
};
