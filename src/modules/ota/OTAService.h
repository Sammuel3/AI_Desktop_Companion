#pragma once

#include <Arduino.h>

/// @brief OTA 升级服务模块 — 管理固件更新生命周期。
///
/// OTAService 当前为框架占位实现。
/// 不负责 WiFi、WebServer、UI、Display、SystemStatusManager。

class OTAService {
public:
    /// @brief 构造 OTA 服务。
    OTAService();

    /// @brief 初始化 OTA 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 启动 OTA 更新（占位）。
    /// @return true 成功。
    bool startUpdate();

    /// @brief 停止 OTA 更新。
    void stopUpdate();

    /// @brief 是否正在更新。
    /// @return true 更新中。
    bool isUpdating() const;

    /// @brief 获取更新进度。
    /// @return 进度百分比（0-100），当前固定 0。
    int getProgress() const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    bool updating_ = false;
    int progress_ = 0;
};
