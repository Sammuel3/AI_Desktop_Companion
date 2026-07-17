#pragma once

#include <Arduino.h>

/// @brief 电池服务模块 — 维护电池电量、电压和充电状态。
///
/// 当前阶段先使用占位电量。
/// 后续会接入 ADC 分压采样和充电状态检测。

class BatteryService {
public:
    /// @brief 初始化电池服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（读取 ADC、计算电量等）。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief 是否正在充电。
    bool isCharging() const;

    /// @brief 获取电池电量百分比 (0-100)。
    uint8_t getBatteryPercent() const;

    /// @brief 获取电池电压（V）。
    float getBatteryVoltage() const;

    /// @brief 获取电池状态文本（用于 HomeScreen 显示）。
    String getStatusText() const;

private:
    bool initialized_ = false;
    bool charging_ = false;
    uint8_t batteryPercent_ = 0;
    float batteryVoltage_ = 0.0f;
    String statusText_ = "Battery: --%";
};
