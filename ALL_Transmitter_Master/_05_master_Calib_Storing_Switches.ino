///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SPEEDPOT
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////JOYSTICKS
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
  ESC0 = defaultStickSpeed;
  ESC_1 = ESC_Y1;
  ESC_2 = ESC_Y2;
  ESC_3 = ESC_Y3;
  ESC_4 = ESC_Y4;
  ESC_5 = ESC_Y5;
  ESC_6 = ESC_Y6;
}
void store_XTURNvalues_to_ESC() {
  ESC0 = defaultStickSpeed_x;
  ESC_1 = ESC_X1;
  ESC_2 = ESC_X2;
  ESC_3 = ESC_X3;
  ESC_4 = reverseESC(4, ESC_X4);             //"reverseESC()" basically does this: map(ESC_X4, lowest[4],180, 180,lowest[4]); simple
  ESC_5 = reverseESC(5, ESC_X5);
  ESC_6 = reverseESC(6, ESC_X6);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SWITCHES
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
  //data.STOP_sw = !digitalRead(STOP_sw);
}
void print_ALLSwitches_onSerialMonitor() {
  Serial.print("Buttons:");
  Serial.print(data.lifting_sw); Serial.print(" ");
  Serial.print(data.throwing_sw); Serial.print(" ");
  Serial.print(data.climbing_sw); Serial.print(" ");
  Serial.print(data.hitting_sw); Serial.print(" ");
  Serial.print(data.STOP_sw); Serial.print("   ");
  //Serial.print(data.levelUP_sw);Serial.print(" ");
  //Serial.print(data.levelDOWN_sw);Serial.print("       ");
}


