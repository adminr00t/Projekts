#include  <LiquidCrystal.h>

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);
int sensorPin = 0;
int tempSetpointPin = 1;

void setup(){
  lcd.begin (16, 2);
  Serial.begin(9600);
  pinMode(8,OUTPUT);
}

void loop(){
    int tempReading = analogRead(sensorPin);
  	int setPoint = analogRead(tempSetpointPin);
  
  	//converting tempReading to a voltage
  	float voltage = tempReading * 5.0;
  	float voltage2 = voltage / 1024.0;
  	float tempC = (voltage2 - 0.5) *100;
 	
  	float potVoltage = setPoint / 5.0;
  	float potVoltage2 = potVoltage / 1024.0 ;
   	float potTemp = (potVoltage2 + .05) * 100 + 10;
  	  
  
      
    //Serial.println(setPoint);
  	//Serial.println(tempReading);
  	Serial.println(tempC);
  	Serial.println(potTemp);
  	//Serial.println(tempReading/setPoint);
  	
  	//Serial.println(setPoint);
  	//Serial.println(setTempPositive);
  	//Serial.println(setTempNegative);
  
  	//Defines then prints temp
  	
  	lcd.setCursor(0,0);
  	lcd.print(tempC);
  	lcd.println("Degrees C");
    
  delay(1000); // Delay a little bit to improve simulation performance


}