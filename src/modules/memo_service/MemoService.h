#pragma once

#include <Arduino.h>

/// @brief 备忘录服务模块 — 管理备忘录文本数据。
///
/// MemoService 仅负责备忘录数据管理。
/// 不负责 UI 显示、输入法、触摸处理、网络同步、数据库存储、文件系统。

class MemoService {
public:
    /// @brief 初始化备忘录服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 设置备忘录内容。
    /// @param memo 备忘录文本。
    void setMemo(const String& memo);

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 备忘录内容是否有效。
    /// @return true 有效，false 无效或为空。
    bool isMemoValid() const;

    /// @brief 获取备忘录内容。
    /// @return 备忘录文本，未就绪时返回空字符串。
    String getMemo() const;

private:
    bool initialized_ = false;
    bool memoValid_ = false;
    String memo_ = "";
};
