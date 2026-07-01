#pragma once
#include <Arduino.h>

class Brain {
public:
    void begin();
    void update();

    float getEnergy() { return energy; }
    float getStress() { return stress; }
    float getCuriosity() { return curiosity; }

private:
    float energy = 80;
    float stress = 10;
    float curiosity = 50;

    // 👇 QUESTA È LA PARTE MANCANTE
    unsigned long lastUpdate = 0;
};