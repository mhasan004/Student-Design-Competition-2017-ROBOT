/*PARAMETER DEFINATION for the 2 functions below: 
 motorSpeedCalib([index to store the lowest position],[what ESC and axis?],[lowest 2nd neutral position that will be stored in the "lowest[]" array],[the middle neutral position of the ESC that we got from the "calib_neutral()" function],[the speed Pot value that will constrain the motor speed])*/                              
int motorSpeedCalib(int index, int stick, int lowestVal, int middle, int speedPot){
    lowest[index] = lowestVal;                                                      //here we will store the lowest positions into the array so we can use this arry to do the X positions (function below) and can also use this array when we need to reverse the ESCs in "reverseESC()" function
    int speedPotForward = map(speedPot, 0, 100, middle, 180);
    int speedPotBack = map(speedPot, 0, 100, middle, lowestVal);
    if (stick > middle){
      stick = map(stick, middle,180, middle,speedPotForward); 
    }
    if (stick < middle){
      stick = map(stick, 0, middle, speedPotBack, middle);                         //had to add the "lowestVal paramater in this function because during testing i noticed that in addition to the neutral position near 90, some motors also have a second neutral position near 0 (the 2 motors i tests have the 2nd neutral from 0 to 15)
    } 
    return(stick);
}

int motorSpeedCalib(int index, int stick, int middle, int speedPot){
    int lowestVal = lowest[index];
    int speedPotForward = map(speedPot, 0, 100, middle, 180);
    int speedPotBack = map(speedPot, 0, 100, middle, lowestVal);
    lowest[index] = lowestVal;
    if (stick > middle){
      stick = map(stick, middle,180, middle,speedPotForward); 
    }
    if (stick < middle){
      stick = map(stick, 0, middle, speedPotBack, middle);                        //had to add the "lowestVal paramater in this function because during testing i noticed that in addition to the neutral position near 90, some motors also have a second neutral position near 0 (the 2 motors i tests have the 2nd neutral from 0 to 15)
    } 
    return(stick);
}
/*DESCRIPTION for the 1stfucntion
This functions allows the joystick to be able to be constrained by the speed potentiometer. 
Basically, if we move the potentiometer slider to the right, all motors will be able to operate at 100% forward (Servo value 180) and backward (Servo value 0 for the 2nd function and whatever "lowestVal" is set to in the 1st function)
If we slide the potentiometer to the left, it will make the motors operate at 0% speed (basically it wont move). 
90 is usually the neutral position, but since each ESC has their own neutral position, turning the potentiometer to 0% will set each ESC to their specific neutral position that we defined by the "calib_neutral()" functon. 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PARAMETER DEFINATION for 3rd function: 
motorSpeedCalib([index to store the lowest position],[what percent can the motors travelat?] [what data.ESC to calibrate?])*/
int motorSpeedCalib(int index, float percentage, int stick){   
    int lowestVal = lowest[index];
    int MAXSpeed_FORWARD = ((180-middle[index]) * (percentage/100))+ middle[index];                   //basically tke the percentage value and change up the max and min we can go
    MAXSpeed_FORWARD = MAXSpeed_FORWARD ;
    int MAXSpeed_BACK = (middle[index] - ((middle[index] - lowestVal)*(percentage/100)));         
    if (stick > middle[index]){
      stick = map(stick, middle[index],180, middle[index],MAXSpeed_FORWARD); 
    }
    if (stick < middle[index]){
      stick = map(stick, lowestVal,middle[index], MAXSpeed_BACK,middle[index]);         
    }
    return(stick);
}

/*DESCRIPTION
This one was made for the Climbing Event, it basically takes in the LATEST data.ESC values and limits the power 
(the latest data.ESC values were created using the first 2 motorSpeedCalib() above and then stored in the data.ESC structre thing in the If Statement blocks*/
