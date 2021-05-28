//Libraries
#include <FastLED.h>

//constants
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;
int red = 0;
int green = 0;
int blue = 0;
int previous_value = 0;

//Variables
#define DATA_PIN 3
#define DATA_PIN2 4
#define NUM_LEDS 88
#define NUM_LEDS2 86
#define BRIGHTNESS 50
int DO = 2;    //Pin for Digital Output - DO
int DA = 0;    // Pin for Analog Output - AO
int trsh = 50; //Set minimum threshold for LED lit

//doom colors and strip segments
//strip1
#define limit1 12
#define limit2 23
#define limit3 35
#define limit4 46
#define limit5 57
#define limit6 68
#define limit7 81

//strip2
#define limit9 11
#define limit10 22
#define limit11 33
#define limit12 44
#define limit13 55
#define limit14 66
#define limit15 80

//Strip definitions
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];

void setup()
{
  Serial.begin(38400);
  pinMode(2, INPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
  EMA_S = analogRead(DA);
}
void fadeall1()
{
  for (int i = (NUM_LEDS)-1; i >= 0; i--)
  {
    strip1[i].nscale8(220);
  }
}

void loop()
{
  //maths
  sensorvalue = analogRead(DA); //Read the analog value
  EMA_S = (EMA_a * sensorvalue);

  //Defining overtrsh and sets the values to Num of LEDS
  int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
  int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
  int avOvertrsh = (overtrsh + overtrsh2) >> 2;

  FastLED.setBrightness(avOvertrsh);

  if (overtrsh > NUM_LEDS)
  {
    overtrsh = NUM_LEDS;
  }
  if (overtrsh2 > NUM_LEDS2)
  {
    overtrsh2 = NUM_LEDS2;
  }

  Serial.println(overtrsh);

  //colors for strip 1
  for (int i = 0; i < overtrsh && i < limit1; i++)
  {
    strip1[i] = CRGB(0, 255, 255);
  }
  for (int i = 12; i < overtrsh && i < limit2; i++)
  {
    strip1[i] = CRGB(0, 154, 255);
  }
  for (int i = 23; i < overtrsh && i < limit3; i++)
  {
    strip1[i] = CRGB(50, 0, 255);
  }
  for (int i = 34; i < overtrsh && i < limit4; i++)
  {
    strip1[i] = CRGB(125, 0, 255);
  }
  for (int i = 45; i < overtrsh && i < limit5; i++)
  {
    strip1[i] = CRGB::Fuchsia;
  }
  for (int i = 56; i < overtrsh && i < limit6; i++)
  {
    strip1[i] = CRGB(255, 0, 77);
  }
  for (int i = 67; i < overtrsh && i < limit7; i++)
  {
    strip1[i] = CRGB::Red;
  }
  for (int i = 78; i < overtrsh && i < NUM_LEDS; i++)
  {
    strip1[i] = CRGB::DarkRed;
  }
  for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
  {
    strip1[i] = CRGB(0, 0, 0);
  }

  //colors for strip2
  for (int i = 0; i < overtrsh2 && i < limit9; i++)
  {
    strip2[i] = CRGB(0, 255, 255);
  }
  for (int i = 10; i < overtrsh2 && i < limit10; i++)
  {
    strip2[i] = CRGB(0, 154, 255);
  }
  for (int i = 21; i < overtrsh2 && i < limit11; i++)
  {
    strip2[i] = CRGB(50, 0, 255);
  }
  for (int i = 32; i < overtrsh2 && i < limit12; i++)
  {
    strip2[i] = CRGB(125, 0, 255);
  }
  for (int i = 43; i < overtrsh2 && i < limit13; i++)
  {
    strip2[i] = CRGB::Fuchsia;
  }
  for (int i = 54; i < overtrsh2 && i < limit14; i++)
  {
    strip2[i] = CRGB(255, 0, 77);
  }
  for (int i = 65; i < overtrsh2 && i < limit15; i++)
  {
    strip2[i] = CRGB::Red;
  }
  for (int i = 76; i < overtrsh2 && i < NUM_LEDS; i++)
  {
    strip2[i] = CRGB::DarkRed;
  }
  for (int i = NUM_LEDS - 1; i > overtrsh2 - 1 && i >= 0; i--)
  {
    strip2[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}
