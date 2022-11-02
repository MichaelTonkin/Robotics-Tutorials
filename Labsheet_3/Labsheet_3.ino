
#include "motors.h"
#include "linesensor.h"
#include "kinematics.h"

# define STATE_INITIAL 0
# define STATE_JOIN_LINE 1
# define STATE_FOUND_LINE 2
# define STATE_FOLLOW_LINE 4
# define STATE_LOST_LINE 5
# define STATE_STOP 6

# define GREEN_LED 30
# define YELLOW_LED 13
# define RED_LED 17

LineSensor_c linesensor;
int state;

void setup() 
{  
  Serial.begin(4800);
  delay(1000);
  Serial.println("It has begin...");

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  state = STATE_INITIAL;
  delay(1000);
}

void loop() 
{
  updateState(); 
  selectState();
  linesensor.lineSensorLoop();
}

bool complete;

void updateState()
{
  Serial.println(state);
  if (state == STATE_INITIAL && linesensor.getInitComplete())
  {
    state = STATE_JOIN_LINE;
  }
  else if (state == STATE_JOIN_LINE)
  {
    if (linesensor.foundLine())
    {
      state = STATE_FOUND_LINE;
    }
  }
  else if (state == STATE_FOLLOW_LINE && (linesensor.foundLine() == 0))
  {
    state = STATE_LOST_LINE;
  }
  else if (state == STATE_FOUND_LINE)
  {
    if(linesensor.faceLine())
      state = STATE_FOLLOW_LINE;
  }
  else if (state == STATE_LOST_LINE)
  {
    if(linesensor.foundLine())
    {
      state = STATE_FOUND_LINE;
    }
  }
}

void selectState()
{
  
if( state == STATE_INITIAL ) {

    linesensor.initialize();    

  } else if( state == STATE_JOIN_LINE ) {

    linesensor.joinLine();
        
  } else if( state == STATE_FOUND_LINE ) {
    foundLineBeeps();
  }
  else if (state == STATE_STOP)
  {
    stopRobot();
  }
  else if (state == STATE_FOLLOW_LINE)
  {
    followLine();
  }
  else if (state == STATE_LOST_LINE)
  {
    linesensor.findLine();
  }
  else {

    Serial.print("System Error, Unknown state: ");
    Serial.println( state );

    Serial.print("Error code: ");
    //Serial.println( error_code );

    stopRobot();
    signalError();
  }
  
}

void foundLineBeeps()
{
  digitalWrite( GREEN_LED, HIGH );
  digitalWrite( RED_LED, HIGH );
  digitalWrite( YELLOW_LED, HIGH );
  //delay(4000);
}

void followLine()
{
  linesensor.followLine();
}

void stopRobot()
{

}

void signalError()
{

}


bool timer(unsigned long target_time, unsigned long start_time)
{
  unsigned long current_ts;
  unsigned long elapsed_ts;
  current_ts = millis();

  if( current_ts > target_time ) 
  {
      return true;
  }

  return false;
  
}

void beginLogging()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("It has begin...");
}