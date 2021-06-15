#include <FastLED.h>
#define NUM_LEDS   88
#define NUM_LEDS2  86
#define DataPin1   3
#define DataPin2   4
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 25 
#define fps  120
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LEDtype, DataPin1, ColorOrder>(strip1, NUM_LEDS);
  FastLED.addLeds<LEDtype, DataPin2, ColorOrder>(strip2, NUM_LEDS2);
  FastLED.setBrightness(Brightness);
}

void fadeall() {
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1[i].nscale8(250);
    strip2[i].nscale8(250);
  }
}

void loop() {

  //strip1
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1[i] =  CRGB(0, 255, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB(0, 154, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {

    strip1 [i] =  CRGB(50, 0, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB(125, 0, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB::Fuchsia;
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB( 255, 0, 77);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB::Red;
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB::DarkRed;
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    strip1 [i] =  CRGB::Black;
    FastLED.show();
    fadeall();
    delay(40);
  }

  //strip2
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB::DarkRed;
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {

    strip2 [i] =  CRGB::Red;
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB(255, 0, 77);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB::Fuchsia;
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB(125, 0, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB(50, 0, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB(0, 154, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB(0, 255, 255);
    FastLED.show();
    fadeall();
    delay(40);
  }
  for (int i = 0; i < NUM_LEDS2; i++) {
    strip2 [i] =  CRGB::Black;
    FastLED.show();
    fadeall();
    delay(40);
    }
  }

