#include <FastLED.h>

int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;
int DO = 2; //Pin for Digital Output - DO
int DA = 0; // Pin for Analog Output - AO

int trsh = 250; //Set minimum threshold for LED lit

#define DATA_PIN 3
#define DATA_PIN2 4
#define NUM_LEDS 82
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS];

void setup()
{
    Serial.begin(115200);
    EMA_S = analogRead(DA);

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS).setCorrection(TypicalLEDStrip);

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
    sensorvalue = analogRead(DA); //Read the analog value
    Serial.println(sensorvalue);
 
  EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    FastLED.setBrightness(avOvertrsh);
    // FastLED.setBrightness(255);

    int color1 = random8();
    int color2 = random8();
    int color3 = random8();
    if (sensorvalue >= trsh)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            strip1[i] = CRGB(color1, color2, color3);
            strip2[i] = CRGB(color3, color1, color2);
            
            // strip1[i] = CRGB(255, 77, 9);
            // strip2[i] = CRGB::DarkOrange;
            
            if (i % 2 == 1) {
                FastLED.show();
                fadeallBars();
            }
        }
         for (int i =0; i < NUM_LEDS; i++)
        {
            strip1[i] = CRGB::Black;
            strip2[i] = CRGB::Black;
        }
        FastLED.show();
        // Serial.println(sensorvalue);
    }
}

void fadeallBars()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(250);
        strip2[i].nscale8(250);
    }
}