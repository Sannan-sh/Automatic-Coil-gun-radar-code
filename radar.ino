#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int servoPin1 = 12;  // Pin for the first servo
const int servoPin2 = 7;   // Pin for the second servo
const int servoPin3 = 3;   // Pin for the third servo

long duration;
int distance;
Servo servo1; // First servo object
Servo servo2; // Second servo object
Servo servo3; // Third servo object

unsigned long lastServoMoveTime = 0;
const unsigned long servoDelayTime = 3000; // 1 seconds delay

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
}

void loop() {
  for(int i = 15; i <= 165; i++) {
    servo1.write(i);
    delay(30);
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    if(distance < 35 && millis() - lastServoMoveTime >= servoDelayTime) {
      moveServoTo120AndBack(); // Move servo2 if distance is less than 35 and delay has passed
      lastServoMoveTime = millis();
    }
  }
  
  for(int i = 165; i > 15; i--) {
    servo1.write(i);
    delay(30);
    distance = calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    if(distance < 35 && millis() - lastServoMoveTime >= servoDelayTime) {
      moveServoTo120AndBack(); // Move servo2 if distance is less than 35 and delay has passed
      lastServoMoveTime = millis();
    }
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveServoTo120AndBack() {
  servo2.write(120);
  delay(200);
  servo2.write(0);
}
