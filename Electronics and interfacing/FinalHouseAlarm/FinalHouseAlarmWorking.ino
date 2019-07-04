// Master Password is The Password backwards
// The circuit:
//  * VCC connection of the sensor attached to +5V
//  * GND connection of the sensor attached to ground
//  * TRIG connection of the sensor attached to digital pin 2
//  * ECHO connection of the sensor attached to digital pin 4

#include <LiquidCrystal.h>
#include <IRremote.h>
#include <TonePlayer.h>
#include <EEPROM.h>


TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);  // pin D9 (Uno), D11 (Mega)
const int rs = 13, en = 11, d4 = 5, d5 = 6, d6 = 3, d7 = 1;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 2;
const int echoPin = 4;
int i = 0;
int buzzerPin = 9; //digital 12
int buttonPin = 7;
int Armed = 1;
boolean previousAlarmState;
boolean state = 0;

int PasswordArray[7];

int tpassword [7];
char trig = 'n';
int receiver = 8;
long previousMillis = 0;    // Store last update
long interval = 500;        // First length of time I want the buzzer to stay on set tone
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
 
void setup() 
{   
  for (int i=0;i<4;i++)
  {
    PasswordArray[i]= EEPROM.read(i);              // Reads every value in EEPROM into Array
    }
    
//  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("t");
  //delay(500);
  //lcd.clear();
  //delay(1000);
//  lcd.print("t");
  //delay(500);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode (buzzerPin, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver;
    // set up the LCD's number of columns and rows:
  
  
  
  
} 
void loop() 
{  
    EEPROMSetup();                                     //checks if password values are all 0, which means this is first startup
  //If button is pressed this should arm the alarm

  
  if ( Armed== LOW && state == 1 && trig == 'y')
  {
    
    if (millis() - previousMillis > interval)    
      {
       ;
       tone1.noTone ();
       tone1.tone (700);
       delay (500);
       tone1.noTone ();
      }
      remote();
  }
   
  if ( Armed== HIGH && state ==0)
  {
    isUnarmed();
  }

  if ( Armed== LOW && state == 1)
  {
    isarmed();
  }

    
  
}
void remote()
{
  
  //  Serial.println(results.value, HEX);  //UN Comment to see raw values
    Serial.println("Enter next Password");
     
    
    
   for(int i=0;i<4;)
   {
    while (i<4)
    {
     
      delay(500);
      if (irrecv.decode(&results)) // have we received an IR signal?
      {        
        tone1.noTone ();
        tone1.tone (900);
        delay (500);
        tone1.noTone ();
        irrecv.resume(); // receive the next value
        tpassword[i]=translateIR();
        if(tpassword[i]!=11)// Is signal the void?
             {
              i++;
             }
        else     
        Serial.println("Enter number again ");
      }
     if (millis() - previousMillis > interval &&Armed== LOW && state == 1 && trig == 'y')    
      {
       
       tone1.noTone ();
       tone1.tone (440);
       delay (500);
       tone1.noTone ();
      }

     
    }
    //tpassword[i]='i';
     
     
   }
   
  Serial.println();  
  Serial.println("PW IS: ");
  for(int i=0;i<4;i++)
  {
    Serial.print(tpassword[i]);
  }
  Serial.println();

   if(tpassword[0]==PasswordArray[0]&&tpassword[1]==PasswordArray[1]&&tpassword[2]==PasswordArray[2]&&tpassword[3]==PasswordArray[3] )
  {
    if(state == 0 && Armed ==HIGH)
    {
      Serial.println("correct password arming");
     Armed = LOW;
     state = 1;
    }
    else
    {
      Serial.println("correct password");
     Armed = HIGH;
     state = 0;
    }
     
  }
  else if( tpassword[0]==PasswordArray[3]&&tpassword[1]==PasswordArray[2]&&tpassword[2]==PasswordArray[1]&&tpassword[3]==PasswordArray[0] )
  {
     if(state == 0 && Armed ==HIGH)
    {
      Serial.println("correct password arming");
     Armed = LOW;
     state = 1;
    }
    else
    {
      Serial.println("correct password");
     Armed = HIGH;
     state = 0;
    }
  }
  else if(trig =='y')
  {
  Serial.println("Incorrect password");
   
  }
  else
  {
  Serial.println("Incorrect password");
   Serial.println("Press Button / Use Remote To Arm");
  }
}

