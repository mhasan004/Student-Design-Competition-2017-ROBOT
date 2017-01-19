//WE DONT NEED THIS FUNCTION AS MUCH NOW!!!
//I based this function from this page: https://www.arduino.cc/en/tutorial/smoothing 
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




/*DESCRIPTION
Basically this function will take the first...say 20 numbers (or whatever number we defined) and average them out

I had to add an index to the 2 parameters so that each joystick can have their own "file" or something.
left joystick and its x axis will be 0, left joystick and its x axis will be 1, etc. 
x axis of the left joystick will only go to the 0 "folder" and the y axis of the left joystick will of go to the 1 "folder" etc.

replace "stick" with whatever joystick we are using. example "right joystick up/down" is how we r gana go forward/back, so
                                                              "smoothing(right_y, 3)"
                                                              
the index can be anything, we just need all the index #s to be different so readings for different sticks will be in different locations 
*/                                                            
                                                              
                                                              

