#pragma once

#include <Arduino.h>
#include "../sdcard/SDCardService.h"
#include <vector>

/// @brief 相册服务模块 — 管理本地相册图片资源。
///
/// AlbumService 负责图片文件扫描、列表维护和索引管理。
/// 不负责图片解码、渲染、LVGL 显示、UIManager、TouchManager。

class AlbumService {
public:
    /// @brief 初始化相册服务。
    /// @param sdCard SDCardService 指针。
    /// @return true 成功。
    bool begin(SDCardService* sdCard);

    /// @brief 周期性更新。
    void update();

    /// @brief 扫描 /album/ 目录中的图片文件。
    /// @return true 扫描成功，false SD 卡未挂载或目录不存在。
    bool scanImages();

    /// @brief 获取图片总数。
    /// @return 图片数量。
    int getImageCount() const;

    /// @brief 获取指定索引的图片路径。
    /// @param index 图片索引（0-based）。
    /// @return 路径字符串，越界返回空字符串。
    String getImagePath(int index) const;

    /// @brief 获取当前图片路径。
    /// @return 当前路径字符串，无图片时返回空字符串。
    String getCurrentImagePath() const;

    /// @brief 切换到下一张图片。
    void nextImage();

    /// @brief 切换到上一张图片。
    void previousImage();

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    static constexpr const char* ALBUM_DIR = "/album";
    bool isImageFile(const String& name) const;

    SDCardService* sdCard_ = nullptr;
    bool initialized_ = false;
    std::vector<String> images_;
    int currentIndex_ = 0;
};
