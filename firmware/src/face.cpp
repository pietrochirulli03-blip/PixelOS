#include "Face.h"
#include <math.h>
#include <Arduino.h>

// =========================
// COSTRUTTORE
// =========================
Face::Face(Adafruit_ST7789 &display)
    : tft(display) {}

// =========================
// INIT DISPLAY
// =========================
void Face::begin() {
    tft.init(240, 320);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);

    Serial.println("Face ready");
}

// =========================
// UPDATE MAIN
// =========================
void Face::update(Brain &brain) {
    updatePhysics(brain);
    drawFace(brain);
}

// =========================
// LOGICA STABILE (FIX)
// =========================
void Face::updatePhysics(Brain &b) {

    // tempo
    float t = millis() * 0.002f;

    // normalizzazione valori brain
    float energy = b.getEnergy() / 100.0f;
    float stress = b.getStress() / 100.0f;
    float curiosity = b.getCuriosity() / 100.0f;

    // =========================
    // BLINK STABILE (NO DRIFT)
    // =========================
    float blinkTarget = 1.0f;

    // blink lento + naturale
    if (sin(millis() * 0.002f) > 0.98f) {
        blinkTarget = 0.25f;
    }

    // smoothing
    blink += (blinkTarget - blink) * 0.15f;

    // =========================
    // PUPILLE (STABILI)
    // =========================
    pupilX = sin(t) * curiosity * 10.0f;
    pupilY = cos(t * 0.7f) * stress * 8.0f;
}

// =========================
// DISEGNO OCCHI
// =========================
void Face::drawFace(Brain &b) {

    tft.fillScreen(ST77XX_BLACK);

    int cx1 = 80;
    int cx2 = 160;
    int cy  = 90;

    // normalizzazione
    float energy = b.getEnergy() / 100.0f;
    float stress = b.getStress() / 100.0f;

    // =========================
    // OPENNESS STABILE
    // =========================
    float openness = blink * energy;

    // stress riduce ma NON distrugge
    openness *= (1.0f - stress * 0.5f);

    // clamp sicurezza
    openness = constrain(openness, 0.35f, 1.0f);

    int eyeW = 40 * openness;
    int eyeH = 55 * openness;

    // =========================
    // OCCHI
    // =========================
    tft.fillRoundRect(cx1, cy, eyeW, eyeH, 10, ST77XX_WHITE);
    tft.fillRoundRect(cx2, cy, eyeW, eyeH, 10, ST77XX_WHITE);

    // =========================
    // PUPILLE
    // =========================
    int px = cx1 + eyeW / 2 + pupilX;
    int py = cy + eyeH / 2 + pupilY;

    int px2 = cx2 + eyeW / 2 + pupilX;
    int py2 = cy + eyeH / 2 + pupilY;

    // nero
    tft.fillCircle(px, py, 6, ST77XX_BLACK);
    tft.fillCircle(px2, py2, 6, ST77XX_BLACK);

    // riflesso
    tft.fillCircle(px + 2, py - 2, 2, ST77XX_WHITE);
    tft.fillCircle(px2 + 2, py2 - 2, 2, ST77XX_WHITE);
}