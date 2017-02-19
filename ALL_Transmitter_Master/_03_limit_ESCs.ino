//FUNC: lets the Speed Potentiometer limits the joystick ranges; redefines lowest position fo ESC (was 0 before)
//(ESC lowest position allowed by SpeedPot)-(ESC middle neutral position)-(ESC highest position allowed by SpeedPot) 
void limitESCs_to_SpeedPot(){                                          
  defaultStickSpeed = motorSpeedCalib(0, defaultStick, speedPot);       //Joystick Calibration#3: Calibrate the joystick valeus to the speed potentiometer, so that we can set how fast a motor can go at any given moment
  ESC_Y1 = motorSpeedCalib(1, ESC_Y1, 16, speedPot);                    //see the parameter description: motorSpeedCalib(index to store the lowest val of 2nd rage, stickESCAxis,lowest value of motor for second neutral range(added this), middle neutral from "calib_neutral(), speedPotentiometer)"
  ESC_Y2 = motorSpeedCalib(2, ESC_Y2, 16, speedPot);
  ESC_Y3 = motorSpeedCalib(3, ESC_Y3, 16, speedPot);
  ESC_Y4 = motorSpeedCalib(4, ESC_Y4, 16, speedPot);
  ESC_Y5 = motorSpeedCalib(5, ESC_Y5, 16, speedPot);
  ESC_Y6 = motorSpeedCalib(6, ESC_Y6, 16, speedPot);
  defaultStickSpeed_x = motorSpeedCalib(0, defaultStick_x, speedPot);   //retrieve the lowest val of the range from the index, and then do the same thing done above
  ESC_X1 = motorSpeedCalib(1, ESC_X1, speedPot);
  ESC_X2 = motorSpeedCalib(2, ESC_X2, speedPot);
  ESC_X3 = motorSpeedCalib(3, ESC_X3, speedPot);
  ESC_X4 = motorSpeedCalib(4, ESC_X4, speedPot);
  ESC_X5 = motorSpeedCalib(5, ESC_X5, speedPot);
  ESC_X6 = motorSpeedCalib(6, ESC_X6, speedPot);
}

void limitESCs_to_Percent(int percent){
  ESC0 = motorSpeedCalib2(0, percent, ESC0);
  ESC_1 = motorSpeedCalib2(1, percent, ESC_1);
  ESC_2 = motorSpeedCalib2(2, percent, ESC_2);
  ESC_3 = motorSpeedCalib2(3, percent, ESC_3);
  ESC_4 = motorSpeedCalib2(4, percent, ESC_4);
  ESC_5 = motorSpeedCalib2(5, percent, ESC_5);
  ESC_6 = motorSpeedCalib2(6, percent, ESC_6);
}


////////////////////////////////////////////////////////////////////////////////////////////(FUNCTIONS USED)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PARAMETER DEFINATION:
/* For the 2 functions below: 
 motorSpeedCalib([index to store the lowest position],[what ESC and axis?],[lowest 2nd neutral position that will be stored in the "lowest[]" array],[the middle neutral position of the ESC that we got from the "calib_neutral()" function],[the speed Pot value that will constrain the motor speed])*/                              
int motorSpeedCalib(int index, int stick, int lowestVal, int speedPot){
    lowest[index] = lowestVal;                                                      //here we will store the lowest positions into the array so we can use this arry to do the X positions (function below) and can also use this array when we need to reverse the ESCs in "reverseESC()" function
    int speedPotForward = map(speedPot, 0, 100, hiN[index], 180);
    int speedPotBack = map(speedPot, 0, 100, lowN[index], lowestVal);
    if (stick > middle[index]){
      stick = map(stick, middle[index],180, hiN[index],speedPotForward); 
    }
    if (stick < middle[index]){
      stick = map(stick, 0, middle[index], speedPotBack, lowN[index]);                         //had to add the "lowestVal paramater in this function because during testing i noticed that in addition to the neutral position near 90, some motors also have a second neutral position near 0 (the 2 motors i tests have the 2nd neutral from 0 to 15)
    } 
    return(stick);
}
int motorSpeedCalib(int index, int stick, int speedPot){
    int lowestVal = lowest[index];
    int speedPotForward = map(speedPot, 0, 100, hiN[index], 180);
    int speedPotBack = map(speedPot, 0, 100, lowN[index], lowestVal);
    if (stick > middle[index]){
      stick = map(stick, middle[index],180, hiN[index],speedPotForward); 
    }
    if (stick < middle[index]){
      stick = map(stick, 0, middle[index], speedPotBack, lowN[index]);                         //had to add the "lowestVal paramater in this function because during testing i noticed that in addition to the neutral position near 90, some motors also have a second neutral position near 0 (the 2 motors i tests have the 2nd neutral from 0 to 15)
    } 
    return(stick);
}

//DESCRIPTION:
/* For the 2nd fucntion
This functions allows the joystick to be able to be constrained by the speed potentiometer. 
Basically, if we move the potentiometer slider to the right, all motors will be able to operate at 100% forward (Servo value 180) and backward (Servo value 0 for the 2nd function and whatever "lowestVal" is set to in the 1st function)
If we slide the potentiometer to the left, it will make the motors operate at 0% speed (basically it wont move). 
90 is usually the neutral position, but since each ESC has their own neutral position, turning the potentiometer to 0% will set each ESC to their specific neutral position that we defined by the "calib_neutral()" functon. 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PARAMETER DEFINATION for 3rd function: 
motorSpeedCalib([index to store the lowest position],[what percent can the motors travelat?] [what ESC to calibrate?])*/
int motorSpeedCalib2(int index, float percentage, int stick){   
    int lowestVal = lowest[index];
    int MAXSpeed_FORWARD = ((180-hiN[index]) * (percentage/100))+ hiN[index];                   //basically tke the percentage value and change up the max and min we can go
    int MAXSpeed_BACK = (lowN[index] - ((lowN[index] - lowestVal)*(percentage/100)));         
    if (stick > middle[index]){
      stick = map(stick, middle[index],180, hiN[index],MAXSpeed_FORWARD); 
    }
    if (stick < middle[index]){
      stick = map(stick, lowestVal,middle[index], MAXSpeed_BACK,lowN[index]);         
    }
    return(stick);
}
/*DESCRIPTION
This one was made for the Climbing Event, it basically takes in the LATEST ESC values and limits the power 
(the latest ESC values were created using the first 2 motorSpeedCalib() above and then stored in the ESC structre thing in the If Statement blocks*/
