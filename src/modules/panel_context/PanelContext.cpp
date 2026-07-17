#include "PanelContext.h"
#include "ESP_Panel.h"

static ESP_Panel panel;

ESP_Panel& PanelContext::getPanel() {
    return panel;
}
