#pragma once

#include <Arduino.h>

/// @brief AI 服务模块 — 管理 AI 请求状态与返回结果。
///
/// AIService 仅负责管理 AI 请求状态、保存返回结果、提供统一调用接口。
/// 不负责 HTTP 请求、WebSocket、API Key 管理、JSON 解析、网络连接、UI 显示、语音输入输出。

class AIService {
public:
    /// @brief 初始化 AI 服务。
    /// @return true 成功。
    bool begin();

    /// @brief 周期性更新。
    void update();

    /// @brief 发送 AI 请求。
    /// @param input 用户输入文本。
    /// @return true 请求已受理，false 忙碌或未初始化。
    bool request(const String& input);

    /// @brief 服务是否已初始化。
    /// @return true 已初始化，false 未初始化。
    bool isInitialized() const;

    /// @brief AI 是否正在处理请求。
    /// @return true 忙碌中，false 空闲。
    bool isBusy() const;

    /// @brief AI 返回结果是否有效。
    /// @return true 有效，false 无效或已过期。
    bool isResponseValid() const;

    /// @brief 获取 AI 返回结果。
    /// @return 返回文本，无效时返回空字符串。
    String getResponse() const;

    /// @brief 清除当前 AI 返回结果。
    void clearResponse();

private:
    bool initialized_ = false;
    bool busy_ = false;
    bool responseValid_ = false;
    String input_ = "";
    String response_ = "";
};
