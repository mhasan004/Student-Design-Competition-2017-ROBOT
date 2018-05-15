# SDC 2016-2017 ROBOT 
This is the robot I have programmed for the SDC 2016-2017 robotic competition. It can climb 3 sets of stairs, sprint forward and back using six brushless motors, lift an object up to 15ft, throw a golf ball, and hit a golf ball placed on the floor. 

The controller has four switches that control each of the five modes. The right joystick (y axis) lets the robot to move forward and backward. The left joystick (x axis) lets the robot to turn left and right. The controller and the robot is explained here: https://mahmudul-hasan.wixsite.com/home/sdc-2017

# Files:
**ALL_Transmitter_Master.ino** : This is the Arduino code for the controller. This code computes all of the data need to operate the robot. 
**ALL_Reciever.ino** : This is the Arduino code for the robot. 
**Description Files** : This file contains the flowcharts ofmy code. It describes how the every variable changes. For example, The y-axis of the right analog stick maps to the forward/backward speed of each brushless motor. The x-axis of the left analog stick maps to the left/right turn speed of each of the six brushless motor. The flow charts describes what function changes what variable. 

# Calibrating the Brushless Motors:

One of the most complicated parts was the robot was to accurate control each of the six brushless motors. To control the motors, the program had to read the x and y component positions of the left and right analog joysticks and then compute a range of servo angle values to control individual brushless motors. Each motor has a maximum and a minimum value. The maximum value represented 100% speed forwards and the minimum value represented 100% speed backward.

**1) SDC Flow Images**
The two images in the master branch called **"SDC17 Flow.pdf"** and **"SDC Flow2.pdf"** describes how the variable changes to calibration the motors. 

**2) Finding the Neutral Pulse Range for Each Motor:**

Each motor has its own natural range. The neutral range is a range of the servo angle values (0 to 180) where the motor does not spin. The maximum and minimum ranges were obtained by manually testing each motor. I made a test code that slowly feeds a pulse to the motor. the testing program slowly feeds a pulse of 0 to a pulse of 180 to the motor. For most of the motors, from 0-15, the motors didn't run. At 16 most of the motors ran at 100% backward. As the pulse got near 90, each motor stopped in the 80 to 100 mark. In this range, we recorded the range of pulses that the motor remained idle. This was the neutral position for each motor. A midpoint value was then calculated. This midpoint value was then mapped to the resting joystick analog value. This way, if the joystick is in the rest position, all motors will receive their own neutral pulse and will not move.

**3) Finding 100% Forward Speed of Each Motor:**

The next difficult step was to figure out what the 100% forward value for each motor was. A problem we noticed was that each motor's 100% speed was either slower or faster than other motors. In other words, the motors did not run at the same speed. This is an issue because if all the motors don't run at the same speed, there will be overheating and control issues. To combat this issue, we have used a speed tachometer to record the speed of each motor. We have tested each motor with a fully charged LiPo battery. After getting an average max forward speed of each motor, we set the max forward speed of all motor the lowest average max forward speed we have obtained for the six motors. This way, all motors will run at near the same max forward and backward speed. Once again, we have mapped this to the joystick.

I made a speed controller using a sliding potentiometer. the potentiometer controls how much I can go forward and backward. For example, if the slider is all the way to the down, all motors will run in 0% forwards and backward (this is the midpoint neutral position for each motor). If the slider is at the top, each motor can will 100% forward and backward.

**4) Others**

There was also a broken brushless motor that constantly overheats and breaks down so we had to deal with that issue.

