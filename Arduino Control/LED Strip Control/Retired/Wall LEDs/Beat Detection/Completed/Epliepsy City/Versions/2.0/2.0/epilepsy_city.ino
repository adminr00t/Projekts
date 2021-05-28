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
#define limit1 69
#define limit2 67
#define BRIGHTNESS 50
int DO = 2;    //Pin for Digital Output - DO
int DA = 0;    // Pin for Analog Output - AO
int trsh = 25; //Set minimum threshold for LED lit

//Strip definitions
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];

void setup()
{
  Serial.begin(38400);
  pinMode(2, INPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  EMA_S = analogRead(DA);
}

void loop()
{
  //maths
  sensorvalue = analogRead(DA); //Read the analog value
  EMA_S = (EMA_a * sensorvalue);

  //Defining overtrsh and sets the values to Num of LEDS
  int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
  int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2

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
    strip1[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    red = (red + 1) & 0xFF;
    green = green + (i * 2) & 0xFF;
    blue = (blue + (i * 3)) & 0xFF;
  }
  for (int i = 69; i < overtrsh && i < NUM_LEDS; i++)
  {
    strip1[i] = CRGB::DarkRed;
  }
  for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
  {
    strip1[i] = CRGB(0, 0, 0);
  }

  //colors for strip2
  for (int i = 0; i < overtrsh2 && i < limit2; i++)
  {
    strip2[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    red = (red + 1) & 0xFF;
    green = green + (i * 2) & 0xFF;
    blue = (blue + (i * 3)) & 0xFF;
  }
  for (int i = 67; i < overtrsh && i < NUM_LEDS2; i++)
  {
    strip2[i] = CRGB::DarkRed;
  }
  for (int i = NUM_LEDS2 - 1; i > overtrsh - 1 && i >= 0; i--)
  {
    strip2[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}
