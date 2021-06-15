#include  <LiquidCrystal.h> //library for LCD
#include <math.h>
#define ThermPIN 0
#define tempSetpointPin 1

LiquidCrystal lcd (12, 11, 5, 4, 3, 2); //LCD pins

float resistorValue = 9850;       

enum led {
  BLUE = 10,
  GREEN = 9,
  RED = 8,
  NONE = 0
};
// Enumeration, makes it easier to read and maintain. Stores the pin number that controls the LED of the specified colour
led cur_led = NONE;
         
float Therm(int RawADC) {
  long R;//resistance  
  float Temp;  // Dual-Purpose variable to save space.

  R=resistorValue*((1024.0 / RawADC) - 1);// ADC = Analog->Digital Converter, converts the raw analog data into readable digital data
  Temp = log(R); // R = Thermistor resistance, uses logarithmic mathematical function
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp)); //Steinhart-Hart Equation; Temp = 1 / (A + Bln(Rt) + Cln (Rt)^3 where A, B and C are measured constants, Rt is resistance of Thermistor
  Temp = Temp - 273.15;  // Kelvin -> Celsius 
  return Temp;// returns the final measured temperature in Celsius 
}



void setup(){
  lcd.begin (16, 2);// sets LCD cursor
  Serial.begin(9600);// begins serial
  pinMode(8, OUTPUT);// sets the pin as voltage outputs rather than inputs
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop(){

    //Useful Maths
  	int setPoint = analogRead(tempSetpointPin); // determines the raw resistance value of the Pot
  	float potResistance = (setPoint / 1023.0);
    int targetTemp = ((potResistance * 15.0) + 15.5);// (Pv * lowest setpoint)+ (Lowest setpoint + .5)
    int currentTemp = Therm(analogRead(ThermPIN));
    int difference = currentTemp - targetTemp;
    float VoltDegree = .95 / 257.5; // Vmax - Vmin / Angle Max - Angle Min = Voltage per Degree
    float theta = potResistance / VoltDegree; // amount of degrees the Pot has turned
  
  	 	
    //LCD print outs
    lcd.setCursor(0,0);
    lcd.print("Target: ");
    lcd.print(targetTemp);
    lcd.print(" deg C");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.print(currentTemp);
    lcd.print(" deg C");
    
    //Serial bug and math checks
    Serial.print("Ambient Temp: ");
    Serial.print(currentTemp); 
    Serial.print("\r\n");
    Serial.print("Target Temp: ");
    Serial.print(targetTemp);
    Serial.print("\r\n");
    Serial.print("Difference: ");
    Serial.print(difference);
    Serial.print("\r\n");
    Serial.print("Pot Resistance: ");
    Serial.print(potResistance); //1 = 10k ohms, 0 = 0 ohms
    Serial.print("\r\n");
    Serial.print("Voltage per Degree turned: ");
    Serial.print(VoltDegree, 4);
    Serial.print("\r\n");
    Serial.print("Degrees turned: ");
    Serial.print(theta);
    Serial.print("\r\n");
    Serial.print("\r\n");



    //the "logic" happens below
    led new_led;
    if (difference < -2) {
    	new_led = BLUE;//"selects" pin 10
    } else if (-2 <= difference && difference <= 2) {
        new_led = GREEN;//"selects" pin 9
    } else if (2 < difference) {
        new_led = RED;//"selects" pin 8
    }
    //determines if difference is more than 2 or less than -2, if so, sends voltage to Red, blue LEDs. IF difference is -2<= or <=2, then it "selects" the Green LED
   
    if (new_led != cur_led) {
        digitalWrite(cur_led, LOW);//sends 0 Volts to current LED
        digitalWrite(new_led, HIGH);  //sends 5 Volts to new LED
        cur_led = new_led; 
    }//here the code enables new LED to be current LED only if new LED does not = current LED 
  
    delay(5000); // Delays by 5 seconds
}
