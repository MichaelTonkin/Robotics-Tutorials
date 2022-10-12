# define LSEN_LEFT_IN_PIN A0
# define LSEN_CENTRE_IN_PIN A2
# define LSEN_RIGHT_IN_PIN A3
# define EMIT 11
# define MAX_LSEN_PIN 3
# define SECONDS 1000

int lsen_pin[MAX_LSEN_PIN] = {LSEN_LEFT_IN_PIN, LSEN_CENTRE_IN_PIN, LSEN_RIGHT_IN_PIN};

void setup() 
{  
  enableLineSensors();
  beginLogging();
}

void loop() 
{
  lineSensorLoop();
}

void lineSensorLoop()
{
  waitUntilVoltsLow();
}

void enableLineSensors()
{
  pinMode(EMIT, OUTPUT);
  pinMode(LSEN_LEFT_IN_PIN, INPUT);
  pinMode(LSEN_CENTRE_IN_PIN, INPUT);
  pinMode(LSEN_RIGHT_IN_PIN, INPUT);
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

void waitUntilVoltsLow()
{
  unsigned long sensor_time;
  sensor_time = countTime();
  printElapsedTime(sensor_time);
  delay(100);
}

unsigned long countTime()
{
  //unsigned long sensor_time;
  unsigned long start_time = micros();
  unsigned long end_time;
  unsigned long elapsed_time;
  unsigned long current_time;
  unsigned long sensor_read[MAX_LSEN_PIN];
  unsigned long timeout = 5 * SECONDS;
  
  bool done = false;

  int remaining = MAX_LSEN_PIN;
//new code needs to go here
      //we need to charge each capacitor
    //and reconfigure the sensor pins to be read again
  
  for(int i = 0; i < MAX_LSEN_PIN; i++)
  {
    chargeCapacitor(lsen_pin[i]);
  }

  while( remaining > 0)
  {
    for (int w = 0; w < MAX_LSEN_PIN; w++) 
    {
      if(pinIsLow(lsen_pin[w])) {
          if(sensor_read[w] == 0 || sensor_read[w] == NULL)
          {
            current_time = micros();
            elapsed_time = calculateElapsedTime(start_time, current_time);
            sensor_read[w] = elapsed_time;
            remaining = remaining - 1;
          }
      }
    }
    if (timedOut(elapsed_time, timeout))
    {
      remaining = 0;
      //Serial.println("--------------");
      //Serial.println("TIMEOUT");
      //Serial.println("--------------");
    }
  }
  
  return sensor_read;
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