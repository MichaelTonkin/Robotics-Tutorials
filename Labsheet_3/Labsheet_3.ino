#include <math.h> 
#include "motors.h"
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
# define SENSOR_R 2

Motors_c motors;
LineSensor_c lineSensor;
Calibrator_c calib;

void setup() 
{  
  motors.initialise();
  Serial.begin(4800);
  delay(1000);
  Serial.println("It has begin...");
  delay(1000);
  lineSensor.enableLineSensors();
  calib.calibrate(SENSOR_R);
  calib.calibrate(SENSOR_L);
 
}

void loop() 
{
  lineSensor.lineSensorLoop(); 
}


void beginLogging()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("It has begin...");
}