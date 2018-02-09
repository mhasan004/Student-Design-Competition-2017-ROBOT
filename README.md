# SDCProgramming
Robot for the ASME SDC 2016-2017 robotic competition

This is the robot I have programmed for the SDC 2016-2017 robotic competition. It can climb 3 sets of stairs, sprint forward and back using six brushless motors, lift an object up to 15ft, throw a golf ball, and hit a golf ball placed on the floor. 
The cotroller has four swiches that controls each of the five modes. The right joystick (y axis) lets the robot to move forwards and backwards. The left joystick (x axis) lets the robot to turn left and right.
The controler and the robot is explained here: https://mahmudul-hasan.wixsite.com/home/sdc-2017

The Transmitter file contains the arduino codes for the controller that I have built. This portion of the code computes all of the data need to operate the robot. The reciever file contrins the arduino code for the robot.

#Calibrating the Brushless Motors
One of the most complicated parts was the robot was to accurate control each of the six burshless motors. 
To control the motors, the program had to reading the x and y component positions of the left and right analog joysticks and then compute a range of servo angle values to control individual brushless motors. Each motor has a maximum and a minimum value. The maximum value represented 100% speed forwards and the minimum value represented 100% speed backward.  

**1) Finding the Neutral Pulse Range**
Each motor had its own netural range. The neutral range is a range of the servo angle values (0 to 180) where the motor does not spin. The maximum and minimum ranges were obtained by manually testing each motor. I made a test code that slowly feeds a pulse to the motor. the testing program slowly feed a pulse of 0 to a pulse of 180 to the motor. For most of the motors, from 0-15, the motors didnt run. At 16 most of the motors ran at 100% backwards. As the pulse got near 90, each motor stopped in the 80 to 100 mark. In this range, we recorded the range of pulses that the motor remained idle. This was the neutral positon for each motors. A midpoint value was then calculated. This midpoint value was then maped to the resting joystick analog value. This way, if the joystick is in rest position, all motors will recieve their own neutral pulse and will not move.

**2) Finding 100% Forward Speed of Each Motor
The next difficult step was to figure out what the 100% forward value for each motor was. A problem we noticed was that each motor's 100% speed was either slower or faster than other motors. In other words, the motors did not run in the same speed. This is an issue because if all the motors dont run at the same speed, there will be overheating and control issues. To combat this issue, we have used a speed tacheometer to record the speed of each motor. We have tested each motor with a fully changed LiPo battery. After getting an average max  forward speed of each motor, we set the max forward speed of all motor the the lowest average max forward speed we have obtained for the six motors. This way, all motors will run at near the same max forward and backward speed. 
Once again, we have mapped this to the joystick. 

I made a speed controller using a sliding potentiommeter. the potentiometer controlls how much i can go forward and backward. For example, if the slider is all the way to the down, all motors will run in 0% forwards and backwards (this is the midpoint neutral position for each motor). If the slider is at the top, each motor can will 100% forwardsa nd backwards. 

**3)
There was also a broken brshless motor that constantly over heats and breaks down so we had to deal with that issue.
