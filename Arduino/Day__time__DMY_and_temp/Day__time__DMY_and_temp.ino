#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <math.h>
#define ThermistorPIN 0


LiquidCrystal lcd(12,11, 5, 4, 3, 2);


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

float vcc = 4.91;                       // only used for display purposes, if used
                                        // set to the measured Vcc.
float pad = 9850;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 10000;                   // thermistor nominal resistance

float Thermistor(int RawADC) {
  long Resistance;  
  float Temp;  // Dual-Purpose variable to save space.

  Resistance=pad*((1024.0 / RawADC) - 1);
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius  
  return Temp;
}
  

RTC_DS1307 rtc;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!rtc.begin()){
    Serial.println("RTC NOT WORKING");
    while(true);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.begin(16, 2);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  float temp;
    temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius

  
    DateTime now = rtc.now();
    
    Serial.print("Year: ");
    Serial.println(now.year(),DEC);
    Serial.print("Month: ");
    Serial.println(now.month(),DEC);  
    Serial.print("Day: ");
    Serial.print(now.day(),DEC);
    Serial.print(" ");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  
      
    lcd.setCursor(0,0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(" ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
  
    lcd.setCursor (0,1);
    lcd.print(now.day(), DEC);
    lcd.print("/");
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.print(" ");
    lcd.print(temp);
    lcd.print((char)223);
  


  delay(500);

}
