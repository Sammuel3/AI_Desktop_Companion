#pragma once

/// @brief 硬件配置模块 — 集中管理板级常量和硬件状态。
///
/// 引脚定义基于 JC8048W550-C3774 官方 Demo / HAL。
/// 后续逐步补充屏幕、触摸、SD卡、背光、电池等引脚定义。

namespace BoardConfig {

    // ============================================================
    // 项目标识
    // ============================================================
    constexpr const char* PROJECT_NAME = "SmartDesktop";

    // ============================================================
    // 串口
    // ============================================================
    constexpr unsigned long SERIAL_BAUD_RATE = 115200;

    // ============================================================
    // 屏幕参数（JC8048W550C / JC8048W550）
    // ============================================================
    constexpr int SCREEN_WIDTH  = 800;
    constexpr int SCREEN_HEIGHT = 480;

    // ============================================================
    // 显示背光
    // ============================================================
    namespace Display {
        constexpr int BACKLIGHT_PIN = 2;
    }

    // ============================================================
    // RGB 并行接口引脚（ST7262）
    // ============================================================
    namespace RGB {
        constexpr int DE   = 40;
        constexpr int VSYNC = 41;
        constexpr int HSYNC = 39;
        constexpr int PCLK  = 42;
        constexpr int R0 = 45;
        constexpr int R1 = 48;
        constexpr int R2 = 47;
        constexpr int R3 = 21;
        constexpr int R4 = 14;
        constexpr int G0 = 5;
        constexpr int G1 = 6;
        constexpr int G2 = 7;
        constexpr int G3 = 15;
        constexpr int G4 = 16;
        constexpr int G5 = 4;
        constexpr int BLUE0 = 8;
        constexpr int BLUE1 = 3;
        constexpr int BLUE2 = 46;
        constexpr int BLUE3 = 9;
        constexpr int BLUE4 = 1;
    }

    // ============================================================
    // RGB 时序参数（ST7262, 800x480）
    // ============================================================
    namespace RGBTiming {
        constexpr int HSYNC_POLARITY    = 0;
        constexpr int HSYNC_FRONT_PORCH = 8;
        constexpr int HSYNC_PULSE_WIDTH = 4;
        constexpr int HSYNC_BACK_PORCH  = 8;
        constexpr int VSYNC_POLARITY    = 0;
        constexpr int VSYNC_FRONT_PORCH = 8;
        constexpr int VSYNC_PULSE_WIDTH = 4;
        constexpr int VSYNC_BACK_PORCH  = 8;
        constexpr int PCLK_ACTIVE_NEG   = 1;
        constexpr int PREFER_SPEED      = 16000000;
    }

    // ============================================================
    // 触摸 I2C 引脚（GT911）
    // ============================================================
    namespace Touch {
        constexpr int SDA        = 19;
        constexpr int SCL        = 20;
        constexpr int RST        = 38;
        constexpr int INT        = -1;
        constexpr int GT911_ADDR = 0x5D;
    }

    // ============================================================
    // SD 卡 SPI 引脚
    // ============================================================
    namespace SDCard {
        constexpr int CS   = 10;
        constexpr int MOSI = 11;
        constexpr int MISO = 13;
        constexpr int SCK  = 12;
    }

    // ============================================================
    // 音频 I2S 引脚
    // ============================================================
    namespace Audio {
        constexpr int I2S_DOUT = 17;
        constexpr int I2S_BCLK = 0;
        constexpr int I2S_LRC  = 18;
    }

    // ============================================================
    // Flash / PSRAM 状态说明
    // ============================================================
    //
    // Flash:
    //   实测 Flash 为 16MB。
    //   当前仍使用 default_8MB.csv。
    //   原因: default_16MB.csv 仍会 boot loop。
    //   TODO: 后续需要继续解决 16MB 分区表问题。
    //
    // PSRAM:
    //   已通过 freenove_esp32_s3_wroom 板级配置成功启用。
    //   psramFound() = true。
    //   ESP.getPsramSize() ≈ 8MB。
    //   后续 LVGL / RGB 屏显示缓冲可以使用 PSRAM。
    //
    // ============================================================

} // namespace BoardConfig
