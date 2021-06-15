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
#define DATA_PIN 6
#define DATA_PIN2 5
#define NUM_LEDS 104
#define ArcReactorLEDS 7
#define BRIGHTNESS 25
#define fps 240
// int DO = 2;     //Pin for Digital Output - DO
int DA = 0;     // Pin for Analog Output - AO
int trsh = 50; //Set minimum threshold for LED lit
uint8_t gHue = 0;
CRGBPalette16 currentPallet;
TBlendType currentBlending;

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
#define limit8 11
#define limit9 22
#define limit10 33
#define limit11 44
#define limit12 55
#define limit13 66
#define limit14 80

CRGB strip1[NUM_LEDS];
CRGB ArcReactor[ArcReactorLEDS];
CRGBPalette16 vibeFlame;
CRGBPalette16 patternOfSynth;

uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;
#pragma endregion

void setup()
{
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS); //.setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(ArcReactor, ArcReactorLEDS);
    EMA_S = analogRead(DA);

    currentBlending = LINEARBLEND;
    currentPallet = RainbowColors_p;
#pragma region Color Pallets
    vibeFlame = CRGBPalette16(CRGB::DarkRed, CRGB::DeepPink, CRGB::Fuchsia, CRGB(20, 201, 189));
    patternOfSynth = CRGBPalette16(CRGB::DarkRed, CRGB::Red, CRGB::OrangeRed, CRGB::DarkOrange,
                                   CRGB::Orange, CRGB::LightSkyBlue, CRGB::DeepSkyBlue, CRGB::Cyan,
                                   CRGB::DeepSkyBlue, CRGB::DarkCyan, CRGB::DodgerBlue, CRGB::Teal,
                                   CRGB::Blue, CRGB::BlueViolet, CRGB::DarkOrchid, CRGB::DarkViolet);

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

    // EC1();
    // EC2();
    // EC250();
    // EC3();
    // EC4();
    // EC401();
    // EC420();
    // EC421();
    // EC422();

    // SynthCity();
    // SynthCity2();
    // VibeTime();
    // TheBigSad();
    AmbientLighting();
    // SafeMode();
    // GradientLightBar(); BROKeN

    // DifferingColors();
    // DifferingColorsMonitor();
    // FadingBlink(startIndex, 255);
    // colorCycle(vibeFlame, startIndex, 255);
    // monitorColorCycle(patternOfSynth, startIndex, 200);

    // PotControlled();

    // MonitorOff();
    ArcReactorOff();
    // AllOff();

    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
}

#pragma region EpilespyCity

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

#pragma region EC2
void EC2()
{
#pragma region Maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
#pragma endregion

#pragma region Limiters
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }

#pragma endregion

#pragma region EC Version
    //colors for strip 1
    for (int i = 0; i < overtrsh && i < 69; i++)
    {
        strip1[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
        red = (red + 1) & 0xFF;
        green = green + (i * 2) & 0xFF;
        blue = (blue + (i * 3)) & 0xFF;
    }
    for (int i = 69; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::DarkRed;
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
#pragma endregion
}
#pragma endregion

#pragma region EC250
void EC250()
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
    int color1 = random8(255); //random8(NUM_LEDS) + (69 * 0.2);
    int color2 = random8(255); //random8(NUM_LEDS + NUM_LEDS2);
    int color3 = random8(255); //random8(NUM_LEDS2) + (69 + 50);
    int color4 = random8(255);
    int color5 = random8(255);
    int color6 = random8(255);

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < 74; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
    }

    for (int i = 74; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::DarkRed;
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
#pragma endregion

#pragma region Colors for ArcReactor
    if (overtrsh <= 75)
    {
        for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
        {
            ArcReactor[i] = CRGB(color3, color2, color1);
            // fadeall1();
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
            // fadeall1();
        }
    }
#pragma endregion
}
#pragma endregion

#pragma region EC3
void EC3()
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

#pragma region Colors for ArcReactor
    for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(color3, color2, color1);
        // fadeall1();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        ArcReactor[i] = CRGB::Black;
    }

