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
const int numReadings = 10;
int readings[numReadings]; // the readings from the analog input
int readIndex = 0;         // the index of the current reading
int total = 0;             // the running total
int average = 0;           // the average
int inputPin = A5;
#pragma endregion

#pragma region Variables
#define DATA_PIN 4
#define DATA_PIN2 5
#define NUM_LEDS 103
#define ArcReactorLEDS 7
#define BRIGHTNESS 75
#define fps 30
// int DO = 2;     //Pin for Digital Output - DO
int DA = 0;     // Pin for Analog Output - AO
int trsh = 160; //Set minimum threshold for LED lit
uint8_t gHue = 0;
CRGBPalette16 currentPallet;
TBlendType currentBlending;

void setup()
{
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS); //.setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(ArcReactor, ArcReactorLEDS);
    EMA_S = analogRead(DA);


#pragma region Color Initialization
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(255, 0, 0);
        FastLED.delay(100);
        // fadeall1();
    }
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(0, 255, 0);
        FastLED.delay(100);
        // fadeall1();
    }
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(0, 0, 255);
        FastLED.delay(100);
        // fadeall1();
    }

    for (int i = 0; i >= 0; i--)
    {
        ArcReactor[i] = CRGB::Black;
    }

    LEDS.showColor(CRGB(255, 0, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 255, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 255));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 0));

#pragma endregion
}

// *** REPLACE FROM HERE ***
void loop()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].r = 19;
        leds[i].g = 214;
        leds[i].b = 182;
    }
    
    for (int i = NUM_LEDS - 1; i >= 0; i--)
    {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }

FastLED.show();
}

// *** REPLACE TO HERE ***
