#include <LiquidCrystal.h>
#include <LCDKeypad.h>
LCDKeypad lcd;


int in_message_started = 0;
int in_message_completed = 0;

int System = -1;
int SubSystem = -1;
int Component = -1;
int DiagType = -1;
int Level = -1;
int DiagMessage = -1;
String Description = "";
String in_message;
void setup() {
  Serial.begin(115200);
  lcd.clear();
  delay(2000);
  Serial.println("BOOTED");

}

void loop() {
  if(in_message_completed == 1)
  {
    if(in_message.substring(0,5) == "$GH13")
    {
      System = in_message.substring(5,6).toInt();
      SubSystem = in_message.substring(6,7).toInt();
      Component = in_message.substring(7,8).toInt();
      DiagType = in_message.substring(8,9).toInt();
      Level = in_message.substring(9,10).toInt();
      DiagMessage = in_message.substring(10,11).toInt();
      Description = in_message.substring(11,in_message.length()-1);
      Serial.print(System);
      Serial.print(",");
      Serial.print(SubSystem);
      Serial.print(",");
      Serial.print(Component);
      Serial.print(",");
      Serial.print(DiagType);
      Serial.print(",");
      Serial.print(Level);
      Serial.print(",");
      Serial.print(DiagMessage);
      Serial.print(",");
      Serial.print(Description);
      Serial.print("xxx");
      Serial.print(in_message.length());
      Serial.println();
      lcd.clear();
      lcd.setCursor(0,1);
      //lcd.print(in_message);

      lcd.print(System);
      lcd.print(SubSystem);
      lcd.print(Component);
      lcd.print(DiagType);
      lcd.print(Level);
      lcd.print(DiagMessage);
      //lcd.print(Description);
    }
    
    
    in_message = "";
    in_message_completed = 0;
  }
  //Serial.print("xxxHello,world!\r\n");
  /*
  if(Serial.available())
  {
    char ch = Serial.read();
    if(ch == '\r')
    {
      msg_buffer[bufferIndex] = 0;
      bufferIndex = 0;
      
      in_message_ready = 1;
    }
    else
    {
      msg_buffer[bufferIndex++] = ch;
    }
  }
  
  
  if(in_message_ready == 1)
  {
    lcd.setCursor(0,1);
    lcd.println(msg_buffer);
    Serial.println(msg_buffer);
    in_message_ready = 0;
  }
  */
  delay(1);
}
void serialEvent()
{
  while((Serial.available() > 0) && (in_message_completed == 0))
  {
    char inChar = (char)Serial.read();
    if(inChar == '$')
    {
      in_message_started = 1;
    }
    if(in_message_started == 1)
    {
      in_message += inChar;
    }
    if(inChar == '*')
    {
      in_message_completed = 1;
      in_message_started = 0;
    }
  }
}

