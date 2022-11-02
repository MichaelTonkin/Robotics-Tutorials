// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _LINESENSOR_H
#define _LINESENSOR_H

#include "Kinematics.h"

# define LSEN_LEFT_IN_PIN A0
# define LSEN_CENTRE_IN_PIN A2
# define LSEN_RIGHT_IN_PIN A3
# define EMIT 11
# define MAX_LSEN_PIN 3
# define LINE_SENSOR_UPDATE 10
# define MOTOR_UPDATE 2000
# define SECONDS 1000
# define GAIN 10
# define SENSOR_L 0
# define SENSOR_C 1
# define SENSOR_R 2



// Class to operate the linesensor(s).
class LineSensor_c {
  private:
  bool centreIsOnTape;
  bool leftIsOnTape;
  bool rightIsOnTape;
  bool initComplete;
  bool debug;
  public:
  
  Motors_c motors;
  Kinematics_c kinematics;

  int lsen_pin[MAX_LSEN_PIN] = {LSEN_LEFT_IN_PIN, LSEN_CENTRE_IN_PIN, LSEN_RIGHT_IN_PIN};
  unsigned long ls_ts = 0;
  unsigned long sensor_outputs[MAX_LSEN_PIN];
  static const int SAMPLE_SIZE = 100;
  unsigned long samples[MAX_LSEN_PIN][SAMPLE_SIZE];

  unsigned long tape[MAX_LSEN_PIN];

LineSensor_c() {

} 

void initialize()
{
  debug = true;
  enableLineSensors();
  motors.initialise();
  motors.setSpeed(100);
  /*calibrate(SENSOR_R);
  calibrate(SENSOR_L); 
  calibrate(SENSOR_C); 
  
  tape[SENSOR_L] = samples[SENSOR_L][SAMPLE_SIZE-40]; 
  tape[SENSOR_C] = samples[SENSOR_C][SAMPLE_SIZE-40]; 
  tape[SENSOR_R] = samples[SENSOR_R][SAMPLE_SIZE-40]; */

  int threshold = 3000;

  tape[SENSOR_L] = threshold;   
  tape[SENSOR_C] = threshold; 
  tape[SENSOR_R] = threshold;

  kinematics.initialize();
  
  initComplete = true;
  delay(1000);
}

bool getInitComplete()
{
  return initComplete;
}

/*void controller()
{
  
  if(sensorIsOnTape(SENSOR_L, tape[SENSOR_L]))
  {
    //motors.turnLeft();
  }
  else if(sensorIsOnTape(SENSOR_R, tape[SENSOR_R]))
  {
    //motors.turnRight();
  }
  else if(sensorIsOnTape(SENSOR_C, tape[SENSOR_C])) //TODO if none of them are on the tape
  {
    //motors.moveForward();
  }
  
}*/

int find_line_call = 0;
int findLine()
{
  if(find_line_call == 0)
  {
    kinematics.resetKinematics();
    find_line_call = 1;
  }

  if(kinematics.getDistanceX() <= 3)
  {
    motors.moveForward();
    if (foundLine())
    {
      find_line_call = 0;
      return 1;
    }
  }
  else if (kinematics.getDistanceX() > 2)
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

void joinLine()
{
  motors.moveForward();
}

bool faceLine()
{
  if(sensorIsOnTape(SENSOR_L, tape[SENSOR_L]))
  {
    return true;
  }
  else
  {
    motors.turnLeft();
  }
  return false;
}

bool sensorIsOnTape(int sensor, unsigned long tape)
{
  if( sensor_outputs[sensor] > tape )
  {
    return true;
  }  
  else
  {
    return false;
  }
}

bool getCentreLSenIsOnTape()
{ 
    return sensorIsOnTape(SENSOR_C, tape[SENSOR_C]);
}

bool foundLine()
{
  return sensorIsOnTape(SENSOR_C, tape[SENSOR_C]) || sensorIsOnTape(SENSOR_R, tape[SENSOR_R]) || sensorIsOnTape(SENSOR_L, tape[SENSOR_L]);
}

void calibrate(int sensor)
{
  unsigned long target_time_modi = 50;
  unsigned long start_time = millis();
  unsigned long target_time = target_time_modi + millis();
  int count = 0;

  while(count < SAMPLE_SIZE)
  {
    motors.turnLeft();// test printing the sensor output
    lineSensorLoop();
    if(timer(target_time, start_time))
    {
      if (samples[sensor][99] == 0)
      {
        samples[sensor][count] = sensor_outputs[sensor];
        //Serial.println(samples[sensor][count]);
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

  insertionSort(samples[sensor], SAMPLE_SIZE);
  //printArray(samples[sensor], SAMPLE_SIZE);
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
  return samples[sensor][SAMPLE_SIZE - 1];
}

unsigned long getMinSenValue(int sensor)
{
  return samples[sensor][0];
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
      kinematics.update();
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
  if(debug)
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

  //Serial.println(sensor_outputs[0]);
  //Serial.println(sensor_outputs[1]);
  //Serial.println(sensor_outputs[2]);

  // Sum ground sensor activation
  lsen_sum = lsen_left + lsen_centre + lsen_right;
  
  w_left = lsen_left + (lsen_centre * 0.5);
  w_right = lsen_right + (lsen_centre * 0.5);

  // Normalise individual sensor readings 
  // against sum
  w_left =  (lsen_left - (getMinSenValue(SENSOR_L))) / (getMaxSenValue(SENSOR_L) - getMinSenValue(SENSOR_L)) ;
  w_right =  (lsen_right - (getMinSenValue(SENSOR_R))) / (getMaxSenValue(SENSOR_R) - getMinSenValue(SENSOR_R)) ;
  // Calculated error signal
  e_line  = w_left - w_right;
  //Serial.println("line error");
  //Serial.println(e_line);

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
    Serial.println(tape[SENSOR_C]);
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

/*int attempt = 0;
void findLine()
{
  /*
  TODO reset theta after certain amount
  
  int theta;

  if(attempt == 0)
  {
    kinematics.resetRotationVals();
    attempt += 1;
  }

  theta = kinematics.getTheta();
  
  if(foundLine())
  {
    attempt = 0;
    return;
  }  
  else if(theta < 50 && attempt == 1)
  {
    motors.turnRight();
  }
  else if(theta > 50 && attempt == 1)
  { 
    attempt = 2;
  }
  else if(theta > -50 && attempt == 2)
  {
    motors.turnLeft();
  }
  else if (theta < -50 && attempt == 2)
  {
    //gap state
    motors.moveForward();
  }
}
*/
};



#endif