#pragma endregion
}

#pragma endregion

#pragma region EC4
void EC4()
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
    int color1 = random8();
    int color2 = random8();
    int color3 = random8();

    int color4 = random8();
    int color5 = random8();
    int color6 = random8();

    int color7 = random8();
    int color8 = random8();
    int color9 = random8();

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }
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

#pragma region Colors for ArcReactor
    for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(color3, color2, color1);
        // fadeall1();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        ArcReactor[i] = CRGB::Black;
    }
}
#pragma endregion

#pragma endregion

#pragma region EC401
void EC401()
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
    int color1 = random8();
    int color2 = random8();
    int color3 = random8();

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

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < 64; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeall1();
    }
    for (int i = 64; i < overtrsh && i < 70; i++)
    {
        strip1[i] = CRGB(color4, color5, color6);
    }
    for (int i = 70; i < overtrsh && i < 76; i++)
    {
        strip1[i] = CRGB(color6, color4, color5);
    }
    for (int i = 76; i < overtrsh && i < 82; i++)
    {
        strip1[i] = CRGB(color5, color6, color4);
    }
    for (int i = 82; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color7, color8, color9);
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }

#pragma endregion
}
#pragma endregion

#pragma region EC420
void EC420()
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

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeall1();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }
#pragma endregion

#pragma region Colors for ArcReactor
    for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(color1, color2, color3);
        // fadeall1();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        ArcReactor[i] = CRGB::Black;
    }
#pragma endregion
}
#pragma endregion

#pragma region EC421
void EC421()
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    // FastLED.setBrightness(overtrsh);
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

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeall1();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }
#pragma endregion

#pragma region Colors for ArcReactor
    for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB(color3, color2, color1);
        // fadeall1();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        ArcReactor[i] = CRGB::Black;
    }
#pragma endregion
}
#pragma endregion

#pragma region EC422
void EC422()
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) + 20;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh); //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;
    // FastLED.setBrightness(overtrsh);
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
    Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    if (avOvertrsh <= 100)
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

#pragma endregion

#pragma region Moods

#pragma region SynthCity
void SynthCity()
{
#pragma region Maths and Limiters
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);

    //Defining overtrsh and sets the values to Num of LEDS
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 2;

    FastLED.setBrightness(avOvertrsh);

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }

#pragma endregion

#pragma region colors
    //colors for strip 1
    for (int i = 0; i < overtrsh && i < limit1; i++)
    {
        strip1[i] = CRGB(0, 255, 255);
    }
    for (int i = 12; i < overtrsh && i < limit2; i++)
    {
        strip1[i] = CRGB(0, 154, 255);
    }
    for (int i = 23; i < overtrsh && i < limit3; i++)
    {
        strip1[i] = CRGB(50, 0, 255);
    }
    for (int i = 34; i < overtrsh && i < limit4; i++)
    {
        strip1[i] = CRGB(125, 0, 255);
    }
    for (int i = 45; i < overtrsh && i < limit5; i++)
    {
        strip1[i] = CRGB::Fuchsia;
    }
    for (int i = 56; i < overtrsh && i < limit6; i++)
    {
        strip1[i] = CRGB(255, 0, 77);
    }
    for (int i = 67; i < overtrsh && i < limit7; i++)
    {
        strip1[i] = CRGB::Red;
    }
    for (int i = 78; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::DarkRed;
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
            ArcReactor[i] = CRGB(0, 154, 255);
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
            ArcReactor[i] = CRGB(255, 0, 77);
            // fadeall1();
        }
        for (int i = ArcReactorLEDS - 1; i > overtrsh && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }
#pragma endregion
}
#pragma endregion
#pragma endregion

#pragma region SynthCity2
void SynthCity2()
{
#pragma region Maths and Limiters
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);

    //Defining overtrsh and sets the values to Num of LEDS
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 2;

    FastLED.setBrightness(avOvertrsh);

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }

#pragma endregion

