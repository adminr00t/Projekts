#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 7
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType currentBlending;

CRGBPalette16 vibeFlame;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup()
{
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    FastLED.setBrightness(255);

    
    vibeFlame = CRGBPalette16(CRGB::DarkRed, CRGB::DeepPink, CRGB::Fuchsia, CRGB(20, 201, 189));
}

void loop()
{
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

    FillLEDsFromPaletteColors(startIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = 255;

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = ColorFromPalette(vibeFlame, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
