#include <FastLED.h>
#define NumLEDS 109
#define DataPin 3
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 50
#define fps  120
CRGB leds[NumLEDS];
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LEDtype, DataPin, ColorOrder>(leds, NumLEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(Brightness);
}

void loop(){
  for (int i = 0; i < NumLEDS; ++i) {
    leds[i] = CRGB::Yellow;
  }
  FastLED.show();
}
