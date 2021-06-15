#include<FastLED.h>

#pragma region constants
const int numReadings = 10;
int readings[numReadings]; // the readings from the analog input
int readIndex = 0;         // the index of the current reading
int total = 0;             // the running total
int average = 0;           // the average
int inputPin = A2;
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;
int red = 0;
int green = 0;
int blue = 0;
int previous_value = 0;
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB


#pragma region Variables
#define DATA_PIN 6
#define DATA_PIN2 5
#define NUM_LEDS 104
#define ArcReactorLEDS 7
#define BRIGHTNESS 50
#define fps 100
int DO = 2;     //Pin for Digital Output - DO
int DA = 0;     // Pin for Analog Output - AO
int trsh = 100; //Set minimum threshold for LED lit
uint8_t gHue = 0;
CRGBPalette16 currentPallet;
TBlendType currentBlending;
CRGB strip1[NUM_LEDS];
CRGB ArcReactor[ArcReactorLEDS];
#pragma endregion

void setup()
{
#pragma region smoothing    
    // initialize serial communication with computer:
    Serial.begin(9600);
    // initialize all the readings to 0:
    for (int thisReading = 0; thisReading < numReadings; thisReading++)
    {
        readings[thisReading] = 0;
    }
#pragma endregion

#pragma region ledsDef
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS); //.setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(ArcReactor, ArcReactorLEDS);
    currentBlending = LINEARBLEND;
    currentPallet = RainbowColors_p;
#pragma endregion    
}
#pragma region Fading
void fadeall1()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(215);
    }
}

#pragma endregion

void loop()
{
#pragma region randomStuff
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
#pragma endregion
    
    // smoothing();
    // monitorColorCycle(PartyColors_p, startIndex, 255);
    changing();
    FastLED.show();
}

void changing(){
#pragma region randomStuff
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
#pragma endregion
#pragma region Maths
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings)
    {
        // ...wrap around to the beginning:
        readIndex = 0;
    }

    // calculate the average:
    average = total / numReadings;
    // send it to the computer as ASCII digits
    Serial.println(average);
    delay(1); // delay in between reads for stability
    #pragma endregion

    if ( average > 750 ){
        monitorColorCycle(PartyColors_p, startIndex, 255);
        colorCycle(RainbowStripeColors_p, startIndex, 255);
    }
    if((average <= 750) && (average >= 500)){
        EC422();
    }

    if ((average <= 500) && (average >= 250))
    {
        VibeTime();
    }

    if ((average <= 250) && (average >= 10))
    {
        EC1();
    }
if (average < 10 )
{
    AllOff();
}

    // if( 749 > average > 500)-
    // {
    //     EC1();
    // }
    // if( 500 > average > 250){
    //     VibeTime();
    // }
    // if( average < 250){
    //     AllOff();
    // }
}
void colorCycle(CRGBPalette16 currentPallet, uint8_t colorIndex, uint8_t brightness)
{
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    FastLED.delay(1000 / fps);
}

#pragma region AllOff

void AllOff()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        strip1[i] = CRGB::Black;
    }

    for (int i = 0; i < ArcReactorLEDS; ++i)
    {
        ArcReactor[i] = CRGB::Black;
    }
}
#pragma endregion

#pragma region Moving Pallet
void monitorColorCycle(CRGBPalette16 currentPallet, uint8_t colorIndex, uint8_t brightness)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    FastLED.delay(1000 / fps);
    FastLED.setBrightness(255);
}
#pragma endregion

#pragma region VibeTime
void VibeTime()
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
    int color2 = random8(NUM_LEDS);
    int color3 = random8(69 + 50);

    int color4 = random8(100) + (69 * 0.25);
    int color5 = random8() - (69 * 0.5);
    int color6 = random8(120);

    int color7 = random8();
    int color8 = random8(147);
    int color9 = random8(NUM_LEDS);

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }
#pragma endregion

#pragma region Diagnosis
    // Serial.println(overtrsh);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < 9; i++)
    {
        strip1[i] = CRGB::Fuchsia;
        fadeall1();
    }
    for (int i = 9; i < overtrsh && i < 34; i++)
    {
        strip1[i] = CRGB(20, 201, 189);
        fadeall1();
    }
    for (int i = 34; i < overtrsh && i < 61; i++)
    {
        strip1[i] = CRGB::Fuchsia;
        fadeall1();
    }
    for (int i = 61; i < overtrsh && i < 86; i++)
    {
        strip1[i] = CRGB(20, 201, 189);
        fadeall1();
    }
    for (int i = 86; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::Fuchsia;
        fadeall1();
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }

#pragma region ArcReactor Colors
    if (avOvertrsh <= 100)
    {
        for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
        {
            ArcReactor[i] = CRGB(20, 201, 189);
            // fadeall1();
        }
        for (int i = ArcReactorLEDS - 1; i > overtrsh && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }
    else
    {
        for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
        {
            ArcReactor[i] = CRGB::Fuchsia;
            // fadeall1();
        }
        for (int i = ArcReactorLEDS - 1; i > overtrsh && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }
#pragma endregion
FastLED.show();
#pragma endregion
}

#pragma endregion

#pragma region EC422
void EC422()
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    FastLED.setBrightness(overtrsh);
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
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    if (avOvertrsh <= 130)
    {
        for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
        {
            strip1[i] = CRGB(color1, color2, color3);
            fadeall1();
        }

        for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
        {
            strip1[i] = CRGB::Black;
        }
    }
    else
    {
        for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
        {
            strip1[i] = CRGB::DarkRed;
        }

        for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
        {
            strip1[i] = CRGB::Black;
        }
    }

#pragma endregion

#pragma region Colors for ArcReactor
    if (avOvertrsh <= 130)
    {

        for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
        {
            ArcReactor[i] = CRGB(color3, color2, color1);
        }

        for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }
    else
    {
        for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
        {
            ArcReactor[i] = CRGB::DarkRed;
        }

        for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }

#pragma endregion
}
#pragma endregion

#pragma region EC1
void EC1()
{
#pragma region Maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    FastLED.setBrightness(avOvertrsh);
#pragma endregion

#pragma region Limiters
    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }

#pragma endregion

#pragma region Diagnosis
    // Serial.println(overtrsh);
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region EC Version
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        //255 - ((i >> 3) * 32)
        // strip1[i] = CRGB(128,0,128);
        strip1[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
        red = (red + 1) & 0xFF;
        green = green + (i * 2) & 0xFF;
        blue = (blue + (i * 3)) & 0xFF;
        if (i > previous_value && i & 0b10 == 1)
        {
            //delay(150);
            //FastLED.show();
        }
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
    //misc
    previous_value = overtrsh;
    FastLED.show();
#pragma endregion
}
#pragma endregion