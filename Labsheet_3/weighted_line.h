#ifndef WeightedLine_h
#define WeightedLine_h

class WeightedLine_c: public LineSensor_c
{
  public:
  
  int index;
  int threshold = 1600;
  bool stop = false;
  unsigned long start_time;

  WeightedLine_c()
  {
  }

void getErrorAndTime(float e_line)
{
  
  unsigned long time = millis();
  if (time >= start_time + 10)
  {
    start_time = time;
    if(e_line == 0)
    {
      //do nothing
    }
    else
    {

      error_time[index][0] = e_line;
      error_time[index][1] = time;
    }
    index += 1;
  }
}

bool lineFollow()
{
  float e_line;
  e_line = getLineError(); 
  float turn_pwm = 60;

  turn_pwm = turn_pwm * e_line * 5;

  if (turn_pwm < 0)
  {
    turn_pwm = turn_pwm * -1;
  }

  motors.setPwm(turn_pwm);
  if (stop)
  {
    return true;
  }
  else if (!isOnLine(threshold))
  {
    if(e_line > 0) //gone too far right
    {
      motors.turnLeft();
      getErrorAndTime(e_line);
    }
    else if (e_line < 0)
    {
      motors.turnRight();
      getErrorAndTime(e_line);
    }
  }
  else
  {
    motors.setPwm(20);
    motors.moveForward();
  }
  
  return false;
}

bool isOnLine(int threshold)
{
  if (sensor_outputs[1] >= threshold)
  {
    return true;
  }
  else
  {
    return false;
  }
}

float getLineError() 
{
  float e_line;
  float w_left;
  float w_right;
  float lsen_left = sensor_outputs[0];
  float lsen_centre = sensor_outputs[1];
  float lsen_right = sensor_outputs[2];

  float lsen_sum;
  float n_left;
  float n_right;
  float n_centre;

  lsen_sum = lsen_left + lsen_centre + lsen_right;

  if(lsen_left < threshold && lsen_centre < threshold && lsen_right < threshold)
  {
    stop = true;
  }

  n_left = lsen_left / lsen_sum; 
  n_right = lsen_right  / lsen_sum;
  n_centre = lsen_centre  / lsen_sum;

  w_left = n_left + (n_centre * 0.5);
  w_right = n_right + (n_centre * 0.5);

  e_line  = w_left - w_right;
  
  return e_line;

}

};
#endif