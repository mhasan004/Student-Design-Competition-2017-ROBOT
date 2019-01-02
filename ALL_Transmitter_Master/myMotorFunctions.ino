
//////////////// FUNCTION: Read all Switches ////////////////
void readALLSwitches() {
  for (int i = 0; i < sizeOfArray; i++) {
    buttonstateArray[i] = digitalRead(switchModeArray[i]);        //read all the switchbuttons
  }
  data.left_sw = buttonstateArray[0];                             //put them in the packet so we can send them out to the reciever
  data.right_sw = buttonstateArray[1];
  data.lifting_sw =  buttonstateArray[2];
  data.throwing_sw = buttonstateArray[3];
  data.climbing_sw = buttonstateArray[4];
  data.hitting_sw =  buttonstateArray[5];
  data.STOP_sw = buttonstateArray[6];
  data.levelUP_sw = buttonstateArray[7];
  data.levelDOWN_sw = buttonstateArray[8];
}
void print_ALLSwitches_onSerialMonitor() {
  Serial.print("Buttons:");
  Serial.print(data.lifting_sw); Serial.print(" ");
  Serial.print(data.throwing_sw); Serial.print(" ");
  Serial.print(data.climbing_sw); Serial.print(" ");
  Serial.print(data.hitting_sw); Serial.print(" ");
  Serial.print(data.STOP_sw); Serial.print("   ");
}

//////////////// FUNCTION: READ The Speed Potentiometer////////////////
void read_and_calibrate_speedPot() {
  speedPot = analogRead(motorSpeed_Pot);
  if (printCalib == 1) {
    Serial.print("InitialPot: ");
    Serial.print(speedPot);
    Serial.print("  ");
  }
  speedPot = map(speedPot, 5, 1020, 0, 100);
  speedPot = constrain(speedPot, 0, 100);
}

//////////////// FUNCTION: Read the Uncalibrated JoyStick Values ////////////////
void readRawJoystickValues() {
  int left_x = analogRead(leftStick_x);   int right_x = analogRead(rightStick_x);         //read the uncalibrated stick
  int left_y = analogRead(leftStick_y);   int right_y = analogRead(rightStick_y);
  int leftStick_sw = digitalRead(leftStick_sw); int rightStick_sw = digitalRead(rightStick_sw);
  if (printCalib == 1) {
   Serial.print("    C1 RY: ");     Serial.print(right_y);
   Serial.print("     ");
  }
}
void store_Yvalues_to_ESC() {
  ESC[0] = defaultStickSpeed_y;
  for (int i=1; i<=6; ++i)
      ESC[i] = ESC_Y[i];
}
void store_XTURNvalues_to_ESC() {
  ESC[0] = defaultStickSpeed_x;
  for (int i=1; i<=3; ++i)
      ESC[i] = ESC_X[i];
  for (int i=4; i<=6; ++i)
      ESC[i] = reverseESC(i, ESC_X[i]);  //"reverseESC()" basically does this: map(ESC_X4, lowest[4],180, 180,lowest[4]); simple
}

//////////////// FUNCTION: Turn JoyStick Values to Servo Values ////////////////
void turn_sticks_to_servo() 
{
  left_x = calibrateJoystick(left_x, 10, 505, 1015, true);      
  left_y = calibrateJoystick(left_y, 10, 504, 1015, false);     
  right_x = calibrateJoystick(right_x, 10, 511, 1015, false);
  right_y = calibrateJoystick(right_y, 10, 532, 1015, true);
  if (printCalib == 1) 
  {
    Serial.print("C2 LX: ");     Serial.print(left_x);
    Serial.print("  ");
    Serial.print("C2 RY: ");     Serial.print(right_y);
    Serial.print("     ");
  }
}
int calibrateJoystick(int stick, int low, int middle, int high, bool reverse)
{
  if (reverse == true)
    stick = map(stick, 0, 1023, 1023, 0);            //Since my right joystick is reverse, i maped the values the right way
  stick = stabilizeJoystick(stick, low, middle, high);
  stick = map2Servo(stick);
  return (stick);
}
int stabilizeJoystick( int stick, int lower, int middle, int upper)
{
  stick = constrain(stick, lower, upper);
  if (stick < middle)
    stick = map(stick, lower, middle, 0, 512);
  else
    stick = map(stick, middle, upper, 512, 1023);
  return (stick);
}
int map2Servo(int calibratedStick)
{
  if (calibratedStick < 90)
    calibratedStick = map(calibratedStick, 5, 512, 0, 90);            //i set it to 5 and not 0 to ensure it will go to 0
  else
    calibratedStick = map(calibratedStick, 512, 1020, 90, 180);       //i set it to 1020 and not 1023 to ensure it will go to 180
  return (calibratedStick);
}
int isreverse(int stick, bool reverse)
{
  if (reverse == true)
    stick = map(stick, 1023, 0, 0, 1023);            //Since my right joystick is reverse, i maped the values the right way
  return (stick);
}

