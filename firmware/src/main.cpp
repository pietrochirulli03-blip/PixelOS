#include <Arduino.h>
#include "brain.h"
#include "Face.h"

Brain brain;
Face face;

void setup() {
    Serial.begin(115200);
    delay(1000);

    brain.begin();
    face.begin();
}

void loop() {
    brain.update();
   // brain.printStatus();
    face.update(brain);

    delay(40);
}