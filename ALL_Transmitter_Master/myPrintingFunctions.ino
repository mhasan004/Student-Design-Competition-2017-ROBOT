//////////////// FUNCTION: LCD Printign (not Important)////////////////
void print_RacingOrClimbingModes_onLCD() {
  if (data.climbing_sw == 0) {
    lcd.setCursor (3, 0);
    lcd.print(" Racing MODE ");
  }
  if (data.climbing_sw == 1) {
    lcd.setCursor (3, 0);
    lcd.print("  Climb MODE  ");
  }
}
void print_LiftingMode_onLCD() {
  lcd.setCursor (0, 0);
  lcd.print("    Lifting MODE    ");
  lcd.setCursor (0, 1);                               //Print "Level Buttons Activated"
  lcd.print("Level Buttons ACTIVE");
}
void print_ThrowingMode_onLCD() {
  lcd.setCursor (0, 0);
  lcd.print("   Throwing MODE    ");
}
void print_HittingMode_onLCD() {
  lcd.setCursor (0, 0);
  lcd.print("    Hitting MODE    ");
}

void print_ForwardPercentage_onLCD() {
  lcd.setCursor (16, 3);
  lcd.print("%   ");
  int forwardStick = map(defaultStickSpeed_y, 90, 180, 0, 100);
  lcd.setCursor (4, 3);
  lcd.print("FORWARD: ");
  lcd.setCursor (13, 3);
  lcd.print(forwardStick);
  if (forwardStick <= 9) {
    lcd.setCursor (14, 3);
    lcd.print("  ");
  }
  if (forwardStick >= 100) {
    lcd.setCursor (15, 3);
    lcd.print("0");
  }
  else {
    lcd.setCursor (15, 3);
    lcd.print(" ");
  }
}
void print_BackPercentage_onLCD() {
  lcd.setCursor (14, 3);
  lcd.print("%   ");
  int backwardStick = map(defaultStickSpeed_y, 90, 0, 0, 100);
  lcd.setCursor (2, 3);
  lcd.print("   BACK:  ");
  lcd.setCursor (11, 3);
  lcd.print(backwardStick);
  if (backwardStick <= 9) {
    lcd.setCursor (12, 3);
    lcd.print(" ");
  }
  if (backwardStick >= 100) {
    lcd.setCursor (13, 3);
    lcd.print("0");
  }
  else {
    lcd.setCursor (13, 3);
    lcd.print(" ");
  }
}
void print_LeftPercentage_onLCD() {
  lcd.setCursor (16, 3);
  lcd.print("%   ");
  int backwardStick_x = map(defaultStickSpeed_x, 90, 0, 0, 100);
  lcd.setCursor (4, 3);
  lcd.print("   LEFT:  ");
  lcd.setCursor (13, 3);
  lcd.print(backwardStick_x);
  if (backwardStick_x <= 9) {
    lcd.setCursor (14, 3);
    lcd.print(" ");
  }
  else if (backwardStick_x >= 100) {
    lcd.setCursor (15, 3);
    lcd.print("0");
  }
  else {
    lcd.setCursor (15, 3);
    lcd.print(" ");
  }
}
void print_RightPercentage_onLCD() {
  lcd.setCursor (16, 3);
  lcd.print("%   ");
  int forwardStick_x = map(defaultStickSpeed_x, 90, 180, 0, 100);
  lcd.setCursor (4, 3);
  lcd.print("  RIGHT:  ");
  lcd.setCursor (13, 3);
  lcd.print(forwardStick_x);
  if (forwardStick_x <= 9) {
    lcd.setCursor (14, 3);
    lcd.print(" ");
  }
  else if (forwardStick_x >= 100) {
    lcd.setCursor (15, 3);
    lcd.print("0");
  }
  else {
    lcd.setCursor (15, 3);
    lcd.print(" ");
  }
}

