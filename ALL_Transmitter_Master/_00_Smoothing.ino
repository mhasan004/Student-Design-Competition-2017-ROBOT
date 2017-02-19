//WE DONT NEED THIS FUNCTION AS MUCH NOW!!!
//I based this function from this page: https://www.arduino.cc/en/tutorial/smoothing 

//Global variables for this function if we were to ever use it again: 
/*
#define amountToAverage 1                                     //this is the amount we will read and keep averaging.
#define x amountToAverage
#define numOfSticks 10                                        //(leftx,lefty,rightx,righy) so 4 axises we need to measure, 1 motor speed potentiometer and got room to add 5 more pot if we needed more, obviously we can add much as we want tho, but though that 10 would be a safe #
const int smoothingValue[numOfSticks] = {x, x, x, x, x, x};   //this was we can use one function to average all axis.
int readings[numOfSticks][x] = {};                            //2 dimentional array:1st index is the axis#(leftx,lefty,righx,righy); 2nd index says that we want the readings to be as big as the #s we want to average
int readIndex[numOfSticks] = {0};                             //(leftx,lefty,rightx,right) will all be 0 (had to put 4 0s for 4 axis)
int total[numOfSticks] = {0};                                 //I didnt know how to set all the elements in an array to one value :/ is this how to do it?
int average[numOfSticks] = {0};
*/

//Te Function:
/*
int smoothing(int stick, int index){                                       
  total[index] = total[index] - readings[index][readIndex[index]];        //Subtract the last reading
  readings[index][readIndex[index]] = stick;                              //read from the sensor, 
  total[index] = total[index] + readings[index][readIndex[index]];        //add the reading to the total:
  readIndex[index] = readIndex[index] + 1;                  // go to the next position in the array:
  if (readIndex[index] >= smoothingValue[index]) {          // if we are reaching the end of the array...
    readIndex[index] = 0;                            // ...go to the the beginning:
  }
  average[index]= total[index] / smoothingValue[index];           // calculate the average:
  return(average[index]);
}
*/




//DESCRIPTION:
/*Basically this function will take the first...say 20 numbers (or whatever number we defined) and average them out

I had to add an index to the 2 parameters so that each joystick can have their own "file" or something.
left joystick and its x axis will be 0, left joystick and its x axis will be 1, etc. 
x axis of the left joystick will only go to the 0 "folder" and the y axis of the left joystick will of go to the 1 "folder" etc.

replace "stick" with whatever joystick we are using. example "right joystick up/down" is how we r gana go forward/back, so
                                                              "smoothing(right_y, 3)"
                                                              
the index can be anything, we just need all the index #s to be different so readings for different sticks will be in different locations 
*/                                                            
                                                              
                                                              