//////////////// FUNCTION: ESC to Neutral Positions////////////////
void calibrate_sticks_to_ESCs() 
{
  defaultStick_y = calib_neutral(0, right_y, 90, 90);            
  ESC_Y[1] = calib_neutral(1, right_y, 90, 90);                 
  ESC_Y[2] = calib_neutral(2, right_y, 92, 98);
  ESC_Y[3] = calib_neutral(3, right_y, 90, 90);
  ESC_Y[4] = calib_neutral(4, right_y, 90, 90);
  ESC_Y[5] = calib_neutral(5, right_y, 93, 101);
  ESC_Y[6] = calib_neutral(6, right_y, 90, 90);
  defaultStick_x = calib_neutral(0, left_x);
  for (int i=1; i<=6; ++i)
    ESC_X[i] = calib_neutral(i, left_x);    
  if (printCalib == 1)
  {
    Serial.print("C3 LX1: ");  Serial.print(ESC_X[1]);
    Serial.print("  ");
    Serial.print("C3 RY1: "); Serial.print(ESC_Y[1]);
    Serial.print("     ");
  }
}
int calib_neutral(int index, int stick, int lowNeutral, int highNeutral)
{
  middle[index] = ((highNeutral - lowNeutral) / 2) + lowNeutral;        
  //Get the low and high neutral position of a specific ESC, and find the middle of the neutral positions
  //Store that middle neutral position to whatever index i choose (this way, all each neutral position of whatever ESC we r currently using will stay in that place we setup using the index#)
  //Store the low and high neutral positions, we will reuse these arrays to print the position of all motors on the LCD:
  lowN[index] = lowNeutral;                                             
  hiN[index] = highNeutral;
  if (stick > middle[index]) 
    stick = map(stick, 90, 180, middle[index], 180);
  if (stick < middle[index])
    stick = map(stick, 0, 90, 0, middle[index]);
  return (stick);
}
int calib_neutral(int index, int stick)                  //this is just a function i made to do the x axis, since we already found the middle neutral position, it wont make sense to re type the same numbers
{
  if (stick > middle[index]) 
    stick = map(stick, 90, 180, middle[index], 180 );
  if (stick < middle[index])
    stick = map(stick, 0, 90, 0, middle[index]);
  return (stick);
}

//////////////// FUNCTION: Limit the ESC Values////////////////
void limitESCs_to_SpeedPot()
{                                          
  defaultStickSpeed_y = motorSpeedCalib(0, defaultStick_y, speedPot);       //Joystick Calibration#3: Calibrate the joystick valeus to the speed potentiometer, so that we can set how fast a motor can go at any given moment
  for (int i = 1; i<=6; ++i)
    ESC_Y[i] = motorSpeedCalib(i, ESC_Y[i], 16, speedPot);            
  //All motors seem to have 16 as lowest position. 
  //See the parameter description: motorSpeedCalib(index to store the lowest val of 2nd rage, stickESCAxis,lowest value of motor for second neutral range(added this), middle neutral from "calib_neutral(), speedPotentiometer)"
  defaultStickSpeed_x = motorSpeedCalib(0, defaultStick_x, speedPot);   //retrieve the lowest val of the range from the index, and then do the same thing done above
  for (int i = 1; i<=6; ++i)
    ESC_X[i] = motorSpeedCalib(i, ESC_X[i], speedPot);   
}

