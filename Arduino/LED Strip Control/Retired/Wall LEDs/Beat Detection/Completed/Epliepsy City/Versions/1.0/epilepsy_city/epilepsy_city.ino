#include <FastLED.h>
#define DATA_PIN    3
#define DATA_PIN2 4
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    88
#define NUM_LEDS2   86
int DO = 2; //Pin for Digital Output - DO
int DA = 0; // Pin for Analog Output - AO
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];


#define BRIGHTNESS         50
#define FRAMES_PER_SECOND  60
int trsh = 25; //Set minimum threshold for LED lit
//Max is 810, increments by 4
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;


void setup() {
  Serial.begin(2000000);
  pinMode(2, INPUT);
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

  sensorvalue = analogRead(DA);  //Read the analog value
  EMA_S = (EMA_a * sensorvalue); //+ ((1 - EMA_a) * EMA_S);
//  Serial.println(EMA_S);

  //defining over-threshold --> edit these values to change beat detection
  int overtrsh = (EMA_S - trsh) >> 1; //Divides by 2
  int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
  if (overtrsh > NUM_LEDS) {
    overtrsh = NUM_LEDS;
  }
  if (overtrsh2 > NUM_LEDS2){
    overtrsh2 = NUM_LEDS2;
  }

  Serial.println(overtrsh);
  
  //colors for strip 1
  for (int i = 0; i < overtrsh && i < NUM_LEDS; i++) {
    //255 - ((i >> 3) * 32)
    // strip1[i] = CRGB(128,0,128);
    strip1[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    red = (red + 1) & 0xFF;
    green = green + (i * 2) & 0xFF;
    blue = (blue + (i * 3)) & 0xFF;
    if (i > previous_value && i & 0b10 == 1) {
      delay(1000);
      FastLED.show();
    }
  }
   for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--) {
    strip1[i] = CRGB(0, 0, 0);
  }

  //colors for strip2
  for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++) {
    //255 - ((i >> 3) * 32)
    // strip2[i] = CRGB(128,0,128);
    strip2[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    red = (red + 1) & 0xFF;
    green = green + (i * 2) & 0xFF;
    blue = (blue + (i * 3)) & 0xFF;
    if (i > previous_value && i & 0b10 == 1) {
      delay(150);
      FastLED.show();
    }
  } 
  for (int i = NUM_LEDS2 - 1; i > overtrsh - 1 && i >= 0; i--) {
    strip2[i] = CRGB(0, 0, 0);
  }

  //misc
  previous_value = overtrsh;
  FastLED.show();
}
