// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#define _MOTORS_H
# define L_PWM_PIN A10
# define L_DIR_PIN 16
# define R_PWM_PIN A9
# define R_DIR_PIN 15

# define FWD LOW
# define REV HIGH

#define LWR_BOUND_PWM 127
#define UPR_BOUND_PWM 255


class Motors_c {
  public:
  int speed = 0;

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

//due to the motor speed being very high even at low PWM setting
//use this function to pause motor function to allow it to slow down
unsigned long last_ts = 0;
bool motorPause()
{
  unsigned long current_ts;
  unsigned long elapsed;
  current_ts = millis();
  elapsed = current_ts - last_ts;
  
  int pause = getSpeed();
  
  if( elapsed > pause ) {
      last_ts = current_ts;  
      return true;
  }
  return false;
}

void setSpeed(int new_speed)
{
  speed = new_speed;
}

int getSpeed()
{
  return speed;
}

void moveForward()
{
  moveLeft(1);
  moveRight(1);
}

void moveReverse()
{
  moveLeft(-1);
  moveRight(-1);
}

void turnLeft()
{
  moveLeft(-1);
  moveRight(1);  
}

void turnRight()
{
  moveLeft(1);
  moveRight(-1);
}

void moveLeft(int dir)
{
  setMotorDir(L_PWM_PIN, dir);
  
  setMotorPower(L_PWM_PIN, 130);
  motorPause();
  setMotorPower(L_PWM_PIN, 0);
  motorPause();
}

void moveRight(int dir)
{
  setMotorDir(R_PWM_PIN, dir);
  setMotorPower(R_PWM_PIN, 130);
  motorPause();
  setMotorPower(R_PWM_PIN, 0);
  motorPause();
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
    digitalWrite(dir_pin, REV);
  }
  else if (dir == 1)
  {
    digitalWrite(dir_pin, FWD);
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



