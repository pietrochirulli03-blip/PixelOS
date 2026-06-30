#include <Arduino.h>
#include "brain.h"

Brain brain;

void setup() {
    Serial.begin(115200);
    delay(1000);

    brain.begin();
}

void loop() {
    brain.update();
    brain.printStatus();

    delay(2000);
}