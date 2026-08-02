#pragma once

#include <lvgl.h>
#include "../../memo/MemoService.h"

/// @brief 备忘录页面 — 显示备忘录列表。
///
/// MemoScreen 仅通过 MemoService 读取数据。
/// 不直接访问 StorageService 或任何业务 Service。

class MemoScreen {
public:
    /// @brief 构造备忘录页面。
    MemoScreen();

    /// @brief 初始化并创建 LVGL 控件。
    /// @param memoService MemoService 指针。
    void begin(MemoService* memoService);

    /// @brief 刷新显示数据。
    void update();

    /// @brief 显示页面。
    void show();

    /// @brief 隐藏页面。
    void hide();

    /// @brief 是否已初始化。
    bool isInitialized() const;

private:
    MemoService* memoService_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* countLabel_ = nullptr;
    lv_obj_t* memoLabel_ = nullptr;
    bool initialized_ = false;
};
