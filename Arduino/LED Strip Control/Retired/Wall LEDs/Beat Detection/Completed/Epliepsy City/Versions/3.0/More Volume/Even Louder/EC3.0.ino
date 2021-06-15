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
#define NUM_LEDS 88
#define NUM_LEDS2 86
#define BRIGHTNESS 50
int DO = 2;     //Pin for Digital Output - DO
int DA = 0;     // Pin for Analog Output - AO
int trsh = 240; //Set minimum threshold for LEDs
#pragma endregion

#pragma region Strip Segments and Definitions
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

CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];
#pragma endregion

void setup()
{
    Serial.begin(38400);
    pinMode(2, INPUT);
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

void loop()
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);

    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    FastLED.setBrightness(avOvertrsh);
#pragma endregion

#pragma region Color Definitions and LED Limiters
    int color1 = random8(NUM_LEDS) + (69 * 0.2);
    int color2 = random8(NUM_LEDS + NUM_LEDS2);
    int color3 = random8(NUM_LEDS2) + (69 + 50);

    int color4 = random8(100) + (69 * 0.25);
    int color5 = random8() - (69 * 0.5);
    int color6 = random8(120);

    int color7 = random8(NUM_LEDS2);
    int color8 = random8(147);
    int color9 = random8(NUM_LEDS);

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
    Serial.println(overtrsh);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < limit1; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
    }
    for (int i = 11; i < overtrsh && i < limit2; i++)
    {
        strip1[i] = CRGB(color3, color1, color2);
    }
    for (int i = 22; i < overtrsh && i < limit3; i++)
    {
        strip1[i] = CRGB(color2, color3, color1);
    }
    for (int i = 33; i < overtrsh && i < limit4; i++)
    {
        strip1[i] = CRGB(color4, color5, color6);
    }
    for (int i = 44; i < overtrsh && i < limit5; i++)
    {
        strip1[i] = CRGB(color6, color4, color5);
    }
    for (int i = 56; i < overtrsh && i < limit6; i++)
    {
        strip1[i] = CRGB(color5, color6, color4);
    }
    for (int i = 67; i < overtrsh && i < limit7; i++)
    {
        strip1[i] = CRGB(color7, color8, color9);
    }
    for (int i = 78; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color9, color7, color8);
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < limit9; i++)
    {
        strip2[i] = CRGB(color1, color2, color3);
    }
    for (int i = 10; i < overtrsh2 && i < limit10; i++)
    {
        strip2[i] = CRGB(color3, color1, color2);
    }
    for (int i = 21; i < overtrsh2 && i < limit11; i++)
    {
        strip2[i] = CRGB(color2, color3, color1);
    }
    for (int i = 32; i < overtrsh2 && i < limit12; i++)
    {
        strip2[i] = CRGB(color4, color5, color6);
    }
    for (int i = 43; i < overtrsh2 && i < limit13; i++)
    {
        strip2[i] = CRGB(color6, color4, color5);
    }
    for (int i = 54; i < overtrsh2 && i < limit14; i++)
    {
        strip2[i] = CRGB(color5, color6, color4);
    }
    for (int i = 65; i < overtrsh2 && i < limit15; i++)
    {
        strip2[i] = CRGB(color7, color8, color9);
    }
    for (int i = 76; i < overtrsh2 && i < NUM_LEDS; i++)
    {
        strip2[i] = CRGB(color8, color7, color8);
    }
    for (int i = NUM_LEDS - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
    }
#pragma endregion
    FastLED.show();
}