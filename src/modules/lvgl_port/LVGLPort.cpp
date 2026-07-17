#include "LVGLPort.h"
#include "modules/logger/Logger.h"
#include "modules/panel_context/PanelContext.h"
#include "ESP_Panel.h"
#include <lvgl.h>
#include "esp_heap_caps.h"

// Display flush callback
static void lvglFlush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {
    ESP_Panel& panel = PanelContext::getPanel();
    if (panel.getLcd() != nullptr) {
        // drawBitmap uses exclusive end: [x1, x2+1) × [y1, y2+1)
        panel.getLcd()->drawBitmap(
            area->x1,
            area->y1,
            area->x2 + 1,
            area->y2 + 1,
            reinterpret_cast<uint16_t*>(color_p)
        );
    }
    lv_disp_flush_ready(disp);
}

// Touch read callback
static void lvglTouchRead(lv_indev_drv_t* indev, lv_indev_data_t* data) {
    ESP_Panel& panel = PanelContext::getPanel();
    ESP_PanelLcdTouch* touch = panel.getLcdTouch();
    if (touch != nullptr) {
        touch->readData();
        if (touch->getTouchState()) {
            TouchPoint p = touch->getPoint(0);
            data->state = LV_INDEV_STATE_PR;
            data->point.x = p.x;
            data->point.y = p.y;
        } else {
            data->state = LV_INDEV_STATE_REL;
        }
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

// Static LVGL objects
static lv_disp_draw_buf_t drawBuf;
static lv_color_t* drawBuf1 = nullptr;
static lv_color_t* drawBuf2 = nullptr;
static lv_disp_drv_t dispDrv;
static lv_indev_drv_t indevDrv;

bool LVGLPort::begin() {
    if (initialized_) {
        return true;
    }

    screenWidth_ = 800;
    screenHeight_ = 480;

    lv_init();

    // Allocate partial PSRAM draw buffers: 800 × 40 = 32000 pixels = 64000 bytes each
    size_t bufSize = screenWidth_ * 40 * sizeof(lv_color_t);
    drawBuf1 = (lv_color_t*)heap_caps_malloc(bufSize, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    drawBuf2 = (lv_color_t*)heap_caps_malloc(bufSize, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);

    if (drawBuf1 == nullptr || drawBuf2 == nullptr) {
        Logger::error("LVGLPort: Failed to allocate PSRAM draw buffers");
        if (drawBuf1) { heap_caps_free(drawBuf1); drawBuf1 = nullptr; }
        if (drawBuf2) { heap_caps_free(drawBuf2); drawBuf2 = nullptr; }
        return false;
    }

    lv_disp_draw_buf_init(&drawBuf, drawBuf1, drawBuf2, bufSize / sizeof(lv_color_t));

    // Init display driver
    lv_disp_drv_init(&dispDrv);
    dispDrv.hor_res = screenWidth_;
    dispDrv.ver_res = screenHeight_;
    dispDrv.flush_cb = lvglFlush;
    dispDrv.draw_buf = &drawBuf;
    lv_disp_drv_register(&dispDrv);

    // Init touch input driver
    lv_indev_drv_init(&indevDrv);
    indevDrv.type = LV_INDEV_TYPE_POINTER;
    indevDrv.read_cb = lvglTouchRead;
    lv_indev_drv_register(&indevDrv);

    initialized_ = true;
    lvglEnabled_ = true;
    Logger::info("LVGLPort initialized");
    return true;
}

void LVGLPort::update() {
    if (!initialized_) {
        return;
    }
    lv_timer_handler();
}

bool LVGLPort::isInitialized() const {
    return initialized_;
}

bool LVGLPort::isLvglEnabled() const {
    return lvglEnabled_;
}

uint16_t LVGLPort::getScreenWidth() const {
    return screenWidth_;
}

uint16_t LVGLPort::getScreenHeight() const {
    return screenHeight_;
}
