#include <Adafruit_MLX90614.h>
#include "Ultrasonic.h"
#include <Wire.h>

#define ULTRASONIC_SENSOR_TRIG 9
#define ULTRASONIC_SENSOR_ECHO 8         
#define MAX_REGULAR_MOTOR_SPEED 160
#define MAX_MOTOR_ADJUST_SPEED 165
#define DISTANCE_TO_CHECK 50
#define DISTANCE_TO_STOP 15
#define TURN_DURATION 500

// Right motor
int enableRightMotor = 5;
int rightMotorPin1 = 8;
int rightMotorPin2 = 9;

// Left motor
int enableLeftMotor = 6;
int leftMotorPin1 = 10;
int leftMotorPin2 = 11;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed);
void turnCar();
Ultrasonic ultrasonic(7);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  mlx.writeEmissivity(1.0);

  Serial.println("Adafruit MLX90614 test");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  }

  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  rotateMotor(0, 0);
}

void loop() {
  int objectTemp = mlx.readObjectTempC();
  int distance = ultrasonic.MeasureInCentimeters();

  Serial.print("Object Temp: ");
  Serial.print(objectTemp);
  Serial.println(" *C");

  if (objectTemp < 24 || distance > DISTANCE_TO_CHECK)
  {
    turnCar();
    }

  else if (objectTemp >= 24 && distance > DISTANCE_TO_STOP && distance <= DISTANCE_TO_CHECK)
  {
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
    while (true) {
      int objectTemp = mlx.readObjectTempC();
      int distance = ultrasonic.MeasureInCentimeters();
      if (objectTemp < 24 || distance > 0 && distance <= DISTANCE_TO_STOP || distance > DISTANCE_TO_CHECK) {
         rotateMotor(0, 0);
          delay(1000);
          return;  
      }
    //  else if (distance > DISTANCE_TO_CHECK && objectTemp < 24)
      //  turnCar();
       // break;
  }
}
 
}

void turnCar() {
//Rotate car to left    
    rotateMotor(-MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED);
    delay(930);
 
    //Read left side distance using ultrasonic sensor
  int objectTemp = mlx.readObjectTempC();
  int distance = ultrasonic.MeasureInCentimeters();
    
    if (objectTemp >= 24 && distance > 0 && distance <= DISTANCE_TO_CHECK)
    {
      rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
      while (true) {
      int objectTemp = mlx.readObjectTempC();
      int distance = ultrasonic.MeasureInCentimeters();
      if (objectTemp < 24 || distance > 0 && distance <= DISTANCE_TO_STOP || distance > DISTANCE_TO_CHECK) {
         rotateMotor(0, 0);
          delay(1000);
          return;  
      }
    }
    }
      else {
    //Rotate car to right
    rotateMotor(MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED);     
    delay(930);    
    
    //Read right side distance using ultrasonic sensor   
      int turningrightobjectTemp = mlx.readObjectTempC();
      int distanceRight = ultrasonic.MeasureInCentimeters();
           
    if (objectTemp >= 24 && distance > 0 && distance <= DISTANCE_TO_CHECK)
    {
      rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
      while (true) {
      int objectTemp = mlx.readObjectTempC();
      int distance = ultrasonic.MeasureInCentimeters();
      if (objectTemp < 24 || distance > 0 && distance <= DISTANCE_TO_STOP || distance > DISTANCE_TO_CHECK) {
         rotateMotor(0, 0);
          delay(1000);
          return;  
      }
  }
      }
}
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed >= 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed >= 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}
