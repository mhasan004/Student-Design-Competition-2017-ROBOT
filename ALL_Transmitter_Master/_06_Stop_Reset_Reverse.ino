void resetALLMotors() 
{
  if (defaultStick >= 87 && defaultStick <= 93) {                                       //MIDDLE BOTH: reset data for whichever stick is middle
    reset_y();                                                                          //If RIGHT stick is MIDDLE, reset Y data to neutral
  }
  if (defaultStick_x >= 87 && defaultStick_x <= 93) {                                   //If LEFT stick is MIDDLE, reset X data to neutral
    reset_x();
  }
  if (defaultStick >= 87 && defaultStick <= 93 && defaultStick_x >= 87 && defaultStick_x <= 93) {      //If the LEFT/RIGHT stick is MIDDLE, print that its still
    lcd.setCursor (4, 3);
    lcd.print("    STILL       ");
    stop();
  }
}

void stop()
{                                                //feed the motors with the neutral pulses
  reset_y();
  reset_y();
  data.ESC0 = middle[0];
  data.ESC_1 = middle[1];           
  data.ESC_2 = middle[2];
  data.ESC_3 = middle[3];
  data.ESC_4 = middle[4];
  data.ESC_5 = middle[5];
  data.ESC_6 = middle[6];
  ESC0 = middle[0];
  ESC_1 = middle[1];           
  ESC_2 = middle[2];
  ESC_3 = middle[3];
  ESC_4 = middle[4];
  ESC_5 = middle[5];
  ESC_6 = middle[6];
}
void reset_y(){
  ESC_Y1 = middle[1];           //reset x and y functions are no longer need because of the stop() function
  ESC_Y2 = middle[2];
  ESC_Y3 = middle[3];
  ESC_Y4 = middle[4];
  ESC_Y5 = middle[5];
  ESC_Y6 = middle[6];
}
void reset_x(){    
  ESC_X1 = middle[1];           
  ESC_X2 = middle[2];
  ESC_X3 = middle[3];
  ESC_X4 = middle[4];
  ESC_X5 = middle[5];
  ESC_X6 = middle[6];
}



