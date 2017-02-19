int reverseESC(int index, int stick, bool reverse){                        //just a quick and easy function to reverse the ESC positions. 
  if (reverse == true){
    if (stick > middle[index]){
      stick = map(stick, middle[index],180, middle[index], lowest[index]);
    }
    else{
      stick = map(stick, lowest[index], middle[index], 180, middle[index]);
    }  
  }
  return(stick); 
}
int reverseESC(int index, int stick){                        //just a quick and easy function to reverse the ESC positions. 
  if (stick > middle[index]){
    stick = map(stick, middle[index],180, middle[index], lowest[index]);
  }
  else{
    stick = map(stick, lowest[index], middle[index], 180, middle[index]);
  }  
  return(stick); 
}
