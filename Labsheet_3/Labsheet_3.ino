
#include "motors.h"
#include "linesensor.h"

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

LineSensor_c linesensor;

void setup() 
{  
  Serial.begin(4800);
  delay(1000);
  Serial.println("It has begin...");
  delay(1000);
  linesensor.initialize();
 
}

void loop() 
{
  linesensor.lineSensorLoop(); 
}


void beginLogging()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("It has begin...");
}