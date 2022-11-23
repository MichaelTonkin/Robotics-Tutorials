
#include "motors.h"
#include "linesensor.h"
#include "weighted_line.h"
#include "kinematics.h"

/*# define STATE_INITIAL 0
# define STATE_JOIN_LINE 1
# define STATE_FOUND_LINE 2
# define STATE_LOST_LINE 5*/
# define STATE_FOLLOW_LINE 4
# define STATE_REPORT 6
# define STATE_STOP 7

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
  
  state = STATE_FOLLOW_LINE;
  delay(1000);
}

void loop() 
{
  updateState(); 
  selectState();
}

bool complete;
bool stopped = false;
bool end_of_line = false;
void updateState()
{
  if (state == STATE_STOP)
  {  
    weightedLine.motors.setPwm(0);    
    weightedLine.motors.moveForward();
    stopped = true;
  }
  else if(state == STATE_FOLLOW_LINE)//I think it is perhaps still trying to call this? Either way this is the only point where motors is called.
  {
    weightedLine.lineSensorLoop();
    if(weightedLine.lineFollow())
    {
      end_of_line = true;
    }
  }
  else if (state == STATE_REPORT)
  {
    weightedLine.getData();
    delay(1000);
  }

}

void selectState()
{
  
  if (state == STATE_FOLLOW_LINE && end_of_line)
  {
    state = STATE_STOP;
  }
  else if (state == STATE_STOP && stopped)
  {
    state = STATE_REPORT;
  }
  
}

void foundLineBeeps()
{
  digitalWrite( GREEN_LED, HIGH );
  digitalWrite( RED_LED, HIGH );
  digitalWrite( YELLOW_LED, HIGH );
  //delay(4000);
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