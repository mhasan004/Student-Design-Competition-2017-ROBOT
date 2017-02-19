//Paramaters: calib_neutral(index#to store neutral position of motor, stickAxis, low neutral of motor, high neutral of motor)
//FUNC: Turn the 0-90-180 to 0-(ESC middle neutral position)-180
void calibrate_sticks_to_ESCs() {
  defaultStick = calib_neutral(0, right_y, 90, 90);            
  ESC_Y1 = calib_neutral(1, right_y, 90, 90);                 
  ESC_Y2 = calib_neutral(2, right_y, 92, 98);
  ESC_Y3 = calib_neutral(3, right_y, 90, 90);
  ESC_Y4 = calib_neutral(4, right_y, 90, 90);
  ESC_Y5 = calib_neutral(5, right_y, 93, 101);
  ESC_Y6 = calib_neutral(6, right_y, 90, 90);
  defaultStick_x = calib_neutral(0, left_x);
  ESC_X1 = calib_neutral(1, left_x);
  ESC_X2 = calib_neutral(2, left_x);
  ESC_X3 = calib_neutral(3, left_x);
  ESC_X4 = calib_neutral(4, left_x);
  ESC_X5 = calib_neutral(5, left_x);
  ESC_X6 = calib_neutral(6, left_x);
  if (printCalib == 1){
    Serial.print("C3 LX1: ");  Serial.print(ESC_X1);
    Serial.print("  ");
    Serial.print("C3 RY1: "); Serial.print(ESC_Y1);
    Serial.print("     ");
  }
}


////////////////////////////////////////////////////////////////////////////(FUNCTIONS USED)////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int calib_neutral(int index, int stick, int lowNeutral, int highNeutral)
{
  middle[index] = ((highNeutral - lowNeutral) / 2) + lowNeutral;        //get the low and high neutral position of a specific ESC, and find the middle of the neutral positions
  //store that middle neutral position to whatever index i choose (this way, all each neutral position of whatever ESC we r currently using will stay in that place we setup using the index#)
  lowN[index] = lowNeutral;                                             //store the low and high neutral positions, we will reuse these arrays to print the position of all motors on the LCD
  hiN[index] = highNeutral;
  if (stick > middle[index]) {
    stick = map(stick, 90, 180, middle[index], 180);
  }
  if (stick < middle[index])
    stick = map(stick, 0, 90, 0, middle[index]);
  return (stick);
}


int calib_neutral(int index, int stick)                  //this is just a function i made to do the x axis, since we already found the middle neutral position, it wont make sense to re type the same numbers
{
  if (stick > middle[index]) {
    stick = map(stick, 90, 180, middle[index], 180 );
  }
  if (stick < middle[index])
    stick = map(stick, 0, 90, 0, middle[index]);
  return (stick);
}



/*DESCRIPTION
  "calibNeutral()" takes it 3 things:
  1.) It takes a stick variable (lets say the y axis (up/down) of the right joystick)
  2.) The range of the neutral position of a specific ESC (the values where the motor is in between forward and reverse and doesnt turn)
  3.) the  index number, basically the position where the MIDDLE neutral position will be stored (in the "middle[]" array)

  and does 2 things:
  1.) it takes the middle position of the neutral range and stores that middle neutral position to the array "middle" that we defined before the "void loop()" function
  2.) It then maps the joystick so that the middle neutral position becomes the new middle value and then returns it so that we can equal it to the stick of our choosing
*/






