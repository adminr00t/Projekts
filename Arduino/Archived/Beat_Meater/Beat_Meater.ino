int DO = 1; //Pin for Digital Output - DO
int DA = 0; // Pin for Analog Output - AO
int trsh = 760; //Set minimum threshold for LED lit
int trsh2 = 780;
int trsh3 = 800;
int trsh4 = 840;
int trsh5 = 870;
int sensorvalue = 0;
float EMA_a = 0.6;
int EMA_S = 0;

 
void setup() {
  Serial.begin(9600);
  pinMode(1, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  EMA_S = analogRead(DA);
}
 
void loop() {
  sensorvalue = analogRead(DA);  //Read the analog value
  EMA_S = (EMA_a*sensorvalue) + ((1-EMA_a)*EMA_S);
  Serial.println(EMA_S);
 
  if (sensorvalue >= trsh) { //Compare analog value with threshold
    digitalWrite(4,HIGH);
  }
  else {
    digitalWrite(4, LOW);
  }
  if (sensorvalue >= trsh2){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }else{
    digitalWrite(5, LOW);
  }
    if (sensorvalue >= trsh3){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }else{
    digitalWrite(6, LOW);
  }
    if (sensorvalue >= trsh4){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  }else{
    digitalWrite(7, LOW);
  }
  if (sensorvalue >= trsh5){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);    
  }else{
    digitalWrite(8, LOW);
  }
  if (sensorvalue <= trsh){
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    }
}
