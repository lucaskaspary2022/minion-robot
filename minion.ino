// Initialization of variables and state arrays

int echoPin = 8; // attach pin D8 to pin Echo of HC-SR04
int trigPin = 7; // attach pin D7 to pin Trig of HC-SR04
int in1 = 4; // variable names for the L298N
int in2 = 5; // variable names for the L298N
int in3 = 9; // variable names for the L298N
int in4 = 10; // variable names for the L298N

int ledpin = 13; //specify the LED pin to pin 13

long duration; // duration of sound wave travel
int distance; // distance measurement

// Setup function: sets up the pin modes for the connections with the HC-SR0 and the L298N, and starts the Arduino.
void setup() {

  pinMode (trigPin, OUTPUT) ; // sonar digital pin mode for trig
  pinMode (echoPin, INPUT); // sonar digital pin mode for echo
  
  pinMode (in1, OUTPUT); // all L298N digital pins are outputs
  pinMode (in2, OUTPUT); // all L298N digital pins are outputs
  pinMode (in3, OUTPUT); // all L298N digital pins are outputs
  pinMode (in4, OUTPUT); // all L298N digital pins are outputs

  Serial.begin (9600) ; // use default of 9600 baud rate for serial communication
}

// Loop function: it essentially calculates the distance of the ultrasonic sensor from an obstacle using the pulseIn function and its returning value
// to calculate the distance from the obstacles, which will determine the robot's behavior.
void loop() {

  // Clears the trigPin condition
  digitalWrite (trigPin, LOW);//starts trig pin low
  delayMicroseconds (2); //waits for hardware to respond
  digitalWrite (trigPin, HIGH); //makes trig pin high
  delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
  digitalWrite (trigPin, LOW); //after 10 microseconds trig pin is brought low
  duration = pulseIn (echoPin, HIGH); //reads echo as it receives the pulse and stores duration
  distance = duration * 0.034 / 2; // Converts the time of flight to distance to object

  // Displays the distance on the serial Monitor
  Serial.print ("Distance: ");
  Serial.print (distance);
  Serial.println(" cm");
  
  // Checks for the distance the robot is from the user. If the distance is of 15 cm, it should go backwards and run away from the user.
  if (distance <= 15) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(ledpin, HIGH);
    
  } else if (distance <= 45) { // Checks for the distance the robot is from the user. If the distance is of 45 cm, it should go forward and follow the user.

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(ledpin, HIGH);
    
  } else { // Checks for the distance the robot is from the user. If the distance doesn't satisfy any of the above conditions, the robot should stop, as the user is out of the sensor's range

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(ledpin, LOW);
    
  }
  delay(10);
  
}