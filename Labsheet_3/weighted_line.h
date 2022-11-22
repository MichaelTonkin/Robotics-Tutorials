#ifndef WeightedLine_h
#define WeightedLine_h

class WeightedLine_c: public LineSensor_c
{
  public:
  WeightedLine_c()
  {
  }

  
void lineFollow()
{
  float e_line;
  e_line = getLineError(); 

  float turn_pwm = 130;

  turn_pwm = turn_pwm * e_line;
  motors.setSpeed(turn_pwm);
  if (isOnLine(3000))
  {
    if(e_line > 0) //gone too far right
    {
      motors.turnLeft();
    }
    else if (e_line < 0)
    {
      motors.turnRight();
    }
    else if (e_line == 0)
    {
      motors.setSpeed(130);
      motors.moveForward();
    }
  }
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

  /*Serial.println(sensor_outputs[0]);
  Serial.println(sensor_outputs[1]);
  Serial.println(sensor_outputs[2]);*/

  // Sum ground sensor activation
  lsen_sum = lsen_left + lsen_centre + lsen_right;
  
  /*n_left = (lsen_left - (left_min)) / (left_max - left_min); 
  n_right = (lsen_right - (right_min)) / (right_max - right_min);
  n_centre = (lsen_centre - (centre_min)) / (centre_max - centre_min);*/
  
  n_left = lsen_left / lsen_sum; 
  n_right = lsen_right  / lsen_sum;
  n_centre = lsen_centre  / lsen_sum;

  w_left = n_left + (n_centre * 0.5);
  w_right = n_right + (n_centre * 0.5);

  // Normalise individual sensor readings 
  // against sum
  //w_left =  (lsen_left - (getMinSenValue(SENSOR_L))) / (getMaxSenValue(SENSOR_L) - getMinSenValue(SENSOR_L)) ;
  //w_right =  (lsen_right - (getMinSenValue(SENSOR_R))) / (getMaxSenValue(SENSOR_R) - getMinSenValue(SENSOR_R)) ;
  //w_left =  (lsen_left - (1448)) / (6808 - 1448) ;
  //w_right =  (lsen_right - (1525)) / (7602 - 1525) ;

  // Calculated error signal
  e_line  = w_left - w_right;
  // Return result
  return e_line;

}

float speedGainFunc(float e_line)
{
  return e_line * GAIN;
}

};
#endif