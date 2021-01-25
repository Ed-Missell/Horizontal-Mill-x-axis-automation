# Horizontal-Mill-x-axis-automation
Horizontal Mill x axis automation
This was developed to control the x axis of a horizontal milling maching using an Arduino Uno, stepper motor and driver.
This program uses the AccelStepper library (https://www.airspayce.com/mikem/arduino/AccelStepper/)
Inputs:
The program operates by a single momentary contact button
There are 2 limit switches, a home and an end stop.(physical home stop and end stop can be moved manualy to make a longer stroke)
There is a potentiomiter which can change the speed of the stepper only when turning in the CW direction.
External to the program there is an e-stop button which will cut power to the stepper driver if pressed.
Operation:
Once the power is turned on, and the e-stop switch is disabled
press the button once and the axis will turn CCW until it reaches the home limit switch.
if the home limit switch is already activated no action will be performed.
once at the home posistion and the button is pressed the axis will turn CW until it reaches the end stop limit switch.
once at the end stop limit switch there will be a slight delay and then the axis will turn CCW at 2 times the rate of speed until it reaches the home limit switch
