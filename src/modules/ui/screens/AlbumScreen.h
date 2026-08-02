#pragma once

#include <lvgl.h>
#include "../../album/AlbumService.h"

/// @brief 相册页面 — 显示当前图片信息。
///
/// AlbumScreen 仅通过 AlbumService 读取数据。
/// 不直接访问 SDCardService、StorageService 或任何业务 Service。

class AlbumScreen {
public:
    /// @brief 构造相册页面。
    AlbumScreen();

    /// @brief 初始化并创建 LVGL 控件。
    /// @param albumService AlbumService 指针。
    /// @return true 成功。
    bool begin(AlbumService* albumService);

    /// @brief 刷新显示数据。
    void update();

    /// @brief 显示页面。
    void show();

    /// @brief 隐藏页面。
    void hide();

    /// @brief 是否已初始化。
    bool isInitialized() const;

private:
    AlbumService* albumService_ = nullptr;
    lv_obj_t* screen_ = nullptr;
    lv_obj_t* titleLabel_ = nullptr;
    lv_obj_t* imageLabel_ = nullptr;
    lv_obj_t* pathLabel_ = nullptr;
    bool initialized_ = false;
};