void findDistance()
{
   pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
}


long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
 
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}   
  

boolean isIntruderPresent() 
  { 
    long duration, inches, cm;
    findDistance();


  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  /*Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();*/
  
  delay(200);
    if(cm > 50)
    return true;
    else
    return false; 
   }

void alarmDisarmed() // if door is closed
{   
  Serial.println("Disarmed");
  
  
  for(i = 0; i <= 10; i++)
        {
           
            //tone(buzzerPin, 200, 25);
            delay(100);
            
            //tone(buzzerPin, 200, 50);
            delay(100);
        }
  
  
} 
 
void alarmTriggered() //This should only check iif the door is open 
{   
  Serial.println("Intruder Alert!!");
  trig = 'y';  //turns on the buzzer  
 
} 
void isarmed()
{
   boolean newAlarmState = isIntruderPresent();
    if(newAlarmState != previousAlarmState && newAlarmState== 0)
       if(newAlarmState)     
      alarmDisarmed(); 
    else  
      alarmTriggered();
      previousAlarmState = newAlarmState;    
}
void isUnarmed()
{
  Serial.println("Press Button / Use Remote To Arm ");
    while (Armed == HIGH)
    {
      
      Armed = digitalRead(buttonPin);
      
    
      
      if (irrecv.decode(&results)) // have we received an IR signal?
      {
        state =0;
        irrecv.resume(); // receive the next value
        tpassword[0]=translateIR();
        if(tpassword[0]==99)// Is signal the power button?
        {
        
          remote();// Enter passcode
             
        }
       /*  if(tpassword[0]==2)
        {
          SetSecondPassword();
        }*/
        
      }
         
      //Armed= LOW;
      state=1; //change flag variable again 
    }
     Serial.println("Arming");

    for(int j=0;j<20;j++)// Change to 20
    {
     Serial.println(j);
     tone1.tone (110);  // frequency of the tone Hz
     delay (500);
     tone1.noTone ();
     delay(500);
    } 

    
     Serial.println("Doors have now been locked and System is Armed !!");
     tone1.tone (440);
     delay (500);
     tone1.noTone ();

     tone1.tone (880);
     delay (500);
     tone1.noTone ();
     
  

      //delay(1000);
}

char translateIR() // takes action based on IR code received

// describing Car MP3 IR codes 

{

  switch(results.value)

  {

  case 0xFFA25D:  
    Serial.println("PWR"); 
    return 99;
  case 0xE318261B:  
    Serial.println("PWR"); 
    return 99;

  case 0x511DBB:  
    Serial.print(" VOL+           "); 
    break;

  case 0xEE886D7F:  
    Serial.print(" FUNC/STOP             "); 
    break;

  case 0x52A3D41F:  
    Serial.print(" PREV            "); 
    break;

  case 0xD7E84B1B:  
    Serial.print(" PLAY/PAUSE           "); 
    break;

  case 0x20FE4DBB:  
    Serial.print(" NEXT           "); 
    break;

  case 0xF076C13B:  
    Serial.print(" DOWN     "); 
    break;

  case 0xFFA857:  
    Serial.print(" VOL-           "); 
    break;

  case 0xE5CFBD7F:  
    Serial.println(" UP             "); 
    break;

  case 0xC101E57B:  
    Serial.print("0"); 
    return 0;
    
  case 0xFF6897:  
    Serial.print("0"); 
    return 0;
    

  case 0x97483BFB:  
    Serial.print(" EQ           "); 
    break;

  case 0xF0C41643:  
    Serial.print(" ST/REPT           "); 
    break;

  case 0x9716BE3F:  
    Serial.print("1");
    return 1; 
    
  case 0xFF30CF:  
    Serial.print("1");
    return 1; 
    

  case 0x3D9AE3F7:  
    Serial.print("2"); 
    return 2;
  case 0xFF18E7:  
    Serial.print("2"); 
    return 2;

  case 0x6182021B:  
    Serial.print("3"); 
    return 3;
  case 0xFF7A85:  
    Serial.print("3"); 
    return 3;
    
  case 0x8C22657B:  
    Serial.print("4"); 
    return 4;
  case 0xFF10EF:  
    Serial.print("4"); 
    return 4;

  case 0x488F3CBB:  
    Serial.print("5"); 
    return 5;
  case 0xFF38C7:  
    Serial.print("5"); 
    return 5;
    
  case 0x449E79F:  
    Serial.print("6"); 
    return 6;
  case 0xFF5AA5:  
    Serial.print("6"); 
    return 6;

  case 0x32C6FDF7:  
    Serial.print("7"); 
    return 7;
  case 0xFF42BD:  
    Serial.print("7"); 
    return 7;
    
  case 0x1BC0157B:  
    Serial.print("8"); 
    return 8;
  case 0xFF4AB5:  
    Serial.print("8"); 
    return 8;
    
  case 0x3EC3FC1B:  
    Serial.print("9"); 
    return 9;
  case 0xFF52AD:  
    Serial.print("9"); 
    return 9;
      
  /*case 0xFFFFFFFF:  
    Serial.println("             "); 
    return '0';

  case 0xFF:  
    Serial.println("             "); 
    return '0';*/
    
  default: 
    Serial.println("void");
    return 11;

  }

  delay(500);


}
////////////////////////////////////////////
/*void clearEEPROM()                                    //Clears all memory
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    if(EEPROM.read(i) != 0)                             //skip already "empty" addresses
    {
      EEPROM.write(i, 0);                               //write 0 to address i
    }
   Password=0;
  }
  Serial.println("Passwords erased");
}


void SaveToEEPROM (int Pos,int EnteredPassword )         //saves Password to Memory
{
   EEPROM.write(Pos, EnteredPassword);                   //Writes the password to the desired position on the EEPROM 
}


Void bool IsPasswordCorrect(int Pos ,int EnteredPassword) // Validates entered password
{
  int CorrectPassword = EEPROM.read(Pos);                 //reads memory at specified position
  if (EnteredPassword = CorrectPassword)                  //If password match
  {
  return true;
  }
  if (EnteredPassword != CorrectPassword)                 //if passwords do not match
  {
  return false;
  } 
}
*/

