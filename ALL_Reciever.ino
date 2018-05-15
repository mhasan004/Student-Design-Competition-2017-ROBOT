//Reciever will have the motors
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24_config.h>
#define CE_PIN   8
#define CSN_PIN  53
RF24 radio(CE_PIN, CSN_PIN);  
const uint64_t pipe = 0xE8E8F0F0E1LL;   
 
#include "DualVNH5019MotorShield.h"                     //This is the Pololu DC Motor driver library
DualVNH5019MotorShield motors;                          //Motor1 will be the lifting motor. Motor2 i dont kow yet, will be the ball hitting motor i think
#include <Servo.h>  
Servo LeftMotor1;        
Servo LeftMotor2;
Servo LeftMotor3;
Servo RightMotor4;
Servo RightMotor5;
Servo RightMotor6;
int LeftMotor_pin1 = 11;
int LeftMotor_pin2 = 9;
int LeftMotor_pin3 = 10;  
int RightMotor_pin4 = 5;
int RightMotor_pin5 = 6;
int RightMotor_pin6 = 7;
int Motor1; int Motor2; int Motor3; int Motor4; int Motor5; int Motor6;   //declaring the data.ESC->Motor values  
int micro_sw1 = 40;                           //(1&2)LIMIT Switches used for Lifting Mode to know if the max/min height is reached. 
int micro_sw2 = 41; 
int micro_sw3 = 42;                           //(3&4) LIMIT Switches used for BALL HITTING Mode, need more info
int micro_sw4 = 43;               
int led = 13;                                 //this is an LED that will be connected to pin 13 and ground of the arduino, it will lightup if the arduino is in ARMING mode in the SETUP

struct controllerData{                        
  int ESC0; int ESC_1;int ESC_2;int ESC_3;int ESC_4;int ESC_5;int ESC_6;     
  int motorSpeed_Pot;
  bool levelUP_sw;
  bool levelDOWN_sw;
  bool left_sw;    
  bool right_sw;
  bool lifting_sw;
  bool throwing_sw;
  bool climbing_sw;
  bool hitting_sw;   
  bool STOP_sw;
};controllerData data;

void setup(){                  
  Serial.begin(250000);
  Serial.println("Starting");
  pinMode(led, OUTPUT);
  motors.init();                                    //Initiate the DC motor shield
  radio.begin();                                      //Link The Radio
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15, 15);
  radio.openReadingPipe(1,pipe); 
  LeftMotor1.attach(LeftMotor_pin1);  
  LeftMotor2.attach(LeftMotor_pin2);  
  LeftMotor3.attach(LeftMotor_pin3);   
  RightMotor4.attach(RightMotor_pin4); 
  RightMotor5.attach(RightMotor_pin5);  
  RightMotor6.attach(RightMotor_pin6);                                
  radio.startListening(); 
}//End of Setup

unsigned long lastRecvTime = 0;
void loop() 
{
  while (radio.available()) 
  {
    radio.read(&data, sizeof(controllerData));
    lastRecvTime = millis(); //here we receive the data 
  }  
  unsigned long now = millis();                              
  Motor1 = data.ESC_1;     //(Left Motors:1-3)(Right Motors: 4-6)
  Motor2 = data.ESC_2;
  Motor3 = data.ESC_3;
  Motor4 = data.ESC_4;
  Motor5 = data.ESC_5;
  Motor6 = data.ESC_6;
  int levelUP_sw = data.levelUP_sw;
  int levelDOWN_sw = data.levelDOWN_sw;
  int left_sw = data.left_sw;  
  int right_sw = data.right_sw;
  int lifting_sw = data.lifting_sw;
  int throwing_sw = data.throwing_sw;
  int climbing_sw = data.climbing_sw;
  int hitting_sw = data.hitting_sw;
  int STOP_sw = data.STOP_sw;
  Serial.print("Buttons:");
  Serial.print(lifting_sw);Serial.print(" ");
  Serial.print(throwing_sw);Serial.print(" ");
  Serial.print(climbing_sw);Serial.print(" ");
  Serial.print(hitting_sw);Serial.print(" ");
  Serial.print(data.STOP_sw);Serial.print(" ");
  ALL_MOTORS();                                   
 
  Serial.print("    LEFT AXIS: ");  
  Serial.print(Motor1);
  Serial.print(" "); 
  Serial.print(Motor2);
  Serial.print(" "); 
  Serial.print(Motor3);
  Serial.print(" "); 
  
  Serial.print("    RIGHT AXIS: ");  
  Serial.print(Motor4);
  Serial.print(" "); 
  Serial.print(Motor5);
  Serial.print(" "); 
  Serial.print(Motor6);
  Serial.print(" ");

  if(now-lastRecvTime > 4000) {
    Serial.print("                 lost");
  }
  Serial.println();      
  radio.startListening(); 
}

////////////////:FUNCTIONS://///////////////
void ALL_MOTORS(){
  LeftMotor1.write(Motor1);
  LeftMotor2.write(Motor2);
  LeftMotor3.write(Motor3);  
  RightMotor4.write(Motor4);                
  RightMotor5.write(Motor5);
  RightMotor6.write(Motor6);
}
/*void ALL_MOTORS_Y(){
  LeftMotor1.write(Motor3_y);
  LeftMotor2.write(Motor2_y);
  LeftMotor3.write(Motor1_y);
  RightMotor1.write(Motor6_y);                
  RightMotor5.write(Motor5_y);
  RightMotor6.write(Motor4_y);
}
void ALL_MOTORS_X(){
  LeftMotor1.write(Motor3_x);
  LeftMotor2.write(Motor2_x);
  LeftMotor3.write(Motor1_x);
  RightMotor1.write(Motor6_x);                
  RightMotor5.write(Motor5_x);
  RightMotor6.write(Motor4_x);
}
void LEFT_MOTORS_X(){
  LeftMotor1.write(Motor3_x);
  LeftMotor2.write(Motor2_x);
  LeftMotor3.write(Motor1_x);
}
void RIGHT_MOTORS_X(){
  RightMotor1.write(Motor6_x);                
  RightMotor5.write(Motor5_x);
  RightMotor6.write(Motor4_x);  
}
*/















