
#include "motors.h"
#include "linesensor.h"
#include "weighted_line.h"
#include "kinematics.h"

# define STATE_INITIAL 0
# define STATE_JOIN_LINE 1
# define STATE_FOUND_LINE 2
# define STATE_FOLLOW_LINE 4
# define STATE_LOST_LINE 5
# define STATE_STOP 6
# define STATE_RETURN_HOME 7

# define GREEN_LED 30
# define YELLOW_LED 13
# define RED_LED 17

WeightedLine_c weightedLine;
int state;

void setup() 
{  
  Serial.begin(4800);
  delay(1000);
  Serial.println("It has begin...");
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  weightedLine.initialize();
  
  state = STATE_INITIAL;
  delay(1000);
}

void loop() 
{
  //updateState(); 
  //selectState();
  weightedLine.lineSensorLoop();
  weightedLine.lineFollow();
}

bool complete;
bool end_of_line = false;
bool return_home = false;
/*void updateState()
{
  Serial.print("");
  if (return_home)
  {
    state = STATE_RETURN_HOME;
  }
  else if (state == STATE_INITIAL && linesensor.getInitComplete())
  {
    state = STATE_JOIN_LINE;
  }
  else if (state == STATE_JOIN_LINE)
  {
    if (linesensor.foundLine() && linesensor.joined == true)
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
    else if (end_of_line == true)
    {
      state = STATE_STOP;
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
    if(linesensor.findLine() == 2)
    {
      end_of_line = true;
    }
  }
  else if (state == STATE_RETURN_HOME)
  {
    linesensor.returnHome();
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
}*/

void stopRobot()
{
  delay(3000);
  return_home = true;
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