void EEPROMSetup()                                       // if the program is setup for the first time with no existing password
{               
 int PasswordTally=0;                                 //Used to add up sum of all numbers in password array
 for (int i=0;i<4;i++)
  {
    PasswordTally =PasswordTally + PasswordArray[i];  //Adds all values in the eeprom together
   }

  if  (PasswordTally == 0)                          // if the sum of all passwords is 0 
   {
     SetFirstPassword();                             // method that sets arraypassword values to whatever is entered on IR remote            
          for(int i=0;i<4;i++)
          {
            EEPROM.write(i, PasswordArray[i]);         // Writes first password into eeprom
           }
              Serial.println("Password Saved");
        }    
   
    }


void SetFirstPassword()
{ //int PasswordTally=0;
   Serial.println("Please enter password 1"); 
   for(int i=0;i<4;)
   {
     // Serial.println("Enter next Password 1 number");
      delay(800);
      if (irrecv.decode(&results)) // have we received an IR signal?
      {
        tone1.noTone ();
        tone1.tone (900);
        delay (200);
        tone1.noTone ();
        irrecv.resume(); // receive the next value
        PasswordArray[i]= translateIR();                     // Sets first 4 values of array 
        if(PasswordArray[i]!=11)// Is signal the void?
             {
              i++;
             }
        else     
        Serial.println("Enter number again ");
        delay (500);
        
      }
   }
     for(int i=0;i<4;i++)
     {
      Serial.println(); 
      Serial.print("PW IS: ");
      Serial.print(PasswordArray[i]);                          //Print first password
      } 
         
     }
  /*  for (int i=0;i<8;i++)
      { 
        PasswordTally =PasswordTally + PasswordArray[i];  //Adds all values in the eeprom together
      }
    if (PasswordTally == 0)                          // if the sum of all passwords is 0 
      { Serial.print("Password cannot be 0000");
        EEPROMSetup(); 
       }
       */



void SetSecondPassword()
{ //int PasswordTally=0;
   Serial.println("Please enter password 2 "); 
   for(int i=4;i<8;)
   {
      delay(800);
      if (irrecv.decode(&results)) // have we received an IR signal?
      {
        tone1.noTone ();
        tone1.tone (900);
        delay (200);
        tone1.noTone ();
        irrecv.resume(); // receive the next value
        PasswordArray[i]= translateIR();                     // Sets last 4 values of array 
        delay (500);
        i++;
      }
   }
     for(int i=4;i<4;i++)
     {
      Serial.print(PasswordArray[i]);                          //Print second password
      } 
      Serial.println();    
     }



