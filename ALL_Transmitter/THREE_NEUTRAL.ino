int calib_neutral(int index, int stick, int lowNeutral, int highNeutral)
{ 
  int middleNeutral = ((highNeutral-lowNeutral)/2)+lowNeutral;              //get the low and high neutral position of a specific ESC, and find the middle of the neutral positions
  middle[index] = middleNeutral;                                            //store that middle neutral position to whatever index i choose (this way, all each neutral position of whatever ESC we r currently using will stay in that place we setup using the index#)
  lowN[index] = lowNeutral;                                                 //store the low and high neutral positions, we will reuse these arrays to print the position of all motors on the LCD
  hiN[index] = highNeutral;
  if (stick > middleNeutral){       
    stick = map(stick, 90, 180, middleNeutral, 180 );    
    }                                                   
  if (stick < middleNeutral) 
    stick = map(stick, 0, 90, 0, middleNeutral);
  return(stick);     
}

int calib_neutral(int stick, int middleNeutral)                  //this is just a function i made to do the x axis, since we already found the middle neutral position, it wont make sense to re type the same numbers
{
  if (stick > middleNeutral){       
    stick = map(stick, 90, 180, middleNeutral, 180 );    
    }                                                   
  if (stick < middleNeutral) 
    stick = map(stick, 0, 90, 0, middleNeutral);
  return(stick);     
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