void limitESCs_to_Percent(int percent){
  for (int i = 0; i<=6; ++i)
    ESC[i] = motorSpeedCalib2(i, percent, ESC[i]);  
}
int motorSpeedCalib(int index, int stick, int lowestVal, int speedPot){
    lowest[index] = lowestVal;                                                      //here we will store the lowest positions into the array so we can use this arry to do the X positions (function below) and can also use this array when we need to reverse the ESCs in "reverseESC()" function
    int speedPotForward = map(speedPot, 0, 100, hiN[index], 180);
    int speedPotBack = map(speedPot, 0, 100, lowN[index], lowestVal);
    if (stick > middle[index])
      stick = map(stick, middle[index],180, hiN[index],speedPotForward); 
    if (stick < middle[index])
      stick = map(stick, 0, middle[index], speedPotBack, lowN[index]);                         //had to add the "lowestVal paramater in this function because during testing i noticed that in addition to the neutral position near 90, some motors also have a second neutral position near 0 (the 2 motors i tests have the 2nd neutral from 0 to 15)
    return(stick);
}
int motorSpeedCalib(int index, int stick, int speedPot){
    int lowestVal = lowest[index];
    int speedPotForward = map(speedPot, 0, 100, hiN[index], 180);
    int speedPotBack = map(speedPot, 0, 100, lowN[index], lowestVal);
    if (stick > middle[index])
      stick = map(stick, middle[index],180, hiN[index],speedPotForward); 
    if (stick < middle[index])
      stick = map(stick, 0, middle[index], speedPotBack, lowN[index]);                         //had to add the "lowestVal paramater in this function because during testing i noticed that in addition to the neutral position near 90, some motors also have a second neutral position near 0 (the 2 motors i tests have the 2nd neutral from 0 to 15)
    return(stick);
}
int motorSpeedCalib2(int index, float percentage, int stick){   
    int lowestVal = lowest[index];
    int MAXSpeed_FORWARD = ((180-hiN[index]) * (percentage/100))+ hiN[index];                   //basically tke the percentage value and change up the max and min we can go
    int MAXSpeed_BACK = (lowN[index] - ((lowN[index] - lowestVal)*(percentage/100)));         
    if (stick > middle[index])
      stick = map(stick, middle[index],180, hiN[index],MAXSpeed_FORWARD); 
    if (stick < middle[index])
      stick = map(stick, lowestVal,middle[index], MAXSpeed_BACK,lowN[index]);         
    return(stick);
}

//////////////// FUNCTION: Reverse the ESCs////////////////
int reverseESC(int index, int stick, bool reverse){                        //just a quick and easy function to reverse the ESC positions. 
  if (reverse == true){
    if (stick > middle[index])
      stick = map(stick, middle[index],180, middle[index], lowest[index]);
    else
      stick = map(stick, lowest[index], middle[index], 180, middle[index]);  
  }
  return(stick); 
}
int reverseESC(int index, int stick){                        //just a quick and easy function to reverse the ESC positions. 
  if (stick > middle[index])
    stick = map(stick, middle[index],180, middle[index], lowest[index]);
  else
    stick = map(stick, lowest[index], middle[index], 180, middle[index]);
  return(stick); 
}

//////////////// FUNCTION: Resetting & Stoping Motors////////////////
void resetALLMotors() 
{
  if (defaultStick_y >= 87 && defaultStick_y <= 93)                                         //MIDDLE BOTH: reset data for whichever stick is middle
    reset_y();                                                                          //If RIGHT stick is MIDDLE, reset Y data to neutral
  if (defaultStick_x >= 87 && defaultStick_x <= 93)                                     //If LEFT stick is MIDDLE, reset X data to neutral
    reset_x();
  if (defaultStick_y >= 87 && defaultStick_y <= 93 && defaultStick_x >= 87 && defaultStick_x <= 93) {      //If the LEFT/RIGHT stick is MIDDLE, print that its still
    lcd.setCursor (4, 3);
    lcd.print("    STILL       ");
    stop();
  }
}
void stop()
{                                                //feed the motors with the neutral pulses
  for (int i=0; i<=6; ++i){
    data.ESC[i] = middle[i];
    ESC[i] = middle[i];
    ESC_Y[i] = middle[i];  
    ESC_X[i] = middle[i]; 
  }
}
void reset_y(){
   for (int i=1; i<=6; ++i)
     ESC_Y[i] = middle[i];     
}
void reset_x(){   
  for (int i=1; i<=6; ++i)
    ESC_X[i] = middle[i];       //reset x and y functions are no longer need because of the stop() function   
}
