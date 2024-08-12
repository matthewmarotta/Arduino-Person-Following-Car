#include "Ultrasonic.h"
 
#define ULTRASONIC_SENSOR_TRIG 9
#define ULTRASONIC_SENSOR_ECHO 8               
#define MAX_REGULAR_MOTOR_SPEED 85
#define MAX_MOTOR_ADJUST_SPEED 130
#define DISTANCE_TO_CHECK 50
#define DISTANCE_TO_STOP 15
#define TURN_DURATION 500 // duration for turning in milliseconds
 
//Right motor
int enableRightMotor=5;
int rightMotorPin1=8;
int rightMotorPin2=9;
 
//Left motor
int enableLeftMotor=6;
int leftMotorPin1=10;
int leftMotorPin2=11;
 
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed);
void turnCar();
Ultrasonic ultrasonic(7);
 
void setup()
{
  // put your setup code here, to run once:
  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);
 
  rotateMotor(0,0);   
}
 
void loop()
{
 
  int distance = ultrasonic.MeasureInCentimeters();
 
  
  if (distance > DISTANCE_TO_CHECK)
  {
    turnCar();
    }
 
  else if (distance > 0 && distance <= DISTANCE_TO_STOP)
  {
    rotateMotor(0, 0);
          delay(1000);
          return;  
  }
    
  else if (distance > DISTANCE_TO_STOP && distance <= DISTANCE_TO_CHECK)
  {
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
    while (true) {
      int distance = ultrasonic.MeasureInCentimeters();
      if (distance > 0 && distance <= DISTANCE_TO_STOP) {
         rotateMotor(0, 0);
          delay(1000);
          return;  
      }
      else if (distance > DISTANCE_TO_CHECK)
        turnCar();
        break;
  }
}
}
 
 
void turnCar() {
//Rotate car to left    
    rotateMotor(-MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED);
    delay(500);
 
    //Read left side distance using ultrasonic sensor
    int distance = ultrasonic.MeasureInCentimeters();
 
    if (distance > DISTANCE_TO_STOP && distance <= DISTANCE_TO_CHECK)
    {
      rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
      while (true) {
      int distanceLeft = ultrasonic.MeasureInCentimeters();
      if (distanceLeft > 0 && distanceLeft <= DISTANCE_TO_STOP) {
         rotateMotor(0, 0);
          delay(1000);
          return;  
      }
    }
    }
      else {
    //Rotate car to right
    rotateMotor(MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED);     
    delay(500);    
    
    //Read right side distance using ultrasonic sensor   
    int distance = ultrasonic.MeasureInCentimeters();
           
    if (distance > DISTANCE_TO_STOP && distance <= DISTANCE_TO_CHECK)
    {
      rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
      while (true) {
      int distanceLeft = ultrasonic.MeasureInCentimeters();
      if (distanceLeft > 0 && distanceLeft <= DISTANCE_TO_STOP) {
         rotateMotor(0, 0);
          delay(500);
          return;  
    }  
  }
      }
}
}
 
 
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed >= 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
 
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed >= 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
 
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
