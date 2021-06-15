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
#pragma endregion

void setup()
{
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
void fadeall1()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(215);
    }
}

void fadeall2()
{
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip2[i].nscale8(215);
    }
}
#pragma endregion

void loop()
{
    // EC1();
    // EC2();
    // EC250();
    // EC3();
    // EC4();
    // EC401();
    EC420();
    FastLED.show();
}

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

#pragma region Colors for Strip2
    for (int i = 0; i < overtrsh2 && i < 62; i++)
    {
        strip2[i] = CRGB(color1, color2, color3);
        fadeall2();
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
        fadeall1();
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
        fadeall2();
    }

    for (int i = NUM_LEDS2 - 1; i > overtrsh2 - 1 && i >= 0; i--)
    {
        strip2[i] = CRGB::Black;
    }
#pragma endregion
}