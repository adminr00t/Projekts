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
#define DATA_PIN 6
#define DATA_PIN2 4
#define NUM_LEDS 104
#define BRIGHTNESS 25
int DO = 2;    //Pin for Digital Output - DO
int DA = 0;    // Pin for Analog Output - AO
int trsh = 35; //Set minimum threshold for LED lit
#pragma endregion

#pragma region Strip Segments and Definitions
CRGB strip1[NUM_LEDS];
#pragma endregion

void setup()
{
    Serial.begin(38400);
    pinMode(2, INPUT);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    // FastLED.setBrightness(BRIGHTNESS);

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

void fadeall1()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(220);
    }
}

void loop()
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    

    int overtrsh = (EMA_S - trsh) >> 1; //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    FastLED.setBrightness(avOvertrsh);
#pragma endregion

#pragma region Color Definitions and LED Limiters
    int color1 = random8();
    int color2 = random8();
    int color3 = random8();
    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
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
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color3, color1, color2);
        fadeall1();
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
#pragma endregion

    FastLED.show();
}