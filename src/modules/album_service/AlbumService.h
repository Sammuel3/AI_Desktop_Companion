#pragma once

#include <Arduino.h>

/// @brief 相册服务模块 — 管理相册图片列表、当前图片索引和轮播状态。
///
/// 当前阶段先使用占位状态。
/// 后续会基于 SDCardService 扫描 TF 卡图片，并支持手机上传图片。

class AlbumService {
public:
    /// @brief 初始化相册服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新（轮播定时器等）。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief 是否有可用的图片。
    bool hasImages() const;

    /// @brief 获取图片总数。
    int getImageCount() const;

    /// @brief 获取当前图片索引。
    int getCurrentIndex() const;

    /// @brief 获取当前图片路径。
    String getCurrentImagePath() const;

    /// @brief 获取相册状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 切换到下一张图片。
    void nextImage();

    /// @brief 切换到上一张图片。
    void previousImage();

private:
    bool initialized_ = false;
    bool hasImages_ = false;
    int imageCount_ = 0;
    int currentIndex_ = -1;
    String currentImagePath_ = "";
    String statusText_ = "Album: No images";
};
