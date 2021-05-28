#include <FastLED.h>
#define NumLEDS1   88
#define NumLEDS2  86
#define DataPin1   3
#define DataPin2   4
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 75
#define fps  120
CRGB strip1[NumLEDS1];
CRGB strip2[NumLEDS2];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LEDtype, DataPin1, ColorOrder>(strip1, NumLEDS1);
  FastLED.addLeds<LEDtype, DataPin2, ColorOrder>(strip2, NumLEDS2);
  FastLED.setBrightness(Brightness);
}


void loop(){
  for (int i = 0; i < NumLEDS1; ++i) {
    strip1[i] = CRGB::Yellow;
  }
  for (int i = 0; i < NumLEDS2; ++i){
    strip2 [i]=CRGB::Yellow;
  }
  FastLED.show();
}
