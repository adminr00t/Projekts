#include <FastLED.h>
#define DATA_PIN  3
#define DATA_PIN2 4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS1   88
#define NUM_LEDS2   86
#define BRIGHTNESS         100
#define FRAMES_PER_SECOND  60
CRGB strip1 [NUM_LEDS1];
CRGB strip2 [NUM_LEDS2];


int trsh = 420 + 20; //Set minimum threshold for LED lit
//Max is 810, increments by 4
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;


void setup() {
  Serial.begin(9600);
  pinMode(1, INPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}


void loop(){
  for (int i = 0; i < NUM_LEDS1; ++i) {
    // strip1[i] = CRGB(0,213,255);
    strip1[i] = CRGB::White;
  }
  for (int i = 0; i < NUM_LEDS2; ++i){
    // strip2 [i]=CRGB(255, 0, 128);
    strip2[i] = CRGB::White;
  }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
