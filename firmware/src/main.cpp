#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#include "brain.h"
#include "Face.h"

// -------------------- PIN --------------------
#define TFT_CS   10
#define TFT_DC    8
#define TFT_RST   9
#define TFT_MOSI 11
#define TFT_SCLK 12

// -------------------- SPI --------------------
SPIClass spi(FSPI);

// -------------------- DISPLAY --------------------
Adafruit_ST7789 tft(&spi, TFT_CS, TFT_DC, TFT_RST);

// -------------------- LOGIC --------------------
Brain brain;
Face face(tft);   // 👈 SOLO QUESTA

void setup() {
    Serial.begin(115200);
    delay(1000);

    spi.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

    face.begin();
    brain.begin();
}

void loop() {
    brain.update();
    face.update(brain);

    delay(40);
}