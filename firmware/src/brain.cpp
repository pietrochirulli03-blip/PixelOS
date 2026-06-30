#include "brain.h"
#include <Arduino.h>

Brain::Brain() {
    energy = 100;
    curiosity = 50;
    boredom = 0;
}

void Brain::begin() {
    Serial.println("Brain online");
}

void Brain::update() {
    energy--;

    curiosity++;
    if (curiosity > 100) curiosity = 100;

    boredom++;
    if (boredom > 100) boredom = 100;
}

void Brain::printStatus() {
    Serial.print("Energy: ");
    Serial.println(energy);

    Serial.print("Curiosity: ");
    Serial.println(curiosity);

    Serial.print("Boredom: ");
    Serial.println(boredom);

    if (energy < 30) {
        Serial.println("State: tired 😴");
    } else if (curiosity > 70) {
        Serial.println("State: curious 🤖");
    } else {
        Serial.println("State: neutral");
    }

    Serial.println("----------------");
}