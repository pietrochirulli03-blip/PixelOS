#include "brain.h"
#include <Arduino.h>

void Brain::begin() {
    energy = 80;
    stress = 10;
    curiosity = 50;
    lastUpdate = millis();
}

void Brain::update() {

    float dt = (millis() - lastUpdate) / 1000.0f;
    lastUpdate = millis();

    // =========================
    // ENERGY (stabile)
    // =========================
    energy -= 2.0f * dt;     // consumo base
    energy += 1.0f * dt;     // recupero naturale lento

    // piccolo rumore controllato
    energy += random(-5, 5) * 0.01f;

    energy = constrain(energy, 20, 100);

    // =========================
    // STRESS (dinamico ma NON esplosivo)
    // =========================
    float activity = abs(sin(millis() * 0.001));

    stress += activity * 5.0f * dt;
    stress -= 3.0f * dt; // rilassamento naturale

    stress += random(-3, 3) * 0.02f;

    stress = constrain(stress, 0, 100);

    // =========================
    // CURIOSITY (quasi stabile)
    // =========================
    curiosity += random(-1, 2) * 0.05f;
    curiosity = constrain(curiosity, 10, 100);
}