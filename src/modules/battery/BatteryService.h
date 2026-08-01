#pragma once

#include <Arduino.h>

/// @brief 电池服务模块 — 维护电池电量与充电状态。
///
/// BatteryService 当前采用硬件抽象设计，默认值供电。
/// 保留未来 ESP32 ADC / 电池管理 IC / GPIO 充电检测扩展点。
/// 不负责 UI 显示、SystemStatusManager、电源管理策略。

class BatteryService {
public:
    /// @brief 初始化电池服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新电池状态。
    void update();

    /// @brief 获取电池电量百分比。
    /// @return 0-100 百分比值。
    int getPercentage() const;

    /// @brief 是否正在充电。
    /// @return true 充电中，false 未充电。
    bool isCharging() const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    int percentage_ = 100;
    bool charging_ = false;
};
