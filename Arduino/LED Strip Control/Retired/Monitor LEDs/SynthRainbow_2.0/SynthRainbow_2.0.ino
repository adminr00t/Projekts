#include <FastLED.h>
#define NumLEDS 104
#define DataPin1 6
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 50
#define fps 25
CRGB leds[NumLEDS];

void setup()
{
  // put your setup code here, to run once:
  FastLED.addLeds<LEDtype, DataPin1, ColorOrder>(leds, NumLEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(Brightness);
}
void fadeall(){
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i].nscale8(250);
  }
}
void loop(){

  //backwards loop (<--)
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB(0, 255, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB(0, 154, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {

    leds[i] = CRGB(50, 0, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB(125, 0, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB::Fuchsia;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB(255, 0, 77);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB::Red;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB::DarkRed;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = (NumLEDS)-1; i >= 0; i--)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }

  //Forwards loop (-->)
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }

  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB::DarkRed;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {

    leds[i] = CRGB::Red;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB(255, 0, 77);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB::Fuchsia;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB(125, 0, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB(50, 0, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB(0, 154, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB(0, 255, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
  for (int i = 0; i < NumLEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    fadeall();
    FastLED.delay(1000/fps);
  }
}
