#pragma once
#include <TFT_eSPI.h>
#include "brain.h"

class Face {
public:
    void begin();
    void update(Brain &brain);

private:
    TFT_eSPI tft;

    float blink = 1.0;
    float pupilX = 0;
    float pupilY = 0;

    void drawFace(Brain &b);
    void updatePhysics(Brain &b);
};