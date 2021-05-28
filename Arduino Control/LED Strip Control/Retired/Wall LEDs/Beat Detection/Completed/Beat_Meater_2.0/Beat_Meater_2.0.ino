#include <FastLED.h>
#define DATA_PIN    2
#define DATA_PIN2   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS   64
#define NUM_LEDS2 116
int DO = 1; //Pin for Digital Output - DO
int DA = 0; // Pin for Analog Output - AO
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];

#define BRIGHTNESS         50
#define FRAMES_PER_SECOND  240
int trsh = 420 + 20; //Set minimum threshold for LED lit
//Max is 810, increments by 4
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;



void setup() {
  Serial.begin(9600);
  pinMode(1, INPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  EMA_S = analogRead(DA);

}
int red = 0;
int green = 0;
int blue = 0;
int previous_value = 0;
void loop() {
  // put your main code here, to run repeatedly:
  sensorvalue = analogRead(DA);  //Read the analog value
  EMA_S = (EMA_a * sensorvalue); //+ ((1 - EMA_a) * EMA_S);
  Serial.println(EMA_S);

  int overtrsh = (EMA_S - trsh) >> 2; //Divides by 4, to find the amount of lights to turn on, limits to 64
  if (overtrsh > 36) {
    overtrsh = overtrsh + 28;
  }
  for (int i = 0; i < overtrsh && i < 64; i++) {
    //255 - ((i >> 3) * 32);
    strip1[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    strip2[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    //leds[i] = CRGB(127, 0, 127);
//    if (i > previous_value && i & 0b10 == 1) {
//      delayMicroseconds(15);
//      FastLED.show();
//    }
  }
  for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--) {
    strip1[i] = CRGB(0, 0, 0);
    strip2[i] = CRGB(0, 0, 0);
  //  if (i < previous_value) {
   //  delayMicroseconds(5);
     // FastLED.show();
    }
    FastLED.show();
  }
//  previous_value = overtrsh;
