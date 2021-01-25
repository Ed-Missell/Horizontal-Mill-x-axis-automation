
#include <AccelStepper.h> // Include the AccelStepper library:


#define dirPin 2 // Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define stepPin 3
#define motorInterfaceType 1



#define home_switch 13    // Pin 13 connected to Home Switch (MicroSwitch)
long initial_homing = -1; // Used to Home Stepper at startup (number of steps per check of switch)

#define limit_switch 12 // Pin 13 connected to Home Switch (MicroSwitch)
long initial_limit = 1; // Used to find the limit switch(number of steps per check of switch)

#define ANALOG_IN A0 // This defines the analog input pin for reading the control voltage
int analog_in ;  // Tested with a 10k linear pot between 5v and GND

#define m_button 8    // Pin 8 connected to motor button (black button)

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);   // Create a new instance of the AccelStepper class:

void setup() {
  Serial.begin(9600); //opens serial port, sets data rate to 9600 bps

  pinMode(home_switch, INPUT_PULLUP);

  pinMode(limit_switch, INPUT_PULLUP);

  pinMode(m_button, INPUT_PULLUP);

  //stepper.setMaxSpeed(10000.0);      // Set Max Speed of Stepper
  stepper.setAcceleration(5000); // Set Acceleration of Stepper
  //stepper.setSpeed(50);


  while (digitalRead(m_button) == true) {  //check button press here and if it is pressed then run the program loop
    analog_in = analogRead(ANALOG_IN) * 10;
    Serial.println(analog_in);
  }
  Serial.println(F("run program"));
}

void loop() {

  //code you always run here; you can leave this section blank if you want the entire program to stop and start, or add code here if you want it to always run

analog_in = analogRead(ANALOG_IN) * 20;
  stepper.setMaxSpeed(analog_in);      // Set Speed of Stepper BASED OFF OF 10K POT INPUT

  //limit1 code****************************************************************************************************

  if (digitalRead(home_switch) == true) {//do not move if home limit switch is already activated
    while (digitalRead(home_switch)) {  // Make the Stepper move CCW(initial homing value) until the switch is activated
  
      stepper.moveTo(initial_homing);  // Set the position to move to
      initial_homing--;               // Decrease by 1 for next move if needed
      stepper.run();                 // Start moving the stepper
    }
  }
  stepper.setCurrentPosition(0);

  
  //limit1 code^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  Serial.println(F("press button to move to limit"));
  while (digitalRead(m_button) == true) {   //check button press here and if it is pressed then run the following lines

  }


  //code you only run after button was pressed************************************************************************
  //limit 2 code
  while (digitalRead(limit_switch)) {  // Make the Stepper move CW(initial limit value) until the switch is activated
    
    analog_in = analogRead(ANALOG_IN) * 10;
      stepper.setMaxSpeed(analog_in);      // Set Speed of Stepper BASED OFF OF 10K POT INPUT
      
    stepper.moveTo(initial_limit);     // Set the position to move to
    initial_limit++;                 // Decrease by 1 for next move if needed
    stepper.run();                   // Start moving the stepper
  }
  stepper.setCurrentPosition(0);
  delay(2000);
  //code you only run after button was pressed^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

}
