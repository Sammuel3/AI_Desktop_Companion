#include <Arduino.h>
#include "modules/app_controller/AppController.h"

AppController app;

void setup() {
    app.begin();
}

void loop() {
    app.update();
}
