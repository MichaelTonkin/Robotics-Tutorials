#include "motors.h"
#include "linesensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "pid.h"

# define L_PWM_PIN 10
# define L_DIR_PIN 16
# define R_PWM_PIN 9
# define R_DIR_PIN 15

# define FWD HIGH
# define REV LOW

#define LWR_BOUND_PWM 130
#define UPR_BOUND_PWM 255

bool limit = false;

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
  analogWrite(L_PWM_PIN, 20);
  analogWrite(R_PWM_PIN, 20);

  // Start serial, send debug text.
  Serial.begin(9600);
  delay(1000);
  Serial.println("***RESET***");

}

// Repeats.
void loop() {
  //analogWrite( L_PWM_PIN, 130 );
  //analogWrite( R_PWM_PIN, 130 );
}

/*
 * Sets the power of the motors using analogWrite().
 * This function sets direction and PWM (power).
 * This function catches all errors of input PWM.
 *  inputs: 
 *     pwm   accepts negative, 0 and positve
 *           values.  Sign of value used to set
 *           the direction of the motor.  Values
 *           are limited in range [ ??? : ??? ].
 *           Magnitude used to set analogWrite().
 */
void setLeftMotorPower( float left_pwm )
{
  setLeftMotorDir( left_pwm );
  analogWrite( L_PWM_PIN, abs(left_pwm) );
}

//if pwm is less than 0, then go in reverse.
void setLeftMotorDir( float left_pwm)
{
  if(left_pwm < 0)
  {
    digitalWrite(L_DIR_PIN, FWD);
    Serial.println("fwd");
  }
  else
  {
    digitalWrite(L_DIR_PIN, REV);
    Serial.println("rev");
  }
}

void leftMotorTest()
{
  for(int i = -255; i <=255; i++)
  {
    setLeftMotorPower(i);
    Serial.println(i);
    delay(50);

    if ( i == -130 )
      i = 130;
  }
}