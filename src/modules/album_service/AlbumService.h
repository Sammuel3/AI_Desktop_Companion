#pragma once

#include <Arduino.h>

/// @brief 相册服务模块 — 管理本地相册资源。
///
/// AlbumService 仅负责管理图片资源列表及其状态。
/// 不负责图片解码、渲染、LVGL 显示、SD 卡驱动、文件系统实现。

class AlbumService {
public:
    /// @brief 初始化相册服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 切换到下一张图片。
    /// @return true 切换成功，false 无图片或只有一张图片。
    bool nextImage();

    /// @brief 切换到上一张图片。
    /// @return true 切换成功，false 无图片或只有一张图片。
    bool previousImage();

    /// @brief 选择指定索引的图片。
    /// @param index 图片索引（0-based）。
    /// @return true 成功，false 索引越界或相册未就绪。
    bool selectImage(size_t index);

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief 相册是否已就绪（已扫描到图片）。
    /// @return true 已就绪，false 无图片。
    bool isAlbumReady() const;

    /// @brief 获取图片总数。
    /// @return 图片数量，未就绪时返回 0。
    size_t getImageCount() const;

    /// @brief 获取当前图片索引。
    /// @return 当前索引（0-based），未就绪时返回 0。
    size_t getCurrentIndex() const;

    /// @brief 获取当前图片路径。
    /// @return 路径字符串，未就绪时返回空字符串。
    String getCurrentImagePath() const;

private:
    bool initialized_ = false;
    bool albumReady_ = false;
    size_t currentIndex_ = 0;
    size_t imageCount_ = 0;
    String currentImagePath_ = "";
};
