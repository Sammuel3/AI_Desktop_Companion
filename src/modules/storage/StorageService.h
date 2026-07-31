#pragma once

#include <Arduino.h>
#include <Preferences.h>

/// @brief 统一存储抽象层 — 基于 ESP32 NVS (Preferences) 提供键值存储。
///
/// StorageService 封装 Preferences API，提供简化的字符串读写接口。
/// 不负责文件系统、SD 卡、数据库。

class StorageService {
public:
    /// @brief 初始化存储服务（打开 NVS 命名空间）。
    /// @return true 成功。
    bool begin();

    /// @brief 写入字符串键值对。
    /// @param key 键名。
    /// @param value 值。
    /// @return true 写入成功。
    bool setString(const String& key, const String& value);

    /// @brief 读取字符串键值对。
    /// @param key 键名。
    /// @param defaultValue 键不存在时返回的默认值。
    /// @return 键对应的值，或默认值。
    String getString(const String& key, const String& defaultValue = "");

    /// @brief 检查键是否存在。
    /// @param key 键名。
    /// @return true 存在，false 不存在。
    bool exists(const String& key);

private:
    static constexpr const char* NAMESPACE = "storage";
    Preferences preferences_;
    bool initialized_ = false;
};
