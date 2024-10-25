#include <PS4Controller.h>

// Motor PWM Pins
const int motorFL = 32; // Front-left motor
const int motorFR = 19; // Front-right motor
const int motorBL = 14; //2 // Back-left motor
const int motorBR = 2; //14 // Back-right motor

// Direction control pins
const int dirFL = 33; // Front-left motor 
const int dirFR = 21; // Front-right motor 
const int dirBL = 12;  //4// Back-left motor 
const int dirBR = 4; //12 // Back-right motor

const int deadband = 8;

// Setting Speed and Direction
void setMotorSpeedAndDirection(int motorPin, int dirPin, int speed, int direction) {
  // Constrains to a Valid Speed
  speed = constrain(speed, 0, 255);
  
  // Sets the Direction
  digitalWrite(dirPin, direction);
  
  // Sets the Speed
  analogWrite(motorPin, speed);
}

 //  Drive Function
void mecanumDrive(int x, int y, int rotation) {
  int FL_speed = y + x + rotation;
  int FR_speed = y - x - rotation;
  int BL_speed = y - x + rotation;
  int BR_speed = y + x - rotation;
  
  // Keeps Speed within Valid Range
  int maxSpeed = max(max(abs(FL_speed), abs(FR_speed)), max(abs(BL_speed), abs(BR_speed)));
  if (maxSpeed > 255) {
    FL_speed = map(FL_speed, -maxSpeed, maxSpeed, -255, 255);
    FR_speed = map(FR_speed, -maxSpeed, maxSpeed, -255, 255);
    BL_speed = map(BL_speed, -maxSpeed, maxSpeed, -255, 255);
    BR_speed = map(BR_speed, -maxSpeed, maxSpeed, -255, 255);
  }
  
  // Sets Motor Speeds and Directions
  setMotorSpeedAndDirection(motorFL, dirFL, abs(FL_speed), FL_speed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorFR, dirFR, abs(FR_speed), FR_speed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBL, dirBL, abs(BL_speed), BL_speed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBR, dirBR, abs(BR_speed), BR_speed >= 0 ? HIGH : LOW);
}

void twoWheelDrive(int LSpeed, int RSpeed) {
  LSpeed = map(LSpeed, -127, 127, -255, 255);
  RSpeed = map(RSpeed, -127, 127, -255, 255);

  setMotorSpeedAndDirection(motorFL, dirFL, abs(LSpeed), LSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorFR, dirFR, abs(RSpeed), RSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBL, dirBL, abs(LSpeed), LSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBR, dirBR, abs(RSpeed), RSpeed >= 0 ? HIGH : LOW);
}

void tankDrive(int LStick, int RStick) {
  LStick = map(LStick, -127, 127, -255, 255);
  RStick = map(RStick, -127, 127, -255, 255);
  int leftWheelTurn = -RStick;
  int rightWheelTurn = RStick;
  int LSpeed = LStick + leftWheelTurn;
  int RSpeed = LStick + rightWheelTurn;
  if (abs(LSpeed) > 255)
    LSpeed = 255;
  if (abs(RSpeed) > 255)
    RSpeed = 255;

  setMotorSpeedAndDirection(motorFL, dirFL, abs(LSpeed), LSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorFR, dirFR, abs(RSpeed), RSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBL, dirBL, abs(LSpeed), LSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBR, dirBR, abs(RSpeed), RSpeed >= 0 ? HIGH : LOW);
}

void oneStickDrive(int X, int Y) {
  X = map(X, -127, 127, -255, 255);
  Y = map(Y, -127, 127, -255, 255);
  int leftWheelTurn = -X;
  int rightWheelTurn = X;
  int LSpeed = Y + leftWheelTurn;
  int RSpeed = Y + rightWheelTurn;
  if (abs(LSpeed) > 255)
    LSpeed = 255;
  if (abs(RSpeed) > 255)
    RSpeed = 255;

  setMotorSpeedAndDirection(motorFL, dirFL, abs(LSpeed), LSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorFR, dirFR, abs(RSpeed), RSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBL, dirBL, abs(LSpeed), LSpeed >= 0 ? HIGH : LOW);
  setMotorSpeedAndDirection(motorBR, dirBR, abs(RSpeed), RSpeed >= 0 ? HIGH : LOW);  
}

void setup() {
  PS4.begin("ac:89:95:6b:70:e4");
  Serial.begin(115200);
  // Initialize Direction Control Pins as OUTPUT
  pinMode(dirFL, OUTPUT);
  pinMode(dirFR, OUTPUT);
  pinMode(dirBL, OUTPUT);
  pinMode(dirBR, OUTPUT);
  
  // Initialize Motor Control Pins as OUTPUT
  pinMode(motorFL, OUTPUT);
  pinMode(motorFR, OUTPUT);
  pinMode(motorBL, OUTPUT);
  pinMode(motorBR, OUTPUT);
  Serial.println("Booting");
}

void loop() {

// Put Movement Directions Here 
// Example:
  //delay(1000);
  //MoveRight(255);
  int leftStick = PS4.LStickY();
  int leftStickX = PS4.LStickX();
  int rightStick = PS4.RStickY();
  int rightStickX = PS4.RStickX();
  if (abs(leftStick) < deadband)
    leftStick = 0;
  if (abs(leftStickX) < deadband)
    leftStickX = 0;
  if (abs(rightStick) < deadband)
    rightStick = 0;
  if (abs(rightStickX) < deadband)
    rightStickX = 0;

  //twoWheelDrive(leftStick, rightStick);
  //tankDrive(leftStick, rightStickX);
  //oneStickDrive(leftStickX, leftStick);
  // For mecanum drive
  leftStickX = map(leftStickX, -127, 127, -255, 255);
  leftStick = map(leftStick, -127, 127, -255, 255);
  rightStickX = map(rightStickX, -127, 127, -255, 255);
  mecanumDrive(leftStickX, leftStick, rightStickX);
  //delay(1000);
// This moves forward full speed for 1 second
  //Serial.println("Driving");
  Serial.printf("Left X: %d\n", PS4.LStickX());
  Serial.printf("Left Y: %d\n",PS4.LStickY());
  Serial.printf("Right X: %d\n",PS4.RStickX());
  Serial.printf("Right Y: %d\n",PS4.RStickY());
}

void MoveForward(int Speed) {
  mecanumDrive(0, Speed, 0);
}

void MoveBackward(int Speed) {
  mecanumDrive(0, -Speed, 0);
}

void MoveRight(int Speed) {
  mecanumDrive(-Speed, 0, 0);
}

void MoveLeft(int Speed) {
  mecanumDrive(Speed, 0, 0);
}

void RotateLeft(int Speed) {
  mecanumDrive(0, 0, -Speed);
}

void RotateRight(int Speed) {
  mecanumDrive(0,0,Speed);
}
