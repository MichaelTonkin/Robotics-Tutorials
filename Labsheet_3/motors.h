// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _MOTORS_H
#define _MOTORS_H
# define L_PWM_PIN A10
# define L_DIR_PIN 16
# define R_PWM_PIN A9
# define R_DIR_PIN 15

# define FWD HIGH
# define REV LOW

#define LWR_BOUND_PWM 130
#define UPR_BOUND_PWM 255

class Motors_c {
  public:

    // Constructor, must exist.
    Motors_c() {

    } 

    // Use this function to 
    // initialise the pins and 
    // state of your motor(s).
    void initialise() {
      pinMode( L_PWM_PIN, OUTPUT );
      pinMode( L_DIR_PIN, OUTPUT );
      pinMode( R_PWM_PIN, OUTPUT );
      pinMode( R_DIR_PIN, OUTPUT );
      // Set initial direction (HIGH/LOW)
      // for the direction pins.
      // ...
      digitalWrite(L_DIR_PIN, REV);  
      digitalWrite(R_DIR_PIN, REV);
      // Set initial power values for the PWM
      // Pins.
      // ...
      analogWrite(L_PWM_PIN, 0);
      analogWrite(R_PWM_PIN, 0);

      // Start serial, send debug text.
      Serial.begin(4800);
      delay(1000);
      Serial.println("***RESET***");
    }


void setMotorSpeed()
{
  //empty
}

void turnLeft()
{
  setMotorDir(L_PWM_PIN, 1);
  setMotorPower(L_PWM_PIN, 127);
}

void turnRight()
{
  setMotorDir(R_PWM_PIN, 1);
  setMotorPower(R_PWM_PIN, 127);
}

void setMotorPower( int pin, float power )
{
  analogWrite( pin, abs(power) );
}

//if power is less than 0, then go in reverse.
void setMotorDir( int pin, int dir)
{
  int dir_pin;

  dir_pin = setDirPin(pin);

  if(dir == -1)
  {
    digitalWrite(dir_pin, FWD);
  }
  else if (dir == 1)
  {
    digitalWrite(dir_pin, REV);
  }
}

int setDirPin(int pwn_pin)
{
  if (pwn_pin == L_PWM_PIN)
  {
    return L_DIR_PIN;
  }
  else if (pwn_pin == R_PWM_PIN)
  {
    return R_DIR_PIN;
  }
}
    
};



#endif
