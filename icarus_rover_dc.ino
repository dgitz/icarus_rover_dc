#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include "Definitions.h"
#include <elapsedMillis.h>
LCDKeypad lcd;

#define PIN_RED 2 //OK:2,3,
#define PIN_BLUE 3
#define BLINK_TIME 1000  //MilliSeconds

bool RED_STATE = false;
bool BLUE_STATE = false;

int in_message_started = 0;
int in_message_completed = 0;
bool temp_state = false;
int System = -1;
int SubSystem = -1;
int Component = -1;
int DiagType = -1;
int Level = -1;
int DiagMessage = -1;

int Pose_Valid = 0;
int Armed_State = 0;
String Description = "";
String in_message;
elapsedMillis timeElapsed_Blue;
elapsedMillis timeElapsed_Red;

int MC_Node_State = MC_NODE_UNKNOWN;
void setup() {
   pinMode(PIN_RED,OUTPUT);
  pinMode(PIN_BLUE,OUTPUT);
  delay(100);
  digitalWrite(PIN_RED,true);
  digitalWrite(PIN_BLUE,true);
  Serial.begin(115200);
  lcd.clear();
  delay(4000);
  lcd.print("BOOTED");
  Serial.println("BOOTED");
 digitalWrite(PIN_RED,false);
  digitalWrite(PIN_BLUE,false);

}

void loop() {
  Serial.print("R:");
  Serial.print(timeElapsed_Red);
  Serial.print("B:");
  Serial.print(timeElapsed_Blue);
  Serial.print("   ");
  Serial.print(RED_STATE);
  Serial.print("   ");
  Serial.println(BLUE_STATE);
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
      
      //lcd.print(in_message);
  
      /*lcd.print(System);
      lcd.print(SubSystem);
      lcd.print(Component);
      lcd.print(DiagType);
      lcd.print(Level);
      lcd.print(DiagMessage);*/
      
    }
    
    
    in_message = "";
    in_message_completed = 0;
    if(System == ROVER)
    {
      if(SubSystem == ROBOT_CONTROLLER)
      {
        if(Component == MOTION_CONTROLLER_NODE)
        {
          if(DiagType == NO_ERROR)
          {
            if(DiagMessage == INITIALIZING)  //MC Node is still booting.  Not Safe to Arm.
            {
               MC_Node_State = MC_NODE_NOT_AVAILABLE; 
            }
            else if(DiagMessage == NO_ERROR)
            {
              MC_Node_State = MC_NODE_READY;
            }
          }
          else if(DiagType == SENSORS)
          {
            if(DiagMessage == DEVICE_NOT_AVAILABLE) //GPS Position Not Available.  Not Safe to ARM
            {
              /*lcd.clear();
              lcd.setCursor(0,1);
              lcd.print(Description);*/
              //MC_Node_State = MC_NODE_NOT_AVAILABLE; 
              Pose_Valid = 0;
            }
            else if(DiagMessage == NO_ERROR) //GPS Position is Available.  Safe to Arm
            {
              /*lcd.clear();
              lcd.setCursor(0,1);
              lcd.print(Description);*/
              Pose_Valid = 1;
              //MC_Node_State = MC_NODE_READY;
              //MC_Ready_Once = 1;
            }
          }
          else if(DiagType == REMOTE_CONTROL)
          {
            if(DiagMessage == ROVER_ARMED)
            {
              Armed_State = 1;
            }
            else if(DiagMessage == ROVER_DISARMED)
            {
              Armed_State = 0;
            }
          }
        }
      }
    }
  }

  if(MC_Node_State == MC_NODE_UNKNOWN) 
  { 
    lcd.clear();
    lcd.setCursor(0,1);
    digitalWrite(PIN_RED,false); 
    digitalWrite(PIN_BLUE,false); 
    
    lcd.print("MC_NODE_UNKNOWN");
    //MC_Node_State = MC_NODE_READY;
  }
  else if(MC_Node_State == MC_NODE_READY) 
  {
    
      //digitalWrite(PIN_RED,true); 
      /*lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("MC_NODE_READY");*/
    
    if(Pose_Valid == 0)
    {
      if (timeElapsed_Blue > BLINK_TIME) 
      {  
        BLUE_STATE = !BLUE_STATE;     
        //ledState = !ledState;    // toggle the state from HIGH to LOW to HIGH to LOW ... 
        digitalWrite(PIN_BLUE, BLUE_STATE);
        timeElapsed_Blue = 0;       // reset the counter to 0 so the counting starts over...
      }
      lcd.clear();
      lcd.setCursor(0,1); 
      lcd.print("POSE NOT READY");
    }
    else if(Pose_Valid == 1)
    {
      digitalWrite(PIN_BLUE, true);
      lcd.clear();
      lcd.setCursor(0,1); 
      lcd.print("POSE READY");
    }
    if(Armed_State == 0)
    {
      if (timeElapsed_Red > BLINK_TIME) 
      {       
        RED_STATE = !RED_STATE;  
        //ledState = !ledState;    // toggle the state from HIGH to LOW to HIGH to LOW ... 
        digitalWrite(PIN_RED, RED_STATE);
        timeElapsed_Red = 0;       // reset the counter to 0 so the counting starts over...
      }
  
    }
    else if(Armed_State == 1)
    {
      digitalWrite(PIN_RED, true);
    }
  }
  
  delay(10);
  
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



