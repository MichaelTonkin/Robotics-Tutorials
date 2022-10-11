# define LSEN_LEFT_IN_PIN A0
# define LSEN_CENTRE_IN_PIN A2
# define LSEN_RIGHT_IN_PIN A3
# define EMIT 11
# define SECONDS 1000

void setup() 
{
  
  enableLineSensors();
  Serial.begin(9600);
  delay(1000);
  Serial.println("It has begin...");

}

void loop() 
{
  lineSensorLoop();
}

void enableLineSensors()
{
  pinMode(EMIT, OUTPUT);
  pinMode(LSEN_LEFT_IN_PIN, INPUT);
  pinMode(LSEN_CENTRE_IN_PIN, INPUT);
  pinMode(LSEN_RIGHT_IN_PIN, INPUT);
}

void lineSensorLoop()
{
  chargeCapacitor();
  waitUntilVoltsLow();
}

void chargeCapacitor()
{
  // Charge capacitor by setting input pin
  // temporarily to output and HIGH
  pinMode( LSEN_LEFT_IN_PIN, OUTPUT );
  digitalWrite( LSEN_LEFT_IN_PIN, HIGH );

  // Tiny delay for capacitor to charge.
  delayMicroseconds(10);

  //  Turn input pin back to an input
  pinMode( LSEN_LEFT_IN_PIN, INPUT );
  
}

void waitUntilVoltsLow()
{
  unsigned long elapsed_time;
    // Places to store microsecond count
  unsigned long start_time; // t_1
  unsigned long end_time;   // t_2

  countTime(start_time, end_time);
}

void countTime(unsigned long start_time, unsigned long end_time)
{
    // Store current microsecond count
  start_time = micros();

  while(pinIsHigh()) {
    doNothing();

    //wait for pin to become LOW
  }

  end_time = micros();
  
  elapsed_time = calculateElapsedTime(start_time, end_time);

  // Print output.
  printElapsedTime(elapsed_time);

  // Delay, just so that we have time toread the 
  // values when using Serial.print().
  delay(100);
}

unsigned long calculateElapsedTime(unsigned long start_time, unsigned long end_time)
{
  return end_time - start_time;;
}

void printElapsedTime(unsigned long elapsed_time)
{
  Serial.print("Left line sensor: " );
  Serial.print( elapsed_time );
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