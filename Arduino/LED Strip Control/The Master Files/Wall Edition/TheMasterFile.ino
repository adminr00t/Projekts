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
#define BRIGHTNESS 50
#define fps 60
#define COOLING 55
#define SPARKING 120
int DO = 2;     //Pin for Digital Output - DO
int DA = 0;     // Pin for Analog Output - AO
int trsh = 115; //Set minimum threshold for LED lit
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
CRGB strip2[NUM_LEDS2];

CRGBPalette16 synthFlame;
CRGBPalette16 blueFlame;
CRGBPalette16 vibeFlame;
CRGBPalette16 patternOfSynth;
CRGBPalette16 jonoColors;

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

    currentBlending = LINEARBLEND;
    currentPallet = RainbowColors_p;
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

#pragma endregion

#pragma region FireColors
    blueFlame = CRGBPalette16(CRGB::Black, CRGB::Blue, CRGB::Aqua, CRGB::White);

    synthFlame = CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::OrangeRed, CRGB::DarkOrange,
                               CRGB::Orange, CRGB::LightSkyBlue, CRGB::DeepSkyBlue, CRGB::Cyan,
                               CRGB::DeepSkyBlue, CRGB::DarkCyan, CRGB::DodgerBlue, CRGB::Teal,
                               CRGB::Blue, CRGB::BlueViolet, CRGB::DarkOrchid, CRGB::DarkViolet);

    vibeFlame = CRGBPalette16(CRGB::Black, CRGB::DarkRed, CRGB::Fuchsia, CRGB(20, 201, 189));

    jonoColors = CRGBPalette16(CRGB::LightGreen, CRGB::SeaGreen, CRGB::Cyan, CRGB::Blue);

    patternOfSynth = CRGBPalette16(CRGB::DarkRed, CRGB::Red, CRGB::OrangeRed, CRGB::DarkOrange,
                                   CRGB::Orange, CRGB::LightSkyBlue, CRGB::DeepSkyBlue, CRGB::Cyan,
                                   CRGB::DeepSkyBlue, CRGB::DarkCyan, CRGB::DodgerBlue, CRGB::Teal,
                                   CRGB::Blue, CRGB::BlueViolet, CRGB::DarkOrchid, CRGB::DarkViolet);

#pragma endregion
}
DEFINE_GRADIENT_PALETTE(myPal2){
    0, 255, 24, 76,
    100, 255, 87, 125,
    175, 255, 205, 220,
    200, 10, 156, 245,
    255, 0, 48, 98};