void print_SpeedPot_onLCD(int speedPot) {
  if (data.lifting_sw == 0){
    //If the lifting mode switch isnt pressed, printing the speed potentiometer percentage on the LCD is allowed
 
    lcd.setCursor (3, 1);
    lcd.print(" Speed: ");
    lcd.setCursor (14, 1);
    lcd.print("%  ");
    lcd.setCursor (11, 1);
    lcd.print(speedPot);
    if (speedPot <= 9) {
      lcd.setCursor (12, 1);
      lcd.print(" ");
    }
    if (speedPot >= 100) {
      lcd.setCursor (13, 1);
      lcd.print("0");
    }
    else {
      lcd.setCursor (13, 1);
      lcd.print(" ");
    }
  }
}/*end of printing the Speed Pot percentage*/
void print_defaultStick_y_onLCD()  { 
  //print the default stick values ("defaultStickSpeed_y" and "defaultStickSpeed_x" that is going to the reciever 'data.ESC[0]') 
  //this is just a test to see that the sticks are stable

  lcd.setCursor(0, 3);
  lcd.print(data.ESC[0]);
  lcd.setCursor (3, 3);
  lcd.print(" ");
  if (data.ESC[0] >= 100) {
    lcd.setCursor(2, 3);
    lcd.print("0");
  }
  else if (data.ESC[0] <= 9) {
    lcd.setCursor(1, 3);
    lcd.print("  ");
  }
  else {
    lcd.setCursor(2, 3);
    lcd.print(" ");
  }
}/*end of function*/
void clearMotors_LCD() {                                            
  //this function just cleans the neutral postions if we r not racing
  lcd.setCursor (0, 0);       //left1
  lcd.print("   ");
  lcd.setCursor (17, 0);      //right1
  lcd.print("   ");
  if (data.lifting_sw == 0) {                                       
    //the lifting switch take sup the second line, so the positions are only cleared if the lifting switch isnt pressed
    lcd.setCursor (0, 1);       //left2
    lcd.print("   ");
    lcd.setCursor (17, 1);      //right2
    lcd.print("   ");
  }
  lcd.setCursor (0, 2);       //left3
  lcd.print("   ");
  lcd.setCursor (17, 2);      //right3
  lcd.print("   ");
}/*end of function*/
void outgoing_leftMotors_LCD() {
  /*-----------------------------------------------------------------------left 1*/
  lcd.setCursor(0, 0);
  lcd.print(data.ESC[1]);
  lcd.setCursor (3, 0);
  lcd.print(" ");
  if ((lowN[1] <= data.ESC[1]) && (data.ESC[1] <= hiN[1])) {
    lcd.setCursor(0, 0);
    lcd.print("NEU");
  }
  else if (data.ESC[1] >= 100) {
    lcd.setCursor(2, 0);
    lcd.print("0");
  }
  else if (data.ESC[1] <= 9) {
    lcd.setCursor(1, 0);
    lcd.print("  ");
  }
  else if ((9 < data.ESC[1]) && (data.ESC[1] < 100)) {
    lcd.setCursor(2, 0);
    lcd.print(" ");
  }
  /*-----------------------------------------------------------------------left 2*/
  lcd.setCursor(0, 1);
  lcd.print(data.ESC[2]);
  lcd.setCursor (3, 1);
  lcd.print(" ");
  if ((lowN[2] <= data.ESC[2]) && (data.ESC[2] <= hiN[2])) {
    lcd.setCursor(0, 1);
    lcd.print("NEU");
  }
  else if (data.ESC[2] >= 100) {
    lcd.setCursor(2, 1);
    lcd.print("0");
  }
  else if (data.ESC[2] <= 9) {
    lcd.setCursor(1, 1);
    lcd.print("  ");
  }
  else if (9 < data.ESC[2] < 100) {
    lcd.setCursor(2, 1);
    lcd.print(" ");
  }
  /*-----------------------------------------------------------------------left 3*/
  lcd.setCursor(0, 2);
  lcd.print(data.ESC[3]);
  lcd.setCursor (3, 2);
  lcd.print(" ");
  if ((lowN[3] <= data.ESC[3]) && (data.ESC[3] <= hiN[3])) {
    lcd.setCursor(0, 2);
    lcd.print("NEU");
  }
  else if (data.ESC[3] >= 100) {
    lcd.setCursor(2, 2);
    lcd.print("0");
  }
  else if (data.ESC[3] <= 9) {
    lcd.setCursor(1, 2);
    lcd.print("  ");
  }
  else if (9 < data.ESC[3] < 100) {
    lcd.setCursor(2, 2);
    lcd.print(" ");
  }
}//end of function

