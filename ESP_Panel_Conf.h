/*
 * ESP32_Display_Panel Configuration for JC8048W550C
 *
 * ST7262 RGB 800x480 panel + backlight + GT911 touch.
 */
#ifndef ESP_PANEL_CONF_H
#define ESP_PANEL_CONF_H

/* Use custom board (not a pre-defined Espressif board) */
#define ESP_PANEL_USE_SUPPORTED_BOARD   (0)

/*-------------------------------- LCD Related --------------------------------*/
#define ESP_PANEL_USE_LCD                   (1)

/* LCD IC: ST7262, 800x480, RGB bus */
#define ESP_PANEL_LCD_NAME                  ST7262
#define ESP_PANEL_LCD_H_RES                 (800)
#define ESP_PANEL_LCD_V_RES                 (480)
#define ESP_PANEL_LCD_BUS_TYPE              (3)     /* RGB */
#define ESP_PANEL_LCD_BUS_SKIP_INIT_HOST    (1)     /* No separate 3-wire SPI */

/* RGB clock & timing (JC8048W550-C3774) */
#define ESP_PANEL_LCD_RGB_CLK_HZ            (16 * 1000 * 1000)
#define ESP_PANEL_LCD_RGB_HPW               (4)
#define ESP_PANEL_LCD_RGB_HBP               (8)
#define ESP_PANEL_LCD_RGB_HFP               (8)
#define ESP_PANEL_LCD_RGB_VPW               (4)
#define ESP_PANEL_LCD_RGB_VBP               (8)
#define ESP_PANEL_LCD_RGB_VFP               (8)
#define ESP_PANEL_LCD_RGB_PCLK_ACTIVE_NEG   (1)
#define ESP_PANEL_LCD_RGB_DATA_WIDTH        (16)

/* RGB control pins */
#define ESP_PANEL_LCD_RGB_IO_DE             (40)
#define ESP_PANEL_LCD_RGB_IO_VSYNC          (41)
#define ESP_PANEL_LCD_RGB_IO_HSYNC          (39)
#define ESP_PANEL_LCD_RGB_IO_PCLK           (42)
#define ESP_PANEL_LCD_RGB_IO_DISP           (-1)

/* RGB DATA0~DATA15 (RGB565: D0-4=B, D5-10=G, D11-15=R) */
#define ESP_PANEL_LCD_RGB_IO_DATA0          (8)
#define ESP_PANEL_LCD_RGB_IO_DATA1          (3)
#define ESP_PANEL_LCD_RGB_IO_DATA2          (46)
#define ESP_PANEL_LCD_RGB_IO_DATA3          (9)
#define ESP_PANEL_LCD_RGB_IO_DATA4          (1)
#define ESP_PANEL_LCD_RGB_IO_DATA5          (5)
#define ESP_PANEL_LCD_RGB_IO_DATA6          (6)
#define ESP_PANEL_LCD_RGB_IO_DATA7          (7)
#define ESP_PANEL_LCD_RGB_IO_DATA8          (15)
#define ESP_PANEL_LCD_RGB_IO_DATA9          (16)
#define ESP_PANEL_LCD_RGB_IO_DATA10         (4)
#define ESP_PANEL_LCD_RGB_IO_DATA11         (45)
#define ESP_PANEL_LCD_RGB_IO_DATA12         (48)
#define ESP_PANEL_LCD_RGB_IO_DATA13         (47)
#define ESP_PANEL_LCD_RGB_IO_DATA14         (21)
#define ESP_PANEL_LCD_RGB_IO_DATA15         (14)

/* LCD color & transform */
#define ESP_PANEL_LCD_COLOR_BITS            (16)
#define ESP_PANEL_LCD_COLOR_SPACE           (0)     /* 0=RGB, 1=BGR */
#define ESP_PANEL_LCD_SWAP_XY               (0)
#define ESP_PANEL_LCD_MIRROR_X              (0)
#define ESP_PANEL_LCD_MIRROR_Y              (0)
#define ESP_PANEL_LCD_INVERT_COLOR          (0)
#define ESP_PANEL_LCD_INEVRT_COLOR          ESP_PANEL_LCD_INVERT_COLOR   /* library typo compat */

/* LCD reset */
#define ESP_PANEL_LCD_IO_RST                (-1)
#define ESP_PANEL_LCD_RST_LEVEL             (0)

/*-------------------------------- LCD Touch Related --------------------------*/
#define ESP_PANEL_USE_LCD_TOUCH             (1)
#define ESP_PANEL_LCD_TOUCH_NAME            GT911
#define ESP_PANEL_LCD_TOUCH_BUS_TYPE        (0)     /* I2C */
#define ESP_PANEL_LCD_TOUCH_BUS_HOST_ID     (0)
#define ESP_PANEL_LCD_TOUCH_I2C_IO_SCL      (20)
#define ESP_PANEL_LCD_TOUCH_I2C_IO_SDA      (19)
#define ESP_PANEL_LCD_TOUCH_IO_RST          (38)
#define ESP_PANEL_LCD_TOUCH_IO_INT          (-1)
#define ESP_PANEL_LCD_TOUCH_H_RES           (800)
#define ESP_PANEL_LCD_TOUCH_V_RES           (480)
#define ESP_PANEL_LCD_TOUCH_SWAP_XY         (0)
#define ESP_PANEL_LCD_TOUCH_MIRROR_X        (0)
#define ESP_PANEL_LCD_TOUCH_MIRROR_Y        (0)

/*-------------------------------- Backlight Related --------------------------*/
#define ESP_PANEL_USE_BL                    (1)
#define ESP_PANEL_LCD_IO_BL                 (2)
#define ESP_PANEL_LCD_BL_LEVEL              (1)     /* High = on */
#define ESP_PANEL_LCD_BL_ON_LEVEL           ESP_PANEL_LCD_BL_LEVEL
#define ESP_PANEL_LCD_BL_USE_PWM            (0)

/*-------------------------------- Others -------------------------------------*/
#define ESP_PANEL_CHECK_RESULT_ASSERT       (1)

#endif /* ESP_PANEL_CONF_H */
