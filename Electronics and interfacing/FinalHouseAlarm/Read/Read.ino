#include <EEPROM.h>
void setup()
{
Serial.begin(9600);
}
void loop()
{
   for (int i=0;i<8;i++)
  {
      
     Serial.print(EEPROM.read(i));
  }
  Serial.println();
  delay(500);
}