#pragma region colors
    //colors for strip 1
    for (int i = 0; i < overtrsh && i < limit1; i++)
    {
        strip1[i] = CRGB(0, 255, 255);
        fadeall1();
    }
    for (int i = 12; i < overtrsh && i < limit2; i++)
    {
        strip1[i] = CRGB(0, 154, 255);
        fadeall1();
    }
    for (int i = 23; i < overtrsh && i < limit3; i++)
    {
        strip1[i] = CRGB(50, 0, 255);
        fadeall1();
    }
    for (int i = 34; i < overtrsh && i < limit4; i++)
    {
        strip1[i] = CRGB(125, 0, 255);
        fadeall1();
    }
    for (int i = 45; i < overtrsh && i < limit5; i++)
    {
        strip1[i] = CRGB::Fuchsia;
        fadeall1();
    }
    for (int i = 56; i < overtrsh && i < limit6; i++)
    {
        strip1[i] = CRGB(255, 0, 77);
        fadeall1();
    }
    for (int i = 67; i < overtrsh && i < limit7; i++)
    {
        strip1[i] = CRGB::Red;
        fadeall1();
    }
    for (int i = 78; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::DarkRed;
        fadeall1();
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }

#pragma endregion

#pragma region ArcReactor Colors
    if (avOvertrsh <= 100)
    {
        for (int i = 0; i < overtrsh && i < ArcReactorLEDS; i++)
        {
            ArcReactor[i] = CRGB(0, 154, 255);
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
            ArcReactor[i] = CRGB(255, 0, 77);
            // fadeall1();
        }
        for (int i = ArcReactorLEDS - 1; i > overtrsh && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }
#pragma endregion
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
#pragma endregion
}

#pragma endregion

#pragma region TheBigSad
void TheBigSad()
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
    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }

#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(128, 0, 2);
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
            ArcReactor[i] = CRGB(128, 0, 2);
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
            ArcReactor[i] = CRGB::DarkRed;
            // fadeall1();
        }
        for (int i = ArcReactorLEDS - 1; i > overtrsh && i >= 0; i--)
        {
            ArcReactor[i] = CRGB::Black;
        }
    }
#pragma endregion
#pragma endregion
}
#pragma endregion

#pragma region SafeMode
void SafeMode()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        strip1[i] = CRGB::Yellow;
    }

    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = CRGB::Yellow;
    }
}

#pragma endregion

#pragma region GradientLightBar
void GradientLightBar()
{
    // put your main code here, to run repeatedly:
    synthRainbow();
    addGlitter(100);
    FastLED.show();
    FastLED.delay(1000 / fps);
    FastLED.setBrightness(50);
}

void addGlitter(fract8 chanceOfGlitter)
{
    if (random8() < chanceOfGlitter)
    {
        strip1[random16(NUM_LEDS)] += CRGB::White;
    }
}

void synthRainbow()
{
    //strip1
    fill_gradient_RGB(strip1, 0, CRGB::Cyan, 55, CRGB::LightSeaGreen);
    fill_gradient_RGB(strip1, 56, CRGB::Fuchsia, NUM_LEDS, CRGB::Red);
}
#pragma endregion

#pragma endregion

#pragma region AmbientLighting
void AmbientLighting()
{
    // Wait for first byte of Magic Word
    for (i = 0; i < sizeof prefix; ++i)
    {
    waitLoop:
        while (!Serial.available())
            ;
        ;
        // Check next byte in Magic Word
        if (prefix[i] == Serial.read())
            continue;
        // otherwise, start over
        i = 0;
        goto waitLoop;
    }

    // Hi, Lo, Checksum
    while (!Serial.available())
        ;
    ;
    hi = Serial.read();
    while (!Serial.available())
        ;
    ;
    lo = Serial.read();
    while (!Serial.available())
        ;
    ;
    chk = Serial.read();

    // If checksum does not match go back to wait
    if (chk != (hi ^ lo ^ 0x55))
    {
        i = 0;
        goto waitLoop;
    }

    memset(strip1, 0, NUM_LEDS * sizeof(struct CRGB));
    // Read the transmission data and set LED values
    for (uint8_t i = 0; i < NUM_LEDS; i++)
    {
        byte r, g, b;
        while (!Serial.available())
            ;
        r = Serial.read();
        while (!Serial.available())
            ;
        g = Serial.read();
        while (!Serial.available())
            ;
        b = Serial.read();
        strip1[i].r = r;
        strip1[i].g = g;
        strip1[i].b = b;
    }

    // Shows new values
    FastLED.show();
}
#pragma endregion

