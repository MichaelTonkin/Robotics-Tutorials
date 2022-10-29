// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

#include "calibrator.h"

# define LSEN_LEFT_IN_PIN A0
# define LSEN_CENTRE_IN_PIN A2
# define LSEN_RIGHT_IN_PIN A3
# define EMIT 11
# define MAX_LSEN_PIN 3
# define LINE_SENSOR_UPDATE 100
# define MOTOR_UPDATE 2000
# define SECONDS 1000
# define GAIN 10
# define SENSOR_L 0
# define SENSOR_C 1
# define SENSOR_R 

int lsen_pin[MAX_LSEN_PIN] = {LSEN_LEFT_IN_PIN, LSEN_CENTRE_IN_PIN, LSEN_RIGHT_IN_PIN};
unsigned long ls_ts = 0;
unsigned long sensor_outputs[MAX_LSEN_PIN];
Calibrator_c calib;

// Class to operate the linesensor(s).
class LineSensor_c {
  public:
  
    // Constructor, must exist.
    LineSensor_c() {

    } 

void lineSensorLoop()
{
  unsigned long current_ts;
  unsigned long elapsed_t;
  current_ts = millis();
  elapsed_t = current_ts - ls_ts;
  
  if( elapsed_t > LINE_SENSOR_UPDATE ) {

      // Conduct a read of the line sensors
      countTime();
      lineDetector();
      // Record when this execution happened.
      // for future iterations of loop()
      ls_ts = millis();

  }
}

void enableLineSensors()
{
  pinMode(EMIT, OUTPUT);
  pinMode(LSEN_LEFT_IN_PIN, INPUT);
  pinMode(LSEN_CENTRE_IN_PIN, INPUT);
  pinMode(LSEN_RIGHT_IN_PIN, INPUT);
}

void countTime()
{
  //unsigned long sensor_time;
  unsigned long start_time = micros();
  unsigned long elapsed_time;
  unsigned long current_time;
  unsigned long timeout = 5 * SECONDS;
  bool done = false;
  int remaining = MAX_LSEN_PIN;
//new code needs to go here
      //we need to charge each capacitor
    //and reconfigure the sensor pins to be read again
  
  for(int i = 0; i < MAX_LSEN_PIN; i++)
  {
    chargeCapacitor(lsen_pin[i]);
    sensor_outputs[i] = 0;
  }

  while( remaining > 0)
  {
    for (int w = 0; w < MAX_LSEN_PIN; w++) 
    {
      if(pinIsLow(lsen_pin[w])) 
      {
        if(sensorIsUnread(sensor_outputs[w]))
        {
          current_time = micros();
          sensor_outputs[w] = calculateElapsedTime(start_time, current_time);
          remaining = remaining - 1;
        }
      }
    }
    if (timedOut(elapsed_time, timeout))
    {
      remaining = 0;
    }
  }
  
  printElapsedTime(sensor_outputs);
}

void lineDetector()
{
  float e_line;
  e_line = getLineError(); 

  float turn_pwm;
  turn_pwm = 255;

  turn_pwm = turn_pwm * e_line;
}

float getLineError() 
{
  float e_line;
  float w_left;
  float w_right;
  unsigned long lsen_left = sensor_outputs[0];
  unsigned long lsen_centre = sensor_outputs[1];
  unsigned long lsen_right = sensor_outputs[2];
  unsigned long lsen_sum;
  unsigned long upper_bound_r = calib.getMaxSenValue(SENSOR_R);
  unsigned long upper_bound_l = calib.getMaxSenValue(SENSOR_L);
  unsigned long lower_bound_r = calib.getMinSenValue(SENSOR_R);
  unsigned long lower_bound_l = calib.getMinSenValue(SENSOR_L);
  
  // Sum ground sensor activation
  lsen_sum = lsen_left + lsen_centre + lsen_right;
  
  w_left = lsen_left + (lsen_centre * 0.5);
  w_right = lsen_right + (lsen_centre * 0.5);

  // Normalise individual sensor readings 
  // against sum
  w_left =  (w_left - (lower_bound_l)) / (upper_bound_l - lower_bound_l) ;
  w_right =  (w_right - (lower_bound_r)) / (upper_bound_r - lower_bound_r) ;
  // Calculated error signal
  e_line  = w_left - w_right;
  Serial.println("line error");
  Serial.println(e_line);

  speedGainFunc(e_line);
  
  // Return result
  return e_line;

}

float speedGainFunc(float e_line)
{
  return e_line * GAIN;
}

bool sensorIsUnread(unsigned long sensor)
{
  if(sensor == 0 || sensor == NULL)
  {
    return true;
  }
  return false;
}

void chargeCapacitor(int pin)
{
  // Charge capacitor by setting input pin
  // temporarily to output and HIGH
  pinMode( pin, OUTPUT );
  digitalWrite( pin, HIGH );

  // Tiny delay for capacitor to charge.
  delayMicroseconds(10);

  //  Turn input pin back to an input
  pinMode( pin, INPUT );
}

bool pinIsLow(int pin)
{
  if( digitalRead( pin ) == LOW ) 
  {
    return true;
  }
  return false;
}

bool timedOut(unsigned long elapsed_time, unsigned long timeout)
{
    if( elapsed_time >= timeout ) 
    {
      return true;
    }
    return false;
}

unsigned long calculateElapsedTime(unsigned long start_time, unsigned long end_time)
{
  return end_time - start_time;
}

void printElapsedTime(unsigned long elapsed_time[])
{
  for (int i = 0; i < MAX_LSEN_PIN; i++)
  {
    Serial.print("Pin ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println( elapsed_time[i] );
  }
  Serial.print("\n");
}

bool pinIsHigh()
{
  if( digitalRead( LSEN_LEFT_IN_PIN ) == HIGH )
  {
    return true;
  }
  return false;
}

};



#endif
