#include "FastLED.h"
#define NUM_LEDS 82
CRGB leds[NUM_LEDS];
#define PIN 3

void setup()
{
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}

void loop() {
  FadeInOut(4,185,244);
}

void FadeInOut(int red, int green, int blue){
  float r, g, b;
     
  for(int k = 0; k < 256; k=k+1) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    FastLED.showColor(CRGB(r,g,b));
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    FastLED.showColor(CRGB(r,g,b));
  }

    for (int i = 64; i < NUM_LEDS; i++)
    {
        leds[i] = CRGB::DarkRed;
    }




}