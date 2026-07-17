#pragma once

#include <Arduino.h>

/// @brief AI 聊天服务模块 — 维护 AI 聊天请求状态、用户输入和最近一次回复。
///
/// 当前阶段只做占位状态。
/// 后续会在 WiFi 连接后调用中转 API 获取真实回复。
/// API Key 不应硬编码在源码中。

class AIService {
public:
    /// @brief 初始化 AI 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 服务是否已初始化。
    bool isInitialized() const;

    /// @brief AI 是否正在处理请求。
    bool isBusy() const;

    /// @brief 是否有待读取的回复。
    bool hasReply() const;

    /// @brief 获取最近一次用户输入。
    String getLastPrompt() const;

    /// @brief 获取最近一次 AI 回复。
    String getLastReply() const;

    /// @brief 获取 AI 服务状态文本（用于 UI 显示）。
    String getStatusText() const;

    /// @brief 发送消息给 AI。
    /// @param message 用户输入的消息。
    /// @return true 请求已受理，false 当前忙碌或服务未初始化。
    bool sendMessage(const char* message);

    /// @brief 清空对话历史。
    void clearConversation();

private:
    bool initialized_ = false;
    bool busy_ = false;
    bool hasReply_ = false;
    String lastPrompt_ = "";
    String lastReply_ = "";
    String statusText_ = "AI: Idle";
};
