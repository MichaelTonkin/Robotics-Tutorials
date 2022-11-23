
class BangBang_c: public LineSensor_c
{

  BangBang_c()
  {
  }

  
int find_line_call = 0;
int findLine()
{
  if(find_line_call == 0)
  {
    kinematics.resetKinematics();
    find_line_call = 1;
  }

  if(kinematics.getDistanceX() <= 5)
  {
    motors.moveForward();
    if (foundLine())
    {
      find_line_call = 0;
      return 1;
    }
  }
  else if (kinematics.getDistanceX() > 5)
  {
    //time to go home
    return 2;
  }
}

void followLine()
{
  if(sensorIsOnTape(SENSOR_C, tape[SENSOR_C]))
  {
    motors.moveForward();
  }
  else if(sensorIsOnTape(SENSOR_L, tape[SENSOR_L]))
  {
    motors.turnLeft();
  }
  else if(sensorIsOnTape(SENSOR_R, tape[SENSOR_R]))
  {
    motors.turnRight();
  }
  else if (sensorIsOnTape(SENSOR_R, tape[SENSOR_R]) && sensorIsOnTape(SENSOR_L, tape[SENSOR_L]))
  {
    motors.turnLeft();
  }
}

bool return_started = false;
bool turned = 0;
void returnHome()
{
  int theta;
  int target_theta;
  target_theta = 55;
  if(return_started == false)
  {
    kinematics.resetKinematics();
    return_started = true;
  }
  theta = kinematics.getTheta();
  if(theta < target_theta && turned == 0)
  {
    motors.turnRight();
  }
  if (theta >= target_theta)
  {
    turned = 1;
  }
  if (kinematics.getDistanceX() <= 15 && turned == 1)
  {
    motors.moveForward();
  }  
  else if (kinematics.getDistanceX() >= 15 && kinematics.getDistanceX() < 19)
  {
    if(foundLine())
    {
      motors.turnRight();
    }
    else
    {
      motors.moveForward();
    }
  }
}

int join_loop = 0;
bool joined = false;
void joinLine()
{
  motors.moveForward();
  if(foundLine() && join_loop < 20)
  {
    motors.turnLeft();
    join_loop += 1;
  }
  else if(foundLine() && join_loop >= 20)
  {
    joined = true;
  }
}

bool faceLine()
{
  if(foundLine())
  {
    return true;
  }
  else
  {
    motors.turnLeft();
  }
  return false;
}




}