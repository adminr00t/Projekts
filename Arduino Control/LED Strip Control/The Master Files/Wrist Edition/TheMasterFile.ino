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
#define NUM_LEDS 18
#define FireLEDS 18
#define BRIGHTNESS 75
#define fps 25
#define COOLING 55
#define SPARKING 120
int DO = 2;    //Pin for Digital Output - DO
int DA = 0;    // Pin for Analog Output - AO
int trsh = 55; //Set minimum threshold for LED lit
uint8_t gHue = 0;
CRGBPalette16 currentPallet;
TBlendType currentBlending;
#pragma endregion

#pragma region Strip Segments and Definitions
CRGB strip1[NUM_LEDS];

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
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    EMA_S = analogRead(DA);

    currentBlending = LINEARBLEND;
    currentPallet = RainbowColors_p;
#pragma endregion

#pragma region Color Initialization
    LEDS.showColor(CRGB(255, 0, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 255, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 255));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 0));
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
    // Off();
    // SynthRainbow();
    // LightBars();

    colorPatterns(colorsOfCyber, startIndex, 200);
    // ColorfulFire(patternOfSynth);
    // simpleLight();
    // MeteorLeft(4, 185, 244, 5, 64, true, 50);

    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
}

#pragma region Moods

#pragma region GradientLightBars

#pragma region SynthRainbow
void SynthRainbow()
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
        FastLED.show();
    }
#pragma endregion
#pragma endregion

#pragma endregion

#pragma region Misc

#pragma region Off
    void Off()
    {
        LEDS.showColor(CRGB(0, 0, 0));
    }
#pragma endregion

#pragma region Misc For other things
    void fadeToBlack(int ledNo, int fadeValue)
    {
        strip1[ledNo].fadeToBlackBy(fadeValue);
    }

    void setPixel(int Pixel, byte red, byte green, byte blue)
    {
        // FastLED
        strip1[Pixel].r = red;
        strip1[Pixel].g = green;
        strip1[Pixel].b = blue;
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

        // Step 1.  Cool down every cell a little
        for (int i = 0; i < 18; i++)
        {
            heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / 18) + 2));
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for (int k1 = 18 - 1; k1 >= 2; k1--)
        {
            heat[k1] = (heat[k1 - 1] + heat[k1 - 2] + heat[k1 - 2]) / 3;
        }

        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if (random8() < SPARKING)
        {
            int y = random8(7);
            heat[y] = qadd8(heat[y], random8(160, 255));
        }

        // Step 4.  Map from heat cells to LED colors
        for (int j = 0; j < 18; j++)
        {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            byte colorindex = scale8(heat[j], 240);
            CRGB color = ColorFromPalette(gPal, colorindex);
            int pixelnumber;
            if (gReverseDirection)
            {
                pixelnumber = (18 - 1) - j;
            }
            else
            {
                pixelnumber = j;
            }
            strip1[pixelnumber] = color;
        }
        FastLED.delay(1000 / fps);
    }
#pragma endregion

#pragma region Meteor

#pragma region Meteor strip 1
    void MeteorLeft(int red, int green, int blue, int size, int tailDecay, boolean randomDecay, int speedDelay)
    {
        FastLED.showColor(CRGB::Black);

        for (int i = 0; i < 18 + 18; i++)
        {
            // fade brightness all LEDs one step
            for (int j = 0; j < 18; j++)
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
#pragma endregion

#pragma region Fading
    void fadeall()
    {
        for (int i = (NUM_LEDS)-1; i >= 0; i--)
        {
            strip1[i].nscale8(215);
        }
    }

    void fadeallVibes()
    {
        for (int i = (NUM_LEDS)-1; i >= 0; i--)
        {
            strip1[i].nscale8(215);
        }
    }

    void fadeallBars()
    {
        for (int i = (NUM_LEDS)-1; i >= 0; i--)
        {
            strip1[i].nscale8(250);
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
        FastLED.delay(1000 / fps);
    }
#pragma endregion

#pragma endregion