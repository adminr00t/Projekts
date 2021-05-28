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
#define DATA_PIN2 7
#define OutputPin 9
#define NUM_LEDS 47
#define NUM_LEDS2 30
#define fps 60
#define COOLING 55
#define SPARKING 120
int DO = 2;     //Pin for Digital Output - DO
int DA = 0;     // Pin for Analog Output - AO
int trsh = 100; //Set minimum threshold for LED lit
uint8_t gHue = 0;
// int Brightness 50;
CRGBPalette16 currentPallet;
TBlendType currentBlending;
#pragma endregion

#pragma region Strip Segments and Definitions
CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS2];
#pragma endregion

#pragma region Reverse Fire
bool gReverseDirection = false;
bool gReverseDirection2 = false;
#pragma endregion

void setup()
{
#pragma region Strip setup and maths
    Serial.begin(115200);
    // pinMode(2, INPUT);
    pinMode(OutputPin, OUTPUT);
    pinMode(DATA_PIN, INPUT);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(strip2, NUM_LEDS2);
    EMA_S = analogRead(DA);

#pragma endregion

#pragma region Color Initialization

    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(255, 0, 0);
        FastLED.delay(10);
        // fadeall1();
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(255, 0, 0);
        FastLED.delay(10);
        // fadeall1();
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(0, 255, 0);
        FastLED.delay(10);
        // fadeall1();
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(0, 255, 0);
        FastLED.delay(10);
        // fadeall1();
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(0, 0, 255);
        FastLED.delay(10);
        // fadeall1();
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(0, 0, 255);
        FastLED.delay(10);
        // fadeall1();
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::Black;
    }

    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB::Black;
    }

}
#pragma endregion

void loop()
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int oT = (EMA_S - trsh) >> 1;  //Divides by 2
    int oT2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOt = (oT + oT2) >> 1;

    if (oT < 0 || oT2 < 0)
    {
        oT = 0;
        oT2 = 0;
    }

    if (avOt < 0){
        avOt = 0;
    }
    // FastLED.setBrightness(avOvertrsh);
    // analogWrite(OutputPin, sensorvalue);
#pragma endregion

    // Beat Detection
    

    if (avOt <= 0)
    {
        for (int i = (NUM_LEDS)-1; i >= 0; i--)
        {
            strip1[i].fadeToBlackBy(2);
            strip2[i].fadeToBlackBy(1);
        }
    }else{
        EC5(oT, oT2, avOt, 50);
    }
    FastLED.show();
}

#pragma region EC5
void EC5(int overtrsh, int overtrsh2, int avOvertrsh, int Brightness)
{


#pragma region Color Definitions and LED Limiters
    // uint8_t heatindex = random8()
    int color1 = random8();
    int color2 = random8();
    int color3 = random8();

    if (overtrsh > NUM_LEDS || overtrsh2 > NUM_LEDS2)
    {
        overtrsh = NUM_LEDS;
        overtrsh2 = NUM_LEDS2;
    }

#pragma endregion

#pragma region Diagnosis
    // Serial.println(overtrsh);
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
    // Serial.println(DATA_PIN);
#pragma endregion

#pragma region Colors for Strip 1


#pragma endregion

#pragma region Colors for Strip2
    if (avOvertrsh <= 75)
    {

        for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
        {
            strip1[i] = CRGB(color1, color2, color3);
            FastLED.setBrightness(Brightness);
        }
        
        // for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
        // {
        //     strip1[i] = CRGB::Black;
        // }

        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB(color3, color2, color1);
            FastLED.setBrightness(Brightness);
        }

        // LED Brightness
    }
    else
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB::DarkRed;
            FastLED.setBrightness(Brightness);
        }
    }

#pragma endregion
}
#pragma endregion