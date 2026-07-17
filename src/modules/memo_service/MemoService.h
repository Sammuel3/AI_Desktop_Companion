#pragma once

#include <Arduino.h>

/// @brief 备忘录服务模块 — 维护当前备忘录标题、内容和更新时间。
///
/// 当前阶段只保存在内存中。
/// 后续会接入手机上传 JSON 和 SDCardService 文件存储。

class MemoService {
public:
    /// @brief 初始化备忘录服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief 是否有备忘录内容。
    bool hasMemo() const;

    /// @brief 获取备忘录标题。
    String getTitle() const;

    /// @brief 获取备忘录内容。
    String getContent() const;

    /// @brief 获取备忘录更新时间。
    String getUpdatedAt() const;

    /// @brief 获取备忘录状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 设置备忘录（标题、内容、更新时间）。
    void setMemo(const char* title, const char* content, const char* updatedAt);

    /// @brief 清空备忘录。
    void clearMemo();

private:
    bool initialized_ = false;
    bool hasMemo_ = false;
    String title_ = "";
    String content_ = "";
    String updatedAt_ = "";
    String statusText_ = "Memo: Empty";
};
