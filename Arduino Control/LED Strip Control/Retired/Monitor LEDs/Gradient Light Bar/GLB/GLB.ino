#include <FastLED.h>
#define NUM_LEDS 78
#define NUM_LEDS2 77
#define DataPin 6
#define DataPin2 7
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 25
#define fps  25
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];


void setup() {
  // put your setup code here, to run once:+
  FastLED.addLeds<LEDtype, DataPin, ColorOrder>(strip1, NUM_LEDS);
  FastLED.addLeds<LEDtype, DataPin2, ColorOrder>(strip2, NUM_LEDS2);
  FastLED.setBrightness(Brightness);
}

void loop()
{
  // put your main code here, to run repeatedly:
  synthRainbow();
  addGlitter(100);
  FastLED.show();
  FastLED.delay(1000 / fps);
}
void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    strip1[random16(NUM_LEDS)] += CRGB::White;
    strip2[random16(NUM_LEDS2)] += CRGB::White;
  }
}

void synthRainbow()
{
  //strip1
  fill_gradient_RGB(strip1, 0, CRGB::Cyan, 55, CRGB::Fuchsia);
  fill_gradient_RGB(strip1, 56, CRGB::Fuchsia, NUM_LEDS, CRGB::Red);

  // strip2
  fill_gradient_RGB(strip2, 0, CRGB::Cyan, 55, CRGB::Fuchsia);
  fill_gradient_RGB(strip2, 56, CRGB::Fuchsia, NUM_LEDS2, CRGB::Red);
}