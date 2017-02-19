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
  Serial.print("*OUTGOING 1: "); Serial.print(data.ESC_1); Serial.print("    ");
  Serial.print("*OUTGOING 2: "); Serial.print(data.ESC_2); Serial.print("    ");
  Serial.print("*OUTGOING 3: "); Serial.print(data.ESC_3); Serial.print("    ");
  Serial.print("*OUTGOING 4: "); Serial.print(data.ESC_4); Serial.print("    ");
  Serial.print("*OUTGOING 5: "); Serial.print(data.ESC_5); Serial.print("    ");
  Serial.print("*OUTGOING 6: "); Serial.print(data.ESC_6); Serial.print("    ");
}

void print_STOPmode_andRefreshLCD() {
  Serial.print("      STOP ACTIVE      ");
  lcd.setCursor (3, 0);
  lcd.print(" STOP MODE ");
  Serial.print("count: ");                                                               //somethings the LCD malfunctions and prints random symbols, so i made it so that if we pressed the STOp button 5 times, it will rest the lcd
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
