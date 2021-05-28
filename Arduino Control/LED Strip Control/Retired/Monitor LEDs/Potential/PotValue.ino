#include <FastLED.h>
#define NumLEDS 104
#define DataPin 6
#define LEDtype WS2812B
#define ColorOrder GRB
#define Brightness 50
#define fps 120
CRGB leds[NumLEDS];

int potPin = 2;  // select the input pin for the potentiometer
// int ledPin = 13; // select the pin for the LED
int val = 0;     // variable to store the value coming from the sensor
float EMA_a = 0.6;
int EMA_S = 0;
int sensitivity = 10;

void setup()
{
    // pinMode(ledPin, OUTPUT); // declare the ledPin as an OUTPUT
    Serial.begin(115200);
}

void loop()
{
    val = analogRead(potPin);   // read the value from the sensor
    EMA_S = (EMA_a * val);
    int usableValue = (EMA_S - sensitivity) >> 1;
    Serial.println(usableValue);
}