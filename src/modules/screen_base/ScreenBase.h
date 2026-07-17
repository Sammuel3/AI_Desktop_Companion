#pragma once

/// @brief 页面基类 — 所有页面模块的抽象接口。
///
/// 定义页面生命周期接口：创建、显示、隐藏、更新、销毁。
/// 后续 HomeScreen、AlbumScreen、MemoScreen、ChatScreen 都将继承此基类。
/// 当前阶段不引入 LVGL，仅定义接口规范。

class ScreenBase {
public:
    virtual ~ScreenBase() {}

    /// @brief 初始化页面（创建 UI 元素、注册回调等）。
    /// @return true 成功，false 失败。
    virtual bool begin() = 0;

    /// @brief 显示页面（页面进入前台，visible_ 置为 true）。
    virtual void show() = 0;

    /// @brief 隐藏页面（页面退入后台，visible_ 置为 false）。
    virtual void hide() = 0;

    /// @brief 周期性更新页面（LVGL 任务处理、数据刷新等）。
    virtual void update() = 0;

    /// @brief 获取页面名称标识。
    /// @return 页面名称（如 "Home", "Album", "Memo", "Chat"）。
    virtual const char* getName() const = 0;

    /// @brief 检查页面当前是否可见（前台显示状态）。
    /// @return true 可见，false 不可见。
    bool isVisible() const;

protected:
    bool visible_ = false;
};
