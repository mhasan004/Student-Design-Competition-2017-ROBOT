void printSpeedPot(int speedPot){
  if (data.lifting_sw == 0)                       //If the lifting mode switch isnt pressed, printing the speed potentiometer percentage on the LCD is allowed
  {  
    lcd.setCursor (3, 1);                               
    lcd.print(" Speed: ");         
    lcd.setCursor (14, 1);                       
    lcd.print("%  ");
    lcd.setCursor (11, 1);   
    lcd.print(speedPot);
    if (speedPot <=9){                 
      lcd.setCursor (12, 1);                       
      lcd.print(" ");     
    }
    if (speedPot >= 100){
      lcd.setCursor (13, 1);                       
      lcd.print("0");     
    }
    else{
      lcd.setCursor (13, 1);                       
      lcd.print(" ");  
    }
  }  
}/*end of printing the Speed Pot percentage
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void defaultStick_LCD()                           //print the default stick values ("defaultStickSpeed" and "defaultStickSpeed_x" that is going to the reciever 'ESC0') this is just a test to see that the sticks are stable
{
  lcd.setCursor(0, 3);
  lcd.print(data.ESC0);  
  lcd.setCursor (3, 3);
  lcd.print(" ");  
  if (data.ESC0 >= 100){
    lcd.setCursor(2, 3);
    lcd.print("0");  
  }
  else if (data.ESC0 <= 9){
    lcd.setCursor(1, 3);
    lcd.print("  ");  
  }
  else{ 
    lcd.setCursor(2, 3);
    lcd.print(" ");  
  }
}/*end of function
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void clearMotors_LCD(){                                             //this function just cleans the neutral postions if we r not racing
  lcd.setCursor (0, 0);       //left1                        
  lcd.print("   ");  
  lcd.setCursor (17, 0);      //right1                      
  lcd.print("   ");  
  if (data.lifting_sw == 0){                                        //the lifting switch take sup the second line, so the positions are only cleared if the lifting switch isnt pressed
  lcd.setCursor (0, 1);       //left2                         
  lcd.print("   ");  
  lcd.setCursor (17, 1);      //right2                      
  lcd.print("   ");  
  }
  lcd.setCursor (0, 2);       //left3                      
  lcd.print("   ");  
  lcd.setCursor (17, 2);      //right3                      
  lcd.print("   ");  
}/*end of function
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void leftMotors_LCD(){              
 /*-----------------------------------------------------------------------left 1*/
  lcd.setCursor(0, 0);              
  lcd.print(data.ESC_1);  
  lcd.setCursor (3, 0);
  lcd.print(" ");
  if ((lowN[1] <= data.ESC_1) && (data.ESC_1 <= hiN[1])){
   lcd.setCursor(0, 0);
   lcd.print("NEU");  
  }
  else if (data.ESC_1 >= 100){
    lcd.setCursor(2, 0);
    lcd.print("0");  
  }
  else if (data.ESC_1 <= 9){
    lcd.setCursor(1, 0);
    lcd.print("  ");  
  } 
  else if ((9 < data.ESC_1) && (data.ESC_1 < 100)){
    lcd.setCursor(2, 0);
    lcd.print(" ");  
  } 
 /*-----------------------------------------------------------------------left 2*/
  lcd.setCursor(0, 1);              
  lcd.print(data.ESC_2);  
  lcd.setCursor (3, 1);
  lcd.print(" ");
  if ((lowN[2] <= data.ESC_2) && (data.ESC_2 <= hiN[2])){
   lcd.setCursor(0, 1);
   lcd.print("NEU");  
  }
  else if (data.ESC_2 >= 100){
    lcd.setCursor(2, 1);
    lcd.print("0");  
  }
  else if (data.ESC_2 <= 9){
    lcd.setCursor(1, 1);
    lcd.print("  ");  
  } 
  else if (9 < data.ESC_2 < 100){
    lcd.setCursor(2, 1);
    lcd.print(" ");  
  } 
 /*-----------------------------------------------------------------------left 3*/
  lcd.setCursor(0, 2);              
  lcd.print(data.ESC_3);  
  lcd.setCursor (3, 2);
  lcd.print(" ");
  if ((lowN[3] <= data.ESC_3) && (data.ESC_3 <= hiN[3])){
   lcd.setCursor(0, 2);
   lcd.print("NEU");  
  }
  else if (data.ESC_3 >= 100){
    lcd.setCursor(2, 2);
    lcd.print("0");  
  }
  else if (data.ESC_3 <= 9){
    lcd.setCursor(1, 2);
    lcd.print("  ");  
  } 
  else if (9 < data.ESC_3 < 100){
    lcd.setCursor(2, 2);
    lcd.print(" ");  
  } 
}//end of function

void rightMotors_LCD(){              
 /*-----------------------------------------------------------------------right 1*/
  lcd.setCursor(17, 0);              
  lcd.print(data.ESC_4);  
  lcd.setCursor (16, 0);
  lcd.print(" ");
  if ((lowN[4] <= data.ESC_4) && (data.ESC_4 <= hiN[4])){
   lcd.setCursor(17, 0);
   lcd.print("NEU");  
  }
  else if (data.ESC_4 >= 100){
    lcd.setCursor(19, 0);
    lcd.print("0");  
  }
  else if (data.ESC_4 <= 9){
    lcd.setCursor(18, 0);
    lcd.print("  ");  
  } 
  else if ((9 < data.ESC_4) && (data.ESC_4 < 100)){
    lcd.setCursor(19, 0);
    lcd.print(" ");  
  } 
 /*-----------------------------------------------------------------------right 2*/
  lcd.setCursor(17, 1);              
  lcd.print(data.ESC_5);  
  lcd.setCursor (16, 1);
  lcd.print(" ");
  if ((lowN[5] <= data.ESC_5) && (data.ESC_5 <= hiN[5])){
   lcd.setCursor(17, 1);
   lcd.print("NEU");  
  }
  else if (data.ESC_5 >= 100){
    lcd.setCursor(19, 1);
    lcd.print("0");  
  }
  else if (data.ESC_5 <= 9){
    lcd.setCursor(18, 1);
    lcd.print("  ");  
  } 
  else if ((9 < data.ESC_5) && (data.ESC_5 < 100)){
    lcd.setCursor(19, 1);
    lcd.print(" ");  
  } 
 /*-----------------------------------------------------------------------right 3*/
  lcd.setCursor(17, 2);              
  lcd.print(data.ESC_6);  
  lcd.setCursor (16, 2);
  lcd.print(" ");
  if ((lowN[6] <= data.ESC_6) && (data.ESC_6 <= hiN[6])){
   lcd.setCursor(17, 2);
   lcd.print("NEU");  
  }
  else if (data.ESC_6 >= 100){
    lcd.setCursor(19, 2);
    lcd.print("0");  
  }
  else if (data.ESC_6 <= 9){
    lcd.setCursor(18, 2);
    lcd.print("  ");  
  } 
  else if ((9 < data.ESC_6) && (data.ESC_6 < 100)){
    lcd.setCursor(19, 2);
    lcd.print(" ");  
  } 
}//end of function






