#include <ArduinoJson.h>
#include <VirtualShield.h>
#include <Text.h>
 
VirtualShield shield; // identify the shield
Text screen = Text(shield); // connect the screen
 
void setup()
{
 
   shield.begin(); // begin communication
 
   screen.clear(); // clear the screen
   screen.print("Hello Virtual Shields");
}
 
   void loop()
{
}