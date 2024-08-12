#include "Ultrasonic.h"

#define ULTRASONIC_SENSOR_TRIG 9
#define ULTRASONIC_SENSOR_ECHO 8               
#define MAX_REGULAR_MOTOR_SPEED 75
#define MAX_MOTOR_ADJUST_SPEED 150
#define DISTANCE_TO_CHECK 15

//Right motor
int enableRightMotor=5;
int rightMotorPin1=8;
int rightMotorPin2=9;

//Left motor
int enableLeftMotor=6;
int leftMotorPin1=10;
int leftMotorPin2=11;

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed);
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

  //If distance is within 15 cm then adjust motor direction as below
  if (distance > 0 && distance < DISTANCE_TO_CHECK)
  {
    //Stop motors
    rotateMotor(0, 0);
    delay(500);  
       
    //Reverse motors
    rotateMotor(-MAX_MOTOR_ADJUST_SPEED, -MAX_MOTOR_ADJUST_SPEED);        
    delay(200);
    
    //Stop motors
    rotateMotor(0, 0);
    delay(500);
    
    //Rotate car to left    
    rotateMotor(-MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
    delay(500);

    //Read left side distance using ultrasonic sensor
    int distanceLeft = ultrasonic.MeasureInCentimeters();

    if (distanceLeft == 50 )
    {
      rotateMotor(MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED);
      delay(200);
    }

    else {
    //Return to centre then rotate car to right
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, -MAX_REGULAR_MOTOR_SPEED);
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, -MAX_REGULAR_MOTOR_SPEED);     
    delay(500);    
    
    //Read right side distance using ultrasonic sensor   
    int distanceRight = ultrasonic.MeasureInCentimeters();
    
           
    if (distanceRight == 50 )
    {
      rotateMotor(MAX_MOTOR_ADJUST_SPEED, MAX_MOTOR_ADJUST_SPEED);
      delay(200);
    }

    rotateMotor(0, 0);    
    delay(200);     
  }
  }
  else
  {
    rotateMotor(MAX_REGULAR_MOTOR_SPEED, MAX_REGULAR_MOTOR_SPEED);
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
