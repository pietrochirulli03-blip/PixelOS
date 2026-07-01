#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "brain.h"

class Face {
public:
    Face(Adafruit_ST7789 &display); 
    void begin();
    void update(Brain &brain);

private:
   Adafruit_ST7789 &tft;

    float blink = 1.0;
    float pupilX = 0;
    float pupilY = 0;

    void drawFace(Brain &b);
    void updatePhysics(Brain &b);
};