#include <FastLED.h>

#pragma region constants
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;
int red = 0;
int green = 0;
int blue = 0;
int previous_value = 0;
#pragma endregion

#pragma region Variables
#define DATA_PIN 3
#define DATA_PIN2 4
#define OutputPin 9
#define NUM_LEDS 88
#define NUM_LEDS2 86
#define BRIGHTNESS 50
int DO = 2;    //Pin for Digital Output - DO
int DA = 0;    // Pin for Analog Output - AO
int trsh = 25; //Set minimum threshold for LED lit
#pragma endregion

#pragma region Strip Definitions
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];
#pragma endregion

void setup(){
    Serial.begin(38400);
    // pinMode(2, INPUT);
    pinMode(OutputPin, OUTPUT);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
    EMA_S = analogRead(DA);
    
    #pragma region Color Initialization
    LEDS.showColor(CRGB(255, 0, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 255, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 255));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 0));
    #pragma endregion
}

#pragma region Fading
void fadeall1(){
  for (int i = (NUM_LEDS)-1; i >= 0; i--){
    strip1[i].nscale8(215);
  }
}

void fadeall2(){
 for (int i = (NUM_LEDS)-1; i >= 0; i--){
    strip2[i].nscale8(215);
    }
}
#pragma endregion

void loop(){
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    FastLED.setBrightness(avOvertrsh);
    analogWrite(OutputPin, sensorvalue);
#pragma endregion

#pragma region Color Definitions and LED Limiters
    int color1 = random8();
    int color2 = random8();
    int color3 = random8();
    
    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }
    if (overtrsh2 > NUM_LEDS2)
    {
        overtrsh2 = NUM_LEDS2;
    }

    
#pragma endregion

#pragma region Diagnosis
    // Serial.println(overtrsh);
    Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS ; i++){
        strip1[i] = CRGB(color1,color2,color3);
        fadeall1();
    }
        
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--){
        strip1[i] = CRGB::Black;
    }
    
#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++){
        strip2[i] = CRGB(color1, color2, color3);
        fadeall2();
    }
    
    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--){
        strip2[i] = CRGB::Black;
    }
#pragma endregion

    FastLED.show();
}