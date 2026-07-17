#pragma once

#include <Arduino.h>

/// @brief SD 卡服务模块 — 管理 TF 卡挂载状态和容量信息。
///
/// 当前阶段先使用占位状态。
/// 后续会基于 BoardConfig::SDCard 引脚接入 SPI SD 卡。

class SDCardService {
public:
    /// @brief 初始化 SD 卡服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（检测 SD 卡插拔等）。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief SD 卡是否已挂载（文件系统可用）。
    bool isMounted() const;

    /// @brief 是否检测到 SD 卡硬件。
    bool isCardAvailable() const;

    /// @brief 获取 SD 卡状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 获取 SD 卡总容量（字节）。
    uint64_t getTotalBytes() const;

    /// @brief 获取 SD 卡已用容量（字节）。
    uint64_t getUsedBytes() const;

private:
    bool initialized_ = false;
    bool mounted_ = false;
    bool cardAvailable_ = false;
    String statusText_ = "SD: Not mounted";
    uint64_t totalBytes_ = 0;
    uint64_t usedBytes_ = 0;
};
