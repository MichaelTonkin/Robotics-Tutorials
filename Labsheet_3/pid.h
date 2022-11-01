// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _PID_H
#define _PID_H

// Class to contain generic PID algorithm.
class PID_c {
  private:
  unsigned long time;
  unsigned long left_v;
  unsigned long right_v;
  float rotation_v;

  public:
  
    // Constructor, must exist.
    PID_c() {

    } 

void initialize()
{
  time = 0;
}

void update()
{ 
  updateLeftV();
  updateRightV();
  updateTime();
  Serial.println(left_v);
  resetTime();
}

void updateLeftV()
{
  left_v = count_el / time;
}

void updateRightV()
{
  right_v = count_er / time;
}

void updateTime()
{  
  time += 1;
}

void resetTime()
{
  time = 0;
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

};



#endif
