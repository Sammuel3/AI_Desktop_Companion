#pragma once

#include <Arduino.h>

/// @brief 日志模块 — 封装串口日志输出。
///
/// 当前阶段仅支持 Serial 输出。
/// 后续可扩展为抽象接口，支持文件日志、网络日志、分级过滤等。
class Logger {
public:
    /// @brief 初始化日志输出（打开串口）。
    static void begin(unsigned long baudRate);

    /// @brief 输出 INFO 级别日志。
    static void info(const String& message);

    /// @brief 输出 WARN 级别日志。
    static void warn(const String& message);

    /// @brief 输出 ERROR 级别日志。
    static void error(const String& message);
};
