
#include "motors.h"
#include "linesensor.h"

# define STATE_INITIAL 0
# define STATE_JOIN_LINE 1
# define STATE_FOUND_LINE 2

LineSensor_c linesensor;
int state;

void setup() 
{  
  Serial.begin(4800);
  delay(1000);
  Serial.println("It has begin...");
  delay(1000);
  linesensor.initialize();
 
}

void loop() 
{
  linesensor.lineSensorLoop();
  linesensor.controller();
  //selectState();
  //updateState(); 
}


void selectState()
{

if( state == STATE_INITIAL ) {

    linesensor.initialize();     

  } else if( state == STATE_JOIN_LINE ) {

    driveForwards();     

  } else if( state == STATE_FOUND_LINE ) {

    foundLineBeeps();

  } else {

    Serial.print("System Error, Unknown state: ");
    Serial.println( state );

    Serial.print("Error code: ");
    //Serial.println( error_code );

    stopRobot();
    signalError();
  }
  
}

void driveForwards()
{

}

void foundLineBeeps()
{

}

void stopRobot()
{

}

void signalError()
{

}

void updateState()
{

}

void intialisingBeeps() 
{

}

void foundLineBeep() 
{

}

void beginLogging()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("It has begin...");
}