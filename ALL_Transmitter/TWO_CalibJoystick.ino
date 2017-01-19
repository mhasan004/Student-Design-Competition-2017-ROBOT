//Take the analog values, stabalize the values, unreverse values, and turn into  Servo positions 
int calibrateJoystick(int stick, int low, int middle, int high, bool reverse)
{
  if (reverse == true)
  {
    stick = map(stick, 0,1023, 1023, 0);             //Since my right joystick is reverse, i maped the values the right way
  } 
  stick = stabilizeJoystick(stick, low, middle, high);
  stick = map2Servo(stick);
  return(stick);  
}

/*DESCRIPTION
"calibrateJoystick()" just takes in a stick and remap the highest, lowest, and middle position of a joystick to desirable values
 *  if its reversed, it fixes it
 *  if its still unstable, it stabalizes it by remapping to 512 as middle (1023/2=512)
 *  and finally, it turns the 0-512-1023 value to servo positions (0-90-180) for our ESCs 
    (ESCs are devices that take DC power and converts it into AC current to drive the brushless motors. each of the 3 wires of the ESC gives off pulses of different lengths and intervals to the motor to keep it spinning) 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//Here are the other functions that are included in the "calibrateJoystick()" function:
int stabilizeJoystick( int stick,int lower,int middle,int upper)
{
  stick = constrain(stick, lower, upper);     
  if (stick < middle)       
    stick = map(stick,lower, middle, 0,512);                                                      
  else
    stick = map(stick, middle, upper, 512, 1023);
  return(stick);   
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int map2Servo(int calibratedStick)
{
  if (calibratedStick < 90)       
    calibratedStick = map(calibratedStick,5, 512, 0,90);              //i set it to 5 and not 0 to ensure it will go to 0                                                
  else
    calibratedStick = map(calibratedStick,512, 1020, 90,180);         //i set it to 1020 and not 1023 to ensure it will go to 180     
  return(calibratedStick);
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int isreverse(int stick, bool reverse)
{
  if (reverse == true)
  {
    stick = map(stick, 1023, 0, 0,1023);             //Since my right joystick is reverse, i maped the values the right way
  }  
  return(stick);
}






