#pragma once

#include <Arduino.h>

/// @brief SD 卡服务模块 — 管理 SD 卡挂载状态与容量信息。
///
/// SDCardService 仅负责 SD 卡初始化、状态检测和容量查询。
/// 不负责 AlbumService、UIManager、LVGL、DisplayDriver 及业务逻辑。

class SDCardService {
public:
    /// @brief 初始化 SD 卡服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（检测 SD 卡插拔等）。
    void update();

    /// @brief SD 卡是否已挂载。
    /// @return true 已挂载，false 未挂载。
    bool isMounted() const;

    /// @brief 获取 SD 卡总容量。
    /// @return 总字节数。
    uint64_t getTotalBytes() const;

    /// @brief 获取 SD 卡已用容量。
    /// @return 已用字节数。
    uint64_t getUsedBytes() const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    bool mounted_ = false;
    uint64_t totalBytes_ = 0;
    uint64_t usedBytes_ = 0;
};
