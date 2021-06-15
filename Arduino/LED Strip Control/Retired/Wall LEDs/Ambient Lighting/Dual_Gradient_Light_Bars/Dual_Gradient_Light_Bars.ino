#include <FastLED.h>
#define NumLEDS   88
#define NumLEDS2  86
#define DataPin1   3
#define DataPin2   4
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 50
#define fps  120
CRGB strip1[NumLEDS];
CRGB strip2[NumLEDS2];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LEDtype,DataPin1,ColorOrder>(strip1, NumLEDS);
  FastLED.addLeds<LEDtype,DataPin2,ColorOrder>(strip2, NumLEDS2);
  FastLED.setBrightness(Brightness);
}



void loop() {
  // put your main code here, to run repeatedly:
  synthRainbow();
  addGlitter(100);
  FastLED.show();
  FastLED.delay(1000/fps);
  
}
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    strip1[random16(NumLEDS) ] += CRGB::White;
    strip2[random16(NumLEDS2)] += CRGB::White;
  }
}

void synthRainbow(){
  //strip1
  fill_gradient_RGB(strip1, 0,CRGB::Gold, 32, CRGB::GreenYellow);
  fill_gradient_RGB(strip1, 33,CRGB::YellowGreen,NumLEDS, CRGB::DarkGreen);
  
  //strip2
  fill_gradient_RGB(strip2, 0,CRGB::LightSeaGreen, 50, CRGB::Fuchsia);
  fill_gradient_RGB(strip2, 51,CRGB::Orchid,NumLEDS2, CRGB::Red);
}
