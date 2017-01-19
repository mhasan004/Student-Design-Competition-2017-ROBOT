void stop(){                                                //feed the motors with the neutral pulses
    data.ESC0 = neutral0;
    data.ESC_1 = neutral1;           
    data.ESC_2 = neutral2;
    data.ESC_3 = neutral3;
    data.ESC_4 = neutral4;
    data.ESC_5 = neutral5;
    data.ESC_6 = neutral6;
}

int reverseESC(int stick, int index ){                        //just a quick and easy function to reverse the ESC positions. 
  stick = map(stick, lowest[index], 180,180,lowest[index]);
  return(stick); 
}
  

void reset_y(){
    ESC_Y1 = neutral1;           //reset x and y functions are no longer need because of the stop() function
    ESC_Y2 = neutral2;
    ESC_Y3 = neutral3;
    ESC_Y4 = neutral4;
    ESC_Y5 = neutral5;
    ESC_Y6 = neutral6;
}

void reset_x(){    
    ESC_X1 = neutral1;           
    ESC_X2 = neutral2;
    ESC_X3 = neutral3;
    ESC_X4 = neutral4;
    ESC_X5 = neutral5;
    ESC_X6 = neutral6;
}


