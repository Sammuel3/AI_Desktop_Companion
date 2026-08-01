#pragma once

#include <Arduino.h>
#include "../storage/StorageService.h"

/// @brief 备忘录数据结构。
struct Memo {
    String title;
    String content;
    uint32_t timestamp = 0;
};

/// @brief 备忘录服务模块 — 基于 StorageService 管理多条备忘录。
///
/// MemoService 通过 StorageService 持久化，不直接访问 Preferences。
/// 不负责 UI 显示、输入法、触摸处理、网络同步。

class MemoService {
public:
    /// @brief 初始化备忘录服务。
    /// @param storage StorageService 指针。
    /// @return true 成功。
    bool begin(StorageService* storage);

    /// @brief 周期性更新。
    void update();

    /// @brief 添加备忘录。
    /// @param title 标题。
    /// @param content 内容。
    /// @return true 成功，false 已满或未初始化。
    bool addMemo(const String& title, const String& content);

    /// @brief 删除指定索引的备忘录。
    /// @param index 索引（0-based）。
    /// @return true 成功，false 越界。
    bool removeMemo(int index);

    /// @brief 更新指定索引的备忘录。
    /// @param index 索引（0-based）。
    /// @param title 新标题。
    /// @param content 新内容。
    /// @return true 成功，false 越界。
    bool updateMemo(int index, const String& title, const String& content);

    /// @brief 获取备忘录数量。
    /// @return 备忘录数量。
    int getMemoCount() const;

    /// @brief 获取备忘录标题。
    /// @param index 索引。
    /// @return 标题字符串。
    String getMemoTitle(int index) const;

    /// @brief 获取备忘录内容。
    /// @param index 索引。
    /// @return 内容字符串。
    String getMemoContent(int index) const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    static constexpr int MAX_MEMOS = 20;

    void saveCount();
    void saveMemo(int index, const Memo& memo);
    Memo loadMemo(int index) const;
    void compact();

    StorageService* storage_ = nullptr;
    bool initialized_ = false;
};
