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

Servo LeftMotor[4];//motors 1 to 3, 0 index not included        
Servo RightMotor[4];//motors 1 to 3, 0 index not included        
int *LeftMotorVal = new int[4]; //declaring the data.ESC->Motor values  
int *RightMotorVal = new int[4];
int Motor_pin[7] = {11,9,10,5,6,7};
  //Motor_pin[1] = 11;   //Left Side Front robot Motor 
  //Motor_pin[2] = 9;    //Left Side Middle robot Motor 
  //Motor_pin[3] = 10;   //Left Side Back robot Motor  
  //Motor_pin[4]= 5;     //Right Side Front robot Motor 
  //Motor_pin[5] = 6;    //Right Side Middle robot Motor 
  //Motor_pin[6] = 7;    //Right Side Back robot Motor 
int micro_sw1 = 40;                           //(1&2)LIMIT Switches used for Lifting Mode to know if the max/min height is reached. 
int micro_sw2 = 41; 
int micro_sw3 = 42;                           //(3&4) LIMIT Switches used for BALL HITTING Mode, need more info
int micro_sw4 = 43;               
int led = 13;                                 //this is an LED that will be connected to pin 13 and ground of the arduino, it will lightup if the arduino is in ARMING mode in the SETUP

struct controllerData {    
  int *ESC = new int[7];                                               
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
}; 
controllerData data;   //making the object    

void setup(){                  
  Serial.begin(250000);
  Serial.println("Starting");
  pinMode(led, OUTPUT);
  motors.init();     //Initiate the DC motor shield
  radio.begin();     //Link The Radio
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15, 15);
  radio.openReadingPipe(1,pipe); 
  for (int i=1; i<=3; ++i){
    LeftMotor[i].attach(Motor_pin[i]); 
    RightMotor[i].attach(Motor_pin[3+i]);
  }                              
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
  for (int i=1; i<=3; ++i)
    LeftMotorVal[i] = data.ESC[i];  //(Left Motors:1-3)
  for (int i=4; i<=6; ++i)
    RightMotorVal[i] = data.ESC[3+i]; //(Right Motors: 4-6) 
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
  for (int i=1; i<=3; ++i)
    Serial.print(LeftMotorVal[i]);
  Serial.print("    RIGHT AXIS: ");  
  for (int i=1; i<=3; ++i)
    Serial.print(RightMotorVal[i]);
  if(now-lastRecvTime > 4000) 
    Serial.print("                 lost");
  Serial.println();      
  radio.startListening(); 
}


void ALL_MOTORS(){
  for (int i=1; i<=3; ++i){
    LeftMotor[i].write(LeftMotorVal[i]);
    RightMotor[i].write(RightMotorVal[i]);  
  }
}
