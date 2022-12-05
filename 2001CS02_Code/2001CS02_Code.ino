#include <Servo.h> // this library allows an Arduino board to control RC (hobby) servo motors

Servo servo;

int trigPin = 5, echoPin = 6, servoPin = 7; // initialising all three pins
long duration, dist, average;
long arr[3];

void setup() {
  Serial.begin(9600); // establishes serial communication between Arduino board and another device
  servo.attach(servoPin); // attaches servo motor to the Arduino board
  pinMode(trigPin, OUTPUT); // configuring trigPin to behave as an output
  pinMode(echoPin, INPUT); // configuring echoPin to behave as an input
  servo.write(0); // sets the angle of the shaft (in degrees)
  delay(100); // delaying by 100 milli seconds
  servo.detach(); // detaches the servo variable from its pin
}

void measure() {
  digitalWrite(trigPin, LOW); // sets the trigPin off
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); // sets the trigPin on
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW); // sets the trigPin off
  pinMode(echoPin, INPUT); // configuring echoPin to behave as an input
  duration = pulseIn(echoPin, HIGH); // returns the length of the pulse in microseconds
  dist = (duration / 2) / 29.1;  // obtaining distance (in 29.1ms sound travels 1cm)
}

void loop() {
  for (int i = 0; i < 3; i++) {
    measure();
    arr[i] = dist;
    delay(10);
  }
  dist = (arr[0] + arr[1] + arr[2]) / 3; // above code takes three continuous measurements with 0.01 seconds delay and then take their average

  if ( dist < 50 ) {
    servo.attach(servoPin); // attaches servo motor to the Arduino board
    delay(1);
    servo.write(150);
    delay(1000);
    servo.detach(); // detaches the servo variable from its pin
  }
  else
  {
    servo.attach(servoPin); // attaches servo motor to the Arduino board
  
    servo.write(0);
    delay(1000);
    servo.detach(); // detaches the servo variable from its pin
  }
  

  Serial.println(dist); // prints data to the serial port as human-readable ASCII text
}
