#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

# define L_PWM_PIN A10
# define L_DIR_PIN 16
# define R_PWM_PIN A9
# define R_DIR_PIN 15

# define FWD LOW
# define REV HIGH
int counter = 0;

// Runs once.
void setup() {

  // Set all the motor pins as outputs.
  // There are 4 pins in total to set.
  // ...
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );
  // Set initial direction (HIGH/LOW)
  // for the direction pins.
  // ...
  digitalWrite(L_DIR_PIN, FWD);  
  digitalWrite(R_DIR_PIN, FWD);
  // Set initial power values for the PWM
  // Pins.
  // ...
  analogWrite(L_PWM_PIN, 0);
  analogWrite(R_PWM_PIN, 0);

  // Start serial, send debug text.
  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

}

// Repeats.
void loop() {

  // Add code to set the direction of rotation
  // for the left and right motor here.
  analogWrite(L_DIR_PIN, REV);
  analogWrite(R_DIR_PIN, REV);

  // Use analogWrite() to set the power to the
  // motors.
  // 20 is a low level of activation to test
  // the motor operation.
  analogWrite( L_PWM_PIN, 255 );
  analogWrite( R_PWM_PIN, 255 );

  // An empty loop can block further uploads.
  // A small delay to prevent this for now.
  delay(5);
}