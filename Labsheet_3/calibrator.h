// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _CALIBRATOR_H

#include "motors.h"

#define _CALIBRATOR_H

# define EMIT 11
# define MAX_LSEN_PIN 3
# define LINE_SENSOR_UPDATE 100
# define MOTOR_UPDATE 2000
# define SECONDS 1000
# define GAIN 10
# define SENSOR_L 0
# define SENSOR_C 1
# define SENSOR_R 2
# define L_PWM_PIN A10
# define L_DIR_PIN 16
# define R_PWM_PIN A9
# define R_DIR_PIN 15
# define LSEN_LEFT_IN_PIN A0
# define LSEN_CENTRE_IN_PIN A2
# define LSEN_RIGHT_IN_PIN A3

const int sample_size = 100;
unsigned long samples[MAX_LSEN_PIN][sample_size];
unsigned long sensor_outputs[MAX_LSEN_PIN];
int lsen_pin[MAX_LSEN_PIN] = {LSEN_LEFT_IN_PIN, LSEN_CENTRE_IN_PIN, LSEN_RIGHT_IN_PIN};

class Calibrator_c {
Motors_c motors;


  public:

    Calibrator_c() {

    } 

void calibrate(int sensor)
{
  unsigned long target_time_modi = 50;
  unsigned long start_time = millis();
  unsigned long target_time = target_time_modi + millis();
  int count = 0;

  while(count < sample_size)
  {
    motors.moveLeft(1);
    lineSensorLoop();
    if(timer(target_time, start_time))
    {
      if (samples[sensor][99] == 0)
      {
        samples[sensor][count] = sensor_outputs[sensor];
        Serial.println(samples[sensor][count]);
        count+=1;
      } 
      else
      {
        count = 0;
      }
      start_time = millis();
      target_time = target_time_modi + millis();
    }
  }

  insertionSort(samples[sensor], sample_size);
  printArray(samples[sensor], sample_size);
}

//don't update start time until this function returns true
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

void insertionSort(unsigned long array[], int n) 
{ 
  int i, element, j; 
  for (i = 1; i < n; i++) 
  { 
    element = array[i]; 
    j = i - 1; 
    while (j >= 0 && array[j] > element) 
    { 
      array[j + 1] = array[j]; 
      j = j - 1; 
    } 
  array[j + 1] = element; 
  } 
}  

void printArray(unsigned long array[], int n) 
{ 
  int i; 
  Serial.println("BEGIN PRINTING");
  for (i = 0; i < n; i++) 
  {
    Serial.println(array[i]); 
  }
}

unsigned long getMaxSenValue(int sensor)
{
  return samples[sensor][sample_size - 1];
}

unsigned long getMinSenValue(int sensor)
{
  return samples[sensor][0];
}

unsigned long ls_ts = 0;
void lineSensorLoop()
{
  unsigned long current_ts;
  unsigned long elapsed_t;
  current_ts = millis();
  elapsed_t = current_ts - ls_ts;
  
  if( elapsed_t > LINE_SENSOR_UPDATE ) {

      // Conduct a read of the line sensors
      countTime();
      //lineDetector(); I think this is redundant?
      // Record when this execution happened.
      // for future iterations of loop()
      ls_ts = millis();

  }
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
}

bool timedOut(unsigned long elapsed_time, unsigned long timeout)
{
    if( elapsed_time >= timeout ) 
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

bool pinIsHigh()
{
  if( digitalRead( LSEN_LEFT_IN_PIN ) == HIGH )
  {
    return true;
  }
  return false;
}

bool sensorIsUnread(unsigned long sensor)
{
  if(sensor == 0 || sensor == NULL)
  {
    return true;
  }
  return false;
}

unsigned long calculateElapsedTime(unsigned long start_time, unsigned long end_time)
{
  return end_time - start_time;
}

};


#endif
