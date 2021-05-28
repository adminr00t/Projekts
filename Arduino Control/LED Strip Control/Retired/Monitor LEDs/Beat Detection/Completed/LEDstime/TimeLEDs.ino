#include <FastLED.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <math.h>

#pragma region LED constants
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

#pragma region Other constants
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

float vcc = 4.91;     // only used for display purposes, if used
                      // set to the measured Vcc.
float pad = 9850;     // balance/pad resistor value, set this to
                      // the measured resistance of your pad resistor
float thermr = 10000; // thermistor nominal resistance

#pragma endregion

#pragma region Variables
#define DATA_PIN 6
#define DATA_PIN2 4
#define NUM_LEDS 104
#define BRIGHTNESS 25
#define ThermistorPIN 1
int DO = 2;    //Pin for Digital Output - DO
int DA = 0;    // Pin for Analog Output - AO
int trsh = 35; //Set minimum threshold for LED lit
#pragma endregion

#pragma region Strip Segments and Definitions
CRGB strip1[NUM_LEDS];
#pragma endregion

#pragma region thermistor Definition
float Thermistor(int RawADC)
{
    long Resistance;
    float Temp; // Dual-Purpose variable to save space.

    Resistance = pad * ((1024.0 / RawADC) - 1);
    Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
    Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
    Temp = Temp - 273.15; // Convert Kelvin to Celsius
    return Temp;
}
#pragma endregion

#pragma region RTC
RTC_DS1307 rtc;
#pragma endregion

void setup(){
#pragma region Misc
    Serial.begin(38400);
    pinMode(2, INPUT);
    pinMode(13, OUTPUT);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(strip1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    // FastLED.setBrightness(BRIGHTNESS);

    EMA_S = analogRead(DA);
#pragma endregion

#pragma region Color LED Initialization
    LEDS.showColor(CRGB(255, 0, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 255, 0));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 255));
    delay(500);
    LEDS.showColor(CRGB(0, 0, 0));
#pragma endregion

#pragma region RTC and LCD Initialization
    if (!rtc.begin())
    {
        Serial.println("RTC NOT WORKING");
        while (true)
            ;
    }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    lcd.begin(16, 2);
#pragma endregion
}

void fadeall1(){
    for (int i = (NUM_LEDS)-1; i >= 0; i--)
    {
        strip1[i].nscale8(220);
    }
}

void loop(){
    digitalWrite(13, HIGH);
    DateTime now = rtc.now();
    int m = now.minute();
    int h = now.hour();
    int s = now.second();
    float temp;
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
    if (overtrsh > NUM_LEDS)
    {
        overtrsh = NUM_LEDS;
    }
#pragma endregion

#pragma region Diagnosis
    #pragma region LEDS
    // Serial.println(overtrsh);
    // Serial.println(sensorvalue);
    // Serial.println(color3);
    // Serial.println(avOvertrsh);
    // Serial.println(EMA_S);
    #pragma endregion

    #pragma region Date and times
    Serial.print("Year: ");
    Serial.println(now.year(), DEC);
    Serial.print("Month: ");
    Serial.println(now.month(), DEC);
    Serial.print("Day: ");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(" ");
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    #pragma endregion
#pragma endregion

#pragma region Colors for Strip 1
    for (int i = 0; i < overtrsh && i < NUM_LEDS; i++)
    {
        strip1[i] = CRGB(color3, color1, color2);
        fadeall1();
    }
    for (int i = NUM_LEDS - 1; i > overtrsh - 1 && i >= 0; i--)
    {
        strip1[i] = CRGB(0, 0, 0);
    }
#pragma endregion
FastLED.show();

#pragma region RTC and Temp

temp = Thermistor(analogRead(ThermistorPIN)); // read ADC and  convert it to Celsius
#pragma endregion

#pragma region LCD
lcd.setCursor(0, 0);
lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
lcd.print("    ");
lcd.print(now.hour(), DEC);
lcd.print(':');
lcd.print(now.minute(), DEC);
//lcd.print(':');
//lcd.print(now.second(), DEC);

lcd.setCursor(0, 1);
lcd.print(now.day(), DEC);
lcd.print("/");
lcd.print(now.month(), DEC);
lcd.print('/');
lcd.print(now.year(), DEC);
lcd.print("  ");
lcd.print(temp);
lcd.print((char)223);
#pragma endregion
}