// Motor PWM Pins
const int motorFL = 6; // Front-left motor
const int motorFR = 9; // Front-right motor
const int motorBL = 10; // Back-left motor
const int motorBR = 3; // Back-right motor

// Direction control pins
const int dirFL = 7; // Front-left motor 
const int dirFR = 8; // Front-right motor 
const int dirBL = 11; // Back-left motor 
const int dirBR = 2; // Back-right motor 

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

void setup() {
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
}

void loop() {

// Put Movement Directions Here 
// Example:
  MoveRight(255);
  delay(1000);
// This moves forward full speed for 1 second

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
