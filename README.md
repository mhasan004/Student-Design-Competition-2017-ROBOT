# SDC 2016-2017 Robot Description
This is the robot I have programmed for the SDC 2016-2017 robotic competition. It can climb 3 sets of stairs, sprint forward and back using six brushless motors, lift an object up to 15ft, throw a golf ball, and hit a golf ball placed on the floor. 

The controller has four switches that control each of the five modes. The right joystick (y axis) lets the robot to move forward and backward. The left joystick (x axis) lets the robot to turn left and right. The controller and the robot are explained here: https://mahmudul-hasan.wixsite.com/home/sdc-2017

# Files:
**ALL_Transmitter_Master.ino** : This is the Arduino code for the controller. This code computes all the data need to operate the robot. It then sends all the necessary information to the receiver, which is the robot.

**ALL_Reciever.ino** : This is the Arduino code for the robot. It receives all the necessary data from the controller and controls the appropriate motor. 

**Description Files** : This file contains the flowcharts of my code. It describes how every variable changes in the controller code. For example, The y-axis of the right analog stick maps to the forward/backward speed of each brushless motor. The x-axis of the left analog stick maps to the left/right turn speed of each of the six-brushless motor. The flow charts describe what function changes what variable. 

# Calibrating the Brushless Motors:

One of the most complicated parts was the robot was to accurate control each of the six brushless motors. To control the motors, the program had to read the x and y component positions of the left and right analog joysticks and then compute a range of servo angle values to control individual brushless motors. Each motor has a maximum and a minimum value. The maximum value represented 100% speed forwards and the minimum value represented 100% speed backward.

**1) Finding the Neutral Pulse Range for Each Motor to Arm Them:**

Each motor has its own natural range. The neutral range is a range of pulses where the brushless motors don’t run. These ranges are from 0 to 180. For an ideal brushless motor, the neutral position would be a 90. To start using a brushless motor, you need to feed them their own neutral pulses to wake them up and arm them. I made a test code that slowly feeds a pulse to the motor. The testing program slowly feeds a pulse of 0 to a pulse of 180 to the motor. Most of the motors didn’t run from the 0-15 servo pulses. At 16 most of the motors ran at 100% backward speed. Each motor stopped working in the 80 to 100 servo angles. the neutral position of each motor was in this range. We recorded the range of pulses that the motor remained idle and figured out the neutral position of each motor. We then calculated the midpoint neutral position of each motor so that when we feed the motor a neutral pulse, we will be sure that the motor wouldn’t run.  These midpoint neutral positions were then mapped to the resting joystick analog value. This way, if the joystick is in the rest position, all motors will receive their own neutral pulse and will not move.

**2) SOLVED OVERHEATING ISSUE:**

The next difficult step was to figure out what the 100% forward RPM value of each motor. We noticed that each motor's maximum speed was either slower or faster than another motor. In other words, the motors did not run at the same speed, which caused overheating issues on two of the six brushless motors. After a few minutes, the motors became too hot and would jitter. To combat this issue, we have used a speed tachometer to record the maximum forward and backward speed of each motor. We then set the maximum forward speed of all motor to the lowest forward speed found and maximum backward speed to the highest backward speed that was found. This way, all motors will run at near the same maximum forward and backward speeds. Once again, we have mapped this new range to the joysticks.

**3) Speed Limiter Using a Sliding Potentiometer:**
I made a actuator speed controller using a sliding potentiometer. The potentiometer limits how fast I can go forward and backward for all motors on the robot. For example, if the slider is all the way to the down, all motors will run 0% forwards and backwards (this is the midpoint neutral position - or the stop pulse - for each motor). If the slider is at the top, all motors will run 100% forwards and backwards. For the climbing mode, we needed the motors to go a bit more slowly sometimes, so this function was useful to control the sped at will. 


