#pragma once

#include <Arduino.h>

/// @brief AI 服务模块 — 管理 AI 请求状态与返回结果。
///
/// AIService 当前阶段为框架占位实现。
/// 不负责 HTTP 请求、WebSocket、API Key 管理、JSON 解析、网络连接、UI 显示。

class AIService {
public:
    /// @brief 构造 AI 服务。
    AIService();

    /// @brief 初始化 AI 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 发送 AI 请求（当前占位）。
    /// @param prompt 用户输入文本。
    /// @return true 请求已处理。
    bool request(const String& prompt);

    /// @brief 获取最近一次 AI 回复。
    /// @return 回复文本。
    String getLastResponse() const;

    /// @brief 服务是否已初始化。
    /// @return true 已初始化。
    bool isInitialized() const;

private:
    bool initialized_ = false;
    String lastResponse_ = "";
};
