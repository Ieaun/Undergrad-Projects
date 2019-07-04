#include <EEPROM.h>
byte Password=0;
int Pos=0;

void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() 
{
  // put your main code here, to run repeatedly:
  for (int i=0;i<8;i++)
  {
     EEPROM.write(i,0);
     delay(500);
     Serial.println(EEPROM.read(0));
  }
}

///////////////////////////////







 