void outgoing_rightMotors_LCD() {
  /*-----------------------------------------------------------------------right 1*/
  lcd.setCursor(17, 0);
  lcd.print(data.ESC[4]);
  lcd.setCursor (16, 0);
  lcd.print(" ");
  if ((lowN[4] <= data.ESC[4]) && (data.ESC[4] <= hiN[4])) {
    lcd.setCursor(17, 0);
    lcd.print("NEU");
  }
  else if (data.ESC[4] >= 100) {
    lcd.setCursor(19, 0);
    lcd.print("0");
  }
  else if (data.ESC[4] <= 9) {
    lcd.setCursor(18, 0);
    lcd.print("  ");
  }
  else if ((9 < data.ESC[4]) && (data.ESC[4] < 100)) {
    lcd.setCursor(19, 0);
    lcd.print(" ");
  }
  /*-----------------------------------------------------------------------right 2*/
  lcd.setCursor(17, 1);
  lcd.print(data.ESC[5]);
  lcd.setCursor (16, 1);
  lcd.print(" ");
  if ((lowN[5] <= data.ESC[5]) && (data.ESC[5] <= hiN[5])) {
    lcd.setCursor(17, 1);
    lcd.print("NEU");
  }
  else if (data.ESC[5] >= 100) {
    lcd.setCursor(19, 1);
    lcd.print("0");
  }
  else if (data.ESC[5] <= 9) {
    lcd.setCursor(18, 1);
    lcd.print("  ");
  }
  else if ((9 < data.ESC[5]) && (data.ESC[5] < 100)) {
    lcd.setCursor(19, 1);
    lcd.print(" ");
  }
  /*-----------------------------------------------------------------------right 3*/
  lcd.setCursor(17, 2);
  lcd.print(data.ESC[6]);
  lcd.setCursor (16, 2);
  lcd.print(" ");
  if ((lowN[6] <= data.ESC[6]) && (data.ESC[6] <= hiN[6])) {
    lcd.setCursor(17, 2);
    lcd.print("NEU");
  }
  else if (data.ESC[6] >= 100) {
    lcd.setCursor(19, 2);
    lcd.print("0");
  }
  else if (data.ESC[6] <= 9) {
    lcd.setCursor(18, 2);
    lcd.print("  ");
  }
  else if ((9 < data.ESC[6]) && (data.ESC[6] < 100)) {
    lcd.setCursor(19, 2);
    lcd.print(" ");
  }
}//end of function

//////////////// FUNCTION: More Printing (not Important)////////////////
void print_TestingStuff_onSerialMonitor() {
  Serial.print("           ");
  Serial.print("testLEFTx: ");       Serial.print(testStick_LeftX);
  Serial.print("   testLEFTy: ");     Serial.print(testStick_LeftY);
  Serial.print("      ");
  Serial.print("testRIGHTx: ");        Serial.print(testStick_RightX);
  Serial.print("   testRIGHTy:");     Serial.print(testStick_RightY);
  Serial.print("               ");
  Serial.print("{InitialSpeedPot: ");
  Serial.print(speedPotTest);
  Serial.print("}  {*TEST RUNNING*}");
}
void print_ALL_OUTGOINGS_onSerialMonitor() {
  for (int i=1; i<=6; ++i){
    Serial.print("*OUTGOING "); Serial.print(i); Serial.print(" "); Serial.print(data.ESC[1]); Serial.print("    ");
  }
}
void print_STOPmode_andRefreshLCD() {
  Serial.print("      STOP ACTIVE      ");
  lcd.setCursor (3, 0);
  lcd.print(" STOP MODE ");
  Serial.print("count: ");                                                               
  //somethings the LCD malfunctions and prints random symbols, so i made it so that if we pressed the STOp button 5 times, it will rest the lcd
  Serial.print(counter);
  Serial.print("   ");
  counter++;
  if (counter >= 5) {
    lcd.clear();
    delay(20);
    Serial.print("   LCD CLEARED   ");
    counter = 0;
  }
}
