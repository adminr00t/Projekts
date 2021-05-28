#include <FastLED.h>
#define DATA_PIN    3
#define DATA_PIN2 4
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    88
#define NUM_LEDS2   86
int DO = 1; //Pin for Digital Output - DO
int DA = 0; // Pin for Analog Output - AO
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];


#define BRIGHTNESS         50
#define FRAMES_PER_SECOND  60 
int trsh = 27; //Set minimum threshold for LED lit
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
   
  sensorvalue = analogRead(DA);  //Read the analog value
  EMA_S = (EMA_a * sensorvalue); //+ ((1 - EMA_a) * EMA_S);
  Serial.println(EMA_S);

  //defining over threshold
  int overtrsh = (EMA_S - trsh) >> 2; //Divides by 4, to find the amount of lights to turn on, limits to 64
   if (overtrsh > 128){
    overtrsh = overtrsh - 130;
  }
  
  if (overtrsh == 86) {
    overtrsh = overtrsh - 26 ;
  }
  overtrsh = overtrsh << 1;
  if (overtrsh > 72){
    overtrsh = overtrsh - 100;
  }



  //for strip 2
  for (int i = 0; i < overtrsh && i < NUM_LEDS2; i++) {
    //255 - ((i >> 3) * 32)
    strip2[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
    red = (red + 1) & 0xFF;
    green = green + (i * 2) & 0xFF;
    blue = (blue + (i * 3)) & 0xFF;
    if (i > previous_value && i & 0b10 == 1){
      delay(150);
      FastLED.show();
    }
  }

  for (int i = NUM_LEDS2 - 1; i > overtrsh - 1 && i >= 0; i--) {
    strip2[i] = CRGB(0, 0, 0);
  }
  previous_value = overtrsh;
  FastLED.show();

  //strip 1
  synthRainbow();
  addGlitter(80);  
  FastLED.show();
  //FastLED.delay(1000/FRAMES_PER_SECOND);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    strip1[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void synthRainbow(){
  fill_gradient_RGB(strip1,0,CRGB::Cyan, 69, CRGB::Fuchsia);
  fill_gradient_RGB(strip1,70 ,CRGB::Orchid, NUM_LEDS, CRGB::Red);
}
