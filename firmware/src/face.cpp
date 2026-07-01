#include "Face.h"
#include <math.h>

void Face::begin() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    Serial.println("Face ready");
}

void Face::update(Brain &brain) {
    updatePhysics(brain);
    drawFace(brain);
}
void Face::updatePhysics(Brain &b) {

    // blinking naturale (lento + random)
    float blinkSpeed = map(b.getEnergy(), 0, 100, 2000, 6000);

    if (millis() % (int)blinkSpeed < 80) {
        blink = 0.2;
    } else {
        blink += (1.0 - blink) * 0.1;
    }

    // pupille vive (curiosità = movimento)
    float t = millis() * 0.002;

    pupilX = sin(t) * (b.getCuriosity() * 0.03);
    pupilY = cos(t * 0.7) * (b.getStress() * 0.02);
}
void Face::drawFace(Brain &b) {

    tft.fillScreen(TFT_BLACK);

    int cx1 = 80;
    int cx2 = 160;
    int cy  = 90;

    float openness = blink * (b.getEnergy() / 100.0);

    // stress = occhi più stretti
    openness -= b.getStress() * 0.003;
    if (openness < 0.2) openness = 0.2;

    int eyeW = 40 * openness;
    int eyeH = 55 * openness;

    // OCCHI SINISTRO
    tft.fillRoundRect(cx1, cy, eyeW, eyeH, 10, TFT_WHITE);

    // OCCHI DESTRO
    tft.fillRoundRect(cx2, cy, eyeW, eyeH, 10, TFT_WHITE);

    // PUPILLE (vive)
    int px = cx1 + eyeW/2 + pupilX;
    int py = cy + eyeH/2 + pupilY;
    int px2 = cx2 + eyeW/2 + pupilX;
    int py2 = cy + eyeH/2 + pupilY;

    tft.fillCircle(px2, py2, 6, TFT_BLACK);
    tft.fillCircle(px2+2, py2-2, 2, TFT_WHITE);

    tft.fillCircle(px, py, 6, TFT_BLACK);
    tft.fillCircle(px+2, py-2, 2, TFT_WHITE);
}