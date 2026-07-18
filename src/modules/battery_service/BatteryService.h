#pragma once

#include <Arduino.h>

/// @brief 电池服务模块 — 采集和维护电池状态。
///
/// BatteryService 仅负责获取电池电量、电压和充电状态。
/// 不负责 UI 显示、低电量提醒、自动关机、电源管理策略、充电控制。

class BatteryService {
public:
    /// @brief 初始化电池服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新电池状态（ADC 采样等）。
    void update();

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 电池数据是否有效（ADC 已成功采样）。
    /// @return true 有效，false 无效。
    bool isBatteryValid() const;

    /// @brief 获取电池电量百分比。
    /// @return 0-100 百分比值，无效时返回 0。
    uint8_t getPercentage() const;

    /// @brief 获取电池电压。
    /// @return 电压值（V），无效时返回 0.0f。
    float getVoltage() const;

    /// @brief 是否正在充电。
    /// @return true 充电中，false 未充电。
    bool isCharging() const;

private:
    bool initialized_ = false;
    bool batteryValid_ = false;
    uint8_t percentage_ = 0;
    float voltage_ = 0.0f;
    bool charging_ = false;
};