#pragma region misc

#pragma region MonitorOff
void MonitorOff()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        strip1[i] = CRGB::Black;
    }
}
#pragma endregion

#pragma region ArcReactorOff
void ArcReactorOff()
{
    for (int i = 0; i < ArcReactorLEDS; ++i)
    {
        ArcReactor[i] = CRGB::Black;
    }
}
#pragma endregion

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

#pragma endregion

#pragma region Monitor Patterns

#pragma region DifferingColorsMonitor
void DifferingColorsMonitor()
{
    FastLED.setBrightness(100);
    EVERY_N_MILLISECONDS(20)
    {
        gHue++;
    }
    FastLED.delay(1000 / fps);

    //working part
    fadeToBlackBy(strip1, NUM_LEDS, 20);
    byte dothue = 0;
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[beatsin16(i + NUM_LEDS, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
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
}
#pragma endregion

#pragma endregion

#pragma region ArcReactor Colors

#pragma region DifferingColors

#pragma region ArcReactor
void DifferingColors()
{
    FastLED.setBrightness(100);
    EVERY_N_MILLISECONDS(20)
    {
        gHue++;
    }
    FastLED.delay(1000 / fps);

    //working part
    fadeToBlackBy(ArcReactor, ArcReactorLEDS, 20);
    byte dothue = 0;
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[beatsin16(i + ArcReactorLEDS, 0, ArcReactorLEDS - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}
#pragma endregion

#pragma endregion

#pragma region FadingBlink
void FadingBlink(uint8_t colorIndex, uint8_t brightness)
{
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    FastLED.delay(1000 / fps);
}
#pragma endregion

#pragma region colorCycle
void colorCycle(CRGBPalette16 currentPallet, uint8_t colorIndex, uint8_t brightness)
{
    for (int i = 0; i < ArcReactorLEDS; i++)
    {
        ArcReactor[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    FastLED.delay(1000 / fps);
}

#pragma endregion

#pragma endregion

#pragma region PotControlled
void PotControlled()
{
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
    // delay(1); // delay in between reads for stability
#pragma endregion

    if (average > 700)
    {
        DifferingColors();
        monitorColorCycle(RainbowColors_p, startIndex, 255);
    }

    if ((average <= 700) && (average >= 650))
    {
        DifferingColors();
        monitorColorCycle(RainbowStripesColors_p, startIndex, 255);
    }

    if ((average <= 650) && (average >= 600))
    {
        colorCycle(RainbowColors_p, startIndex, 255);
        monitorColorCycle(RainbowColors_p, startIndex, 255);
    }

    if ((average <= 600) && (average >= 550))
    {
        FadingBlink(startIndex, 255);
        monitorColorCycle(RainbowColors_p, startIndex, 255);
    }

    if ((average <= 550) && (average >= 500))
    {
        VibeTime();
    }
    if ((average <= 500) && (average >= 450))
    {
        SynthCity2();
    }

    if ((average <= 450) && (average >= 400))
    {
        TheBigSad();
    }

    // if ((average <= 400) && (average >= 350))
    // {
    //     EC422();
    // }

    // if ((average <= 350) && (average >= 300))
    // {
    //     EC420();
    // }

    // if ((average <= 300) && (average >= 250))
    // {
    //     EC401();
    // }

    // if ((average <= 250) && (average >= 200))
    // {
    //     EC3();
    // }
    if ((average <= 200) && (average >= 150))
    {
        EC250();
    }
    if ((average <= 150) && (average >= 100))
    {
        EC2();
    }

    // if ((average <= 100) && (average >= 50))
    // {
    //     EC1();
    // }

    if (average < 50)
    {
        AllOff();
    }
}
#pragma endregion