CRGBPalette16 colorsOfCyber = myPal2;
void loop()
{
#pragma region randomStuff
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
#pragma endregion

    // Beat Detection
    // EC1();
    // EC2();
    // EC250();
    // EC3();
    // EC4();
    // EC401();
    // EC420();
    // EC421();
    // EC422();
    // EC5(50);

    // Beat Detection Mood Lighting
    // CyberBeats(patternOfSynth, synthFlame);
    // SynthCity();
    // VibeTime();
    // TheBigSad();
    // pbBD(PartyColors_p, startIndex);

    // Color Patterns
    colorPatterns(patternOfSynth, startIndex, 200);
    // SynthRain();
    // LightBars();
    // SafeSpace();
    // MeditationTime(ForestColors_p, startIndex, 255);

    // Modes
    // Off();
    // LeftOff();
    // RightOff();

    // Misc
    // FireEmbers(255, 140, 0, 100);
    // ColorfulFire(HeatColors_p);
    // simpleLight();
    // MeteorLeft(4, 185, 244, 5, 64, true, 30);
    // MeteorRight(248, 1, 87, 5, 62, true, 30);

    FastLED.show();
    FastLED.setBrightness(BRIGHTNESS);
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

#pragma region COlors
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

    //colors for strip2
    for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
    {
        //255 - ((i >> 3) * 32)
        // strip2[i] = CRGB(128,0,128);
        strip2[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
        red = (red + 1) & 0xFF;
        green = green + (i * 2) & 0xFF;
        blue = (blue + (i * 3)) & 0xFF;
        if (i > previous_value && i & 0b10 == 1)
        {
            //delay(150);
            //FastLED.show();
        }
    }
    for (int i = NUM_LEDS2 - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
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
    if (overtrsh2 > NUM_LEDS2)
    {
        overtrsh2 = NUM_LEDS2;
    }

    Serial.println(overtrsh);
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

    //colors for strip2
    for (int i = 0; i < overtrsh2 && i < 67; i++)
    {
        strip2[i] = CRGB((red += i) & 0xFF, (green += i * 3) & 0xFF, (blue += i * 5) & 0xFF);
        red = (red + 1) & 0xFF;
        green = green + (i * 2) & 0xFF;
        blue = (blue + (i * 3)) & 0xFF;
    }
    for (int i = 67; i < overtrsh && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB::DarkRed;
    }
    for (int i = NUM_LEDS2 - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
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

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < 72; i++)
    {
        strip2[i] = CRGB(color4, color5, color6);
    }

    for (int i = 72; i < overtrsh2 && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB::DarkRed;
    }

    for (int i = NUM_LEDS - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
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
    for (int i = 0; i < overtrsh2 && i < limit8; i++)
    {
        strip2[i] = CRGB(color1, color2, color3);
    }
    for (int i = 10; i < overtrsh2 && i < limit9; i++)
    {
        strip2[i] = CRGB(color3, color1, color2);
    }
    for (int i = 21; i < overtrsh2 && i < limit10; i++)
    {
        strip2[i] = CRGB(color2, color3, color1);
    }
    for (int i = 32; i < overtrsh2 && i < limit11; i++)
    {
        strip2[i] = CRGB(color4, color5, color6);
    }
    for (int i = 43; i < overtrsh2 && i < limit12; i++)
    {
        strip2[i] = CRGB(color6, color4, color5);
    }
    for (int i = 54; i < overtrsh2 && i < limit13; i++)
    {
        strip2[i] = CRGB(color5, color6, color4);
    }
    for (int i = 65; i < overtrsh2 && i < limit14; i++)
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
    for (int i = 0; i < overtrsh2 && i < limit8; i++)
    {
        strip2[i] = CRGB(color9, color8, color7);
    }
    for (int i = 10; i < overtrsh2 && i < limit9; i++)
    {
        strip2[i] = CRGB(color7, color9, color8);
    }
    for (int i = 21; i < overtrsh2 && i < limit10; i++)
    {
        strip2[i] = CRGB(color8, color7, color9);
    }
    for (int i = 32; i < overtrsh2 && i < limit11; i++)
    {
        strip2[i] = CRGB(color6, color5, color4);
    }
    for (int i = 43; i < overtrsh2 && i < limit12; i++)
    {
        strip2[i] = CRGB(color4, color6, color5);
    }
    for (int i = 54; i < overtrsh2 && i < limit13; i++)
    {
        strip2[i] = CRGB(color5, color4, color6);
    }
    for (int i = 65; i < overtrsh2 && i < limit14; i++)
    {
        strip2[i] = CRGB(color3, color2, color1);
    }
    for (int i = 76; i < overtrsh2 && i < NUM_LEDS; i++)
    {
        strip2[i] = CRGB(color1, color3, color2);
    }
    for (int i = NUM_LEDS - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
    }
#pragma endregion
}
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
    for (int i = 0; i < overtrsh && i < 64; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
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

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < 62; i++)
    {
        strip2[i] = CRGB(color1, color2, color3);
    }
    for (int i = 62; i < overtrsh && i < 68; i++)
    {
        strip2[i] = CRGB(color4, color5, color6);
    }
    for (int i = 68; i < overtrsh && i < 74; i++)
    {
        strip2[i] = CRGB(color6, color4, color5);
    }
    for (int i = 74; i < overtrsh && i < 80; i++)
    {
        strip2[i] = CRGB(color5, color6, color4);
    }
    for (int i = 80; i < overtrsh && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(color7, color8, color9);
    }

    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB::Black;
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
    Serial.println(overtrsh);
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeallVibes();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }

#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(color1, color2, color3);
        fadeallVibes2();
    }

    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB::Black;
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
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeallVibes();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }

#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(color3, color2, color1);
        fadeallVibes2();
    }

    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB::Black;
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
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;

    if (overtrsh < 0 || overtrsh2 < 0)
    {
        overtrsh = 0;
        overtrsh2 = 0;
    }

    FastLED.setBrightness(avOvertrsh);
    // analogWrite(OutputPin, sensorvalue);
#pragma endregion

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
    Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
    // Serial.println(DATA_PIN);
#pragma endregion

#pragma region Colors for Strip 1
    // if (avOvertrsh <= 75)
    // {
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeallVibes();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }
    // }
    // else
    // {
    //     for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    //     {
    //         strip1[i] = CRGB::DarkRed;
    //         fadeallVibes();
    //     }

    //     for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    //     {
    //         strip1[i] = CRGB::Black;
    //     }
    // }
#pragma endregion

#pragma region Colors for Strip2
    if (avOvertrsh <= 75)
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB(color3, color2, color1);
            fadeallVibes2();
        }

        for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
        {
            strip2[i] = CRGB::Black;
        }
    }
    else
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB::DarkRed;
            // fadeallVibes2();
        }

        for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
        {
            strip2[i] = CRGB::Black;
        }
    }

#pragma endregion
}
#pragma endregion

#pragma region EC5
void EC5(int brightness)
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;

    if (overtrsh < 0 || overtrsh2 < 0)
    {
        overtrsh = 0;
        overtrsh2 = 0;
    }

    // FastLED.setBrightness(avOvertrsh);
    // analogWrite(OutputPin, sensorvalue);
#pragma endregion

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
    Serial.println(overtrsh);
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
    // Serial.println(DATA_PIN);
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        FastLED.setBrightness(brightness);
        // fadeallVibes();
    }
    
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i].fadeToBlackBy(4);
    }

#pragma endregion

#pragma region Colors for Strip2
    if (avOvertrsh <= 75)
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB(color3, color2, color1);
            FastLED.setBrightness(brightness);
            // fadeallVibes2();
        }

        for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
        {
            strip2[i].fadeToBlackBy(2);
        }

    }
    else
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB::DarkRed;
            FastLED.setBrightness(brightness);
            // fadeallVibes2();
        }

        for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
        {
            strip2[i].fadeToBlackBy(2);
        }
    }

#pragma endregion
}
#pragma endregion

#pragma region ColorChangingBeatDetection
void ColorChangingBeatDetection()
{
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
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color1, color2, color3);
        fadeall();
    }

    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
    }

#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(color1, color2, color3);
        fadeall();
    }

    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB::Black;
    }
#pragma endregion
}
#pragma endregion

#pragma region PatternBrightnessBeatDetection
void pbBD(CRGBPalette16 currentPallet, uint8_t colorIndex)
{
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    uint8_t overtrsh = (EMA_S - trsh) >> 1; //Divides by 2

    if (overtrsh < 0)
    {
        overtrsh = 0;
    }

    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }
    uint8_t brightness = overtrsh;

    // for (int i = (NUM_LEDS)-1; i >= 0; i--)
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = ColorFromPalette(currentPallet, colorIndex, overtrsh, currentBlending);
        colorIndex += 3;
    }

    for (int i = (NUM_LEDS2)-1; i >= 0; i--)
    {
        strip2[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
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
    if (overtrsh2 > NUM_LEDS2)
    {
        overtrsh2 = NUM_LEDS2;
    }

    Serial.println(overtrsh);
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

    //colors for strip2
    for (int i = 0; i < overtrsh2 && i < limit8; i++)
    {
        strip2[i] = CRGB(0, 255, 255);
    }
    for (int i = 10; i < overtrsh2 && i < limit9; i++)
    {
        strip2[i] = CRGB(0, 154, 255);
    }
    for (int i = 21; i < overtrsh2 && i < limit10; i++)
    {
        strip2[i] = CRGB(50, 0, 255);
    }
    for (int i = 32; i < overtrsh2 && i < limit11; i++)
    {
        strip2[i] = CRGB(125, 0, 255);
    }
    for (int i = 43; i < overtrsh2 && i < limit12; i++)
    {
        strip2[i] = CRGB::Fuchsia;
    }
    for (int i = 54; i < overtrsh2 && i < limit13; i++)
    {
        strip2[i] = CRGB(255, 0, 77);
    }
    for (int i = 65; i < overtrsh2 && i < limit14; i++)
    {
        strip2[i] = CRGB::Red;
    }
    for (int i = 76; i < overtrsh2 && i < NUM_LEDS; i++)
    {
        strip2[i] = CRGB::DarkRed;
    }
    for (int i = NUM_LEDS - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
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
    FastLED.setBrightness(BRIGHTNESS);
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
    for (int i = 0; i < overtrsh && i < 24; i++)
    {
        strip1[i] = CRGB(20, 201, 189);
       
    }
    for (int i = 24; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::Fuchsia;
       
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i].fadeToBlackBy(2);
    }
#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < 15; i++)
    {
        strip2[i] = CRGB::Fuchsia;
       
    }
    for (int i = 15; i < overtrsh && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(20, 201, 189);
           }
    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i].fadeToBlackBy(2);
    }
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
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(128, 0, 2);
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
#pragma endregion

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(128, 0, 2);
    }
    for (int i = NUM_LEDS2 - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB(0, 0, 0);
    }

#pragma endregion
}
#pragma endregion

#pragma region GradientLightBars

#pragma region SynthRainbow
void SynthRain()
{

    //strip1
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB(0, 255, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB(0, 154, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {

        strip1[i] = CRGB(50, 0, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB(125, 0, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB::Fuchsia;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB(255, 0, 77);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB::Red;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB::DarkRed;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i] = CRGB::Black;
        FastLED.show();
        fadeallBars();
        delay(40);
    }

    //strip2
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB::DarkRed;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {

        strip2[i] = CRGB::Red;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(255, 0, 77);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB::Fuchsia;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(125, 0, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(50, 0, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(0, 154, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB(0, 255, 255);
        FastLED.show();
        fadeallBars();
        delay(40);
    }
    for (int i = 0; i < NUM_LEDS2; i++)
    {
        strip2[i] = CRGB::Black;
        FastLED.show();
        fadeallBars();
        delay(40);
    }
}

#pragma endregion

#pragma region LightBars
void LightBars()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        // strip1[i] = CRGB(0,213,255);
        strip1[i] = CRGB::Cyan;
    }
    for (int i = 0; i < NUM_LEDS2; ++i)
    {
        // strip2 [i]=CRGB(255, 0, 128);
        strip2[i] = CRGB::Fuchsia;
    }
    FastLED.show();
}
#pragma endregion

#pragma region SafeSpace
void SafeSpace()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        // strip1[i] = CRGB(0,213,255);
        strip1[i] = CRGB::Yellow;
    }
    for (int i = 0; i < NUM_LEDS2; ++i)
    {
        // strip2 [i]=CRGB(255, 0, 128);
        strip2[i] = CRGB::Yellow;
    }
    FastLED.show();
}
#pragma endregion

#pragma endregion

#pragma region CyberBeats
void CyberBeats(CRGBPalette16 primaryPallet, CRGBPalette16 secondaryPallet)
{
#pragma region maths
    sensorvalue = analogRead(DA); //Read the analog value
    EMA_S = (EMA_a * sensorvalue);
    int overtrsh = (EMA_S - trsh) >> 1;  //Divides by 2
    int overtrsh2 = (EMA_S - trsh) >> 1; //Divides by 2
    int avOvertrsh = (overtrsh + overtrsh2) >> 1;

    if (overtrsh < 0 || overtrsh2 < 0)
    {
        overtrsh = 0;
        overtrsh2 = 0;
    }

    FastLED.setBrightness(avOvertrsh);
    // analogWrite(OutputPin, sensorvalue);
#pragma endregion

#pragma region Color Definitions and LED Limiters
    uint8_t heatindex = random8();
    uint8_t twoHotTwoFurious = random8();

    if (overtrsh > NUM_LEDS || overtrsh2 > NUM_LEDS2)
    {
        overtrsh = NUM_LEDS;
        overtrsh2 = NUM_LEDS2;
    }

#pragma endregion

#pragma region Diagnosis
    Serial.println(overtrsh);
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
#pragma endregion

#pragma region Colors for Strip 1
    if (avOvertrsh <= 75)
    {
        for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
        {
            strip1[i] = ColorFromPalette(primaryPallet, heatindex);
            
        }

        for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
        {
            strip1[i].fadeToBlackBy(2);
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
            strip1[i].fadeToBlackBy(2);
        }
    }
#pragma endregion

#pragma region Colors for Strip2
    if (avOvertrsh <= 75)
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = ColorFromPalette(secondaryPallet, twoHotTwoFurious);
        }

        for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
        {
            strip2[i].fadeToBlackBy(2);
        }
    }
    else
    {
        for (int i = 0; i < overtrsh2 && i < NUM_LEDS2; i++)
        {
            strip2[i] = CRGB::DarkRed;
        }

        for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
        {
            strip2[i].fadeToBlackBy(2);
        }
    }

#pragma endregion
}
#pragma endregion

#pragma endregion

#pragma region Misc

#pragma region Off
void Off()
{
    LEDS.showColor(CRGB(0, 0, 0));
}
#pragma endregion

#pragma region LeftOff
void LeftOff()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        strip1[i] = CRGB::Black;
    }
}
#pragma endregion

#pragma region RightOff
void RightOff()
{
    for (int i = 0; i < NUM_LEDS2; ++i)
    {
        strip2[i] = CRGB::Black;
    }
}
#pragma endregion

#pragma region Misc For other things
void fadeToBlack(int ledNo, int fadeValue)
{
    strip1[ledNo].fadeToBlackBy(fadeValue);
}

void fadeToBlack2(int ledNo, int fadeValue)
{
    strip2[ledNo].fadeToBlackBy(fadeValue);
}

void setPixel(int Pixel, byte red, byte green, byte blue)
{
    // FastLED
    strip1[Pixel].r = red;
    strip1[Pixel].g = green;
    strip1[Pixel].b = blue;
}

void setPixel2(int Pixel, byte red, byte green, byte blue)
{
    // FastLED
    strip2[Pixel].r = red;
    strip2[Pixel].g = green;
    strip2[Pixel].b = blue;
}

void FireEmbers(int red, int green, int blue, int SpeedDelay)
{
    for (int i = 64; i < NUM_LEDS; i++)
    {
        int Pixel = i;
        setPixel(Pixel, red, green, blue);
        FastLED.show();
        delay(SpeedDelay);
        strip1[Pixel].nscale8(4);
    }
    for (int i = NUM_LEDS - 1; i >= 64; i--)
    {
        strip1[i] = CRGB::Black;
    }
}

void simpleLight()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB::Cyan;
    }
}
#pragma endregion

#pragma endregion

#pragma region Fire
void ColorfulFire(CRGBPalette16 gPal)
{
    random16_add_entropy(random());

    // Array of temperature readings at each simulation cell
    static byte heat[NUM_LEDS];
    static byte heat2[NUM_LEDS2];

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }

    for (int i = 0; i < NUM_LEDS2; i++)
    {
        heat2[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS2) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k1 = NUM_LEDS - 1; k1 >= 2; k1--)
    {
        heat[k1] = (heat[k1 - 1] + heat[k1 - 2] + heat[k1 - 2]) / 3;
    }
    for (int k2 = NUM_LEDS2 - 1; k2 >= 2; k2--)
    {
        heat2[k2] = (heat[k2 - 1] + heat[k2 - 2] + heat[k2 - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < SPARKING)
    {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160, 255));
        heat2[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for (int j = 0; j < NUM_LEDS; j++)
    {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        byte colorindex = scale8(heat[j], 240);
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        strip1[pixelnumber] = color;
    }

    for (int j = 0; j < NUM_LEDS2; j++)
    {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        byte colorindex = scale8(heat2[j], 240);
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection2)
        {
            pixelnumber = (NUM_LEDS2 - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        strip2[pixelnumber] = color;
    }
    FastLED.delay(1000 / fps);
}
#pragma endregion

#pragma region Meteor

#pragma region Meteor strip 1
void MeteorLeft(int red, int green, int blue, int size, int tailDecay, boolean randomDecay, int speedDelay)
{
    FastLED.showColor(CRGB::Black);

    for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++)
    {
        // fade brightness all LEDs one step
        for (int j = 0; j < NUM_LEDS; j++)
        {
            if ((!randomDecay) || (random(10) > 5))
            {
                fadeToBlack(j, tailDecay);
            }
        }

        // draw meteor
        for (int j = 0; j < size; j++)
        {
            if ((i - j < NUM_LEDS) && (i - j >= 0))
            {
                setPixel(i - j, red, green, blue);
            }
        }
        FastLED.delay(speedDelay);
    }
}

#pragma endregion

#pragma region Meteor stript 2
void MeteorRight(int red, int green, int blue, int size, int tailDecay, boolean randomDecay, int speedDelay)
{
    FastLED.showColor(CRGB::Black);

    for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++)
    {
        // fade brightness all LEDs one step
        for (int j = 0; j < NUM_LEDS2; j++)
        {
            if ((!randomDecay) || (random(10) > 5))
            {
                fadeToBlack2(j, tailDecay);
            }
        }

        // draw meteor
        for (int j = 0; j < size; j++)
        {
            if ((i - j < NUM_LEDS2) && (i - j >= 0))
            {
                setPixel2(i - j, red, green, blue);
            }
        }
        FastLED.delay(speedDelay);
    }
}
#pragma endregion
#pragma endregion

#pragma region Fading
void fadeall()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(215);
        strip2[i].nscale8(215);
    }
}

void fadeallVibes()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(215);
    }
}

void fadeallVibes2()
{
    for (int i = (NUM_LEDS2)-1; i >= 0; i--)
    {
        strip2[i].nscale8(215);
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
#pragma endregion

#pragma region Patterns

#pragma region ColorPatterns
void colorPatterns(CRGBPalette16 currentPallet, uint8_t colorIndex, uint8_t brightness)
{
    // for (int i = (NUM_LEDS)-1; i >= 0; i--)
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

    for (int i = (NUM_LEDS2)-1; i >= 0; i--)
    {
        strip2[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

    FastLED.delay(1000 / fps);
}
#pragma endregion

#pragma region MeditationTime
void MeditationTime(CRGBPalette16 currentPallet, uint8_t colorIndex, uint8_t brightness)
{
    // for (int i = (NUM_LEDS)-1; i >= 0; i--)
    for (int i = 0; i < NUM_LEDS; i++)
    {
        strip1[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

    for (int i = (NUM_LEDS2)-1; i >= 0; i--)
    {
        strip2[i] = ColorFromPalette(currentPallet, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

    FastLED.delay(1000 / fps);
}
#pragma endregion

#pragma endregion