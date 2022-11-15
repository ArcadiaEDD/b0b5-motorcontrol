#include <Servo.h>

// motor macros
#define PUL 9
#define DIR 10
#define ENA 11
int dirBin = 0; // 0 is clockwise, 1 is counterclockwise
int pwmWidth = 300;
const int minPWMWidth = 40;
const int maxPWMWidth = 10000;

// microswitch macro
#define MCROSWC 2

// piston macros
#define PSTA 4
#define PSTB 5

// servo macros
#define SERVOPIN 6
Servo srv;
int srvPos = 0;

///

void setup() {
  Serial.begin(9600);

  //

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);

  //

  Serial.println("Enable motor");
  digitalWrite(ENA, LOW);
  delay(200);

  //

  Serial.println("Direction set");
  digitalWrite(DIR, LOW);
  delay(200);

  //

  Serial.println("Attach servo");
  srv.attach(SERVOPIN);

  unlockServo();
}


///
// 150 vs 40
void loop() {

  /*updateDirection();
  genPWM();*/


  delay(500);
}

// motor controller helper functions

void enableMotor(){
  digitalWrite(ENA, LOW);
  delay(200);
}

void disableMotor(){
  digitalWrite(ENA, HIGH);
  delay(200);
}

void updateSpeed(int pwmW){
  if (pwmW >= minPWMWidth && pwmW <= maxPWMWidth){
    pwmWidth = pwmW;
  }
}

void updateDirection(){
  // direction change
  if (digitalRead(DIR) != dirBin){
    digitalWrite(DIR, dirBin);

    //

    Serial.print("Direction Change = ");
    Serial.println(dirBin);

    //

    delayMicroseconds(10);
  }
}

void genPWM(){
  // PWM
  digitalWrite(PUL, LOW);
  delayMicroseconds(pwmWidth);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(pwmWidth);
}

// servo helper function

void lockServo(){ // holds servo up against the ball, CW
   turnServoCW();
   delay(1000);
   stopServo();
}

void unlockServo(){ // gets out of the way of the ball, CCW
  turnServoCCW();
  delay(1000);
  stopServo();
}

void turnServoCW(){
  updateServoPos(150);
}

void turnServoCCW(){
  updateServoPos(40);
}

void stopServo(){
  updateServoPos(80);
}

void updateServoPos(int p){
  srv.write(p);
}


