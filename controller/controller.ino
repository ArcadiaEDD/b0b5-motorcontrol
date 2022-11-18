#include <Servo.h>

// motor macros
#define PUL 9
#define DIR 10
#define ENA 11
int dirBin = 1; // 0 is clockwise, 1 is counterclockwise
int pwmWidth = 2000;
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

  //

  pinMode(MCROSWC, INPUT);

  //

  pinMode(PSTA, OUTPUT);
  pinMode(PSTB, OUTPUT);

  resetPiston();
}


///
  /*dirBin = getSwitchPressed();
  updateDirection();*/
   /*if (dirBin){
    turnServoCW();
  }
  else{
    turnServoCCW();
  }

  delay(500);*/

  /*if (dirBin){
    /*extendPiston();
    Serial.println("pressed");
    delay(2000);
    retractPiston();
    lockServo();
  }

  Serial.println("it");

  delay(100);*/

bool hasFinishedRunning = false;
int loopOrderIndex = 0; // 0 is await ball, 1 is for aiming, 2 is for fire ball

const int goalCount = 5;
const int aimingTiming[] = {0, 100, 300, 200, 300};
const int aimingDirection[] = {0, 1, 0, 1, 1}; // 1 is to right, 0 is left
int aimingIndex = 0;
int aimingTimingCount = 0;

void loop() {

  if (!hasFinishedRunning){
    if (loopOrderIndex == 0){
      if (aimingIndex >= goalCount){
        hasFinishedRunning = true;
      }
      else{
        awaitBall();
        loopOrderIndex++;
      }
    }
    else if (loopOrderIndex == 1){
      aimingIteration();
    }
    else if (loopOrderIndex == 2){
      fireBall();
      loopOrderIndex++;
    }
    else{ // reset order
      loopOrderIndex = 0;
    }
  }
  else{
    Serial.println("Finished Running");
    delay(1000);
  }

}

void aimingIteration(){
  if (aimingIndex < goalCount){
    if (aimingTimingCount < aimingTiming[aimingIndex]){

      dirBin = aimingDirection[aimingIndex];
      updateDirection();
      genPWM();

      aimingTimingCount++;

    }
    else{
      aimingIndex++;
      aimingTimingCount = 0;
      loopOrderIndex++;
    }
  }
  else{
    hasFinishedRunning = true;
  }
}

void awaitBall(){
  while (!getSwitchPressed()){
    Serial.print("awaiting ball for goal #");
    Serial.println(aimingIndex+1);
    delay(1);
  }

  lockServo();
  delay(1000);
}

void fireBall(){
  delay(2000);
  unlockServo();

  resetPiston();
  delay(10);

  extendPiston();
  delay(1000);
  retractPiston();
  delay(1000);
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
   delay(355);
   stopServo();
}

void unlockServo(){ // gets out of the way of the ball, CCW
  turnServoCCW();
  delay(1000);
  stopServo();
}

void turnServoCW(){
  //Serial.println("CW");
  updateServoPos(150);
}

void turnServoCCW(){
  //Serial.println("CCW");
  updateServoPos(40);
}

void stopServo(){
  //Serial.println("Stop");
  updateServoPos(80);
}

void updateServoPos(int p){
  srv.write(p);
}

// switch helper functions

int getSwitchPressed(){
  return 1-digitalRead(MCROSWC);
}

// pneumatic helper functions

void resetPiston(){
  digitalWrite(PSTA, LOW);
  digitalWrite(PSTB, LOW);
}

void retractPiston(){
  digitalWrite(PSTA, LOW);
  digitalWrite(PSTB, HIGH);
}

void extendPiston(){
  digitalWrite(PSTA, HIGH);
  digitalWrite(PSTB, LOW);
}

