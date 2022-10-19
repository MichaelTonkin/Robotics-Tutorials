# define LSEN_LEFT_IN_PIN A0
# define LSEN_CENTRE_IN_PIN A2
# define LSEN_RIGHT_IN_PIN A3
# define EMIT 11
# define MAX_LSEN_PIN 3
# define LINE_SENSOR_UPDATE 100
# define MOTOR_UPDATE 2000
# define SECONDS 1000

int lsen_pin[MAX_LSEN_PIN] = {LSEN_LEFT_IN_PIN, LSEN_CENTRE_IN_PIN, LSEN_RIGHT_IN_PIN};
unsigned long ls_ts = 0;
unsigned long sensor_outputs[MAX_LSEN_PIN] = {0,0,0};

void setup() 
{  
  Serial.begin(4800);
  delay(1000);
  Serial.println("It has begin...");
  delay(1000);
  enableLineSensors();
  //beginLogging();
}

void loop() 
{
  lineSensorLoop();

  float e_line;
  e_line = getLineError(); 

  float turn_pwm;
  turn_pwm = 0;

  turn_pwm = turn_pwm * e_line;

  //setMotorValues( (0 - turn_pwm), (0 + turn_pwm) );
}

float getLineError() {
  float e_line;
  float w_left;
  float w_right;

  // Get latest line sensor readings.
  // You may need to call an updateLineSensor()
  // function from loop before hand - it depends
  // on your implementation.

  // Sum ground sensor activation
  
  // Normalise individual sensor readings 
  // against sum

  // Calculated error signal
  w_right = 0;
  w_left  = 0;
  e_line  = 0;

  // Return result
  return e_line;
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
  Serial.println(sensor_outputs[1]);
  printElapsedTime(sensor_outputs);
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

void doNothing()
{
  //you've been trying to understand my code for a long time. Take a rest here.
}

void beginLogging()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("It has begin...");
}