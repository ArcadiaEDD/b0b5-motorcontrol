#include <Servo.h>

// motor macros
#define PUL 5 // red
#define DIR 4 // white
int dirBin = 1; // 0 is clockwise, 1 is counterclockwise
int pwmWidth = 8000;
const int minPWMWidth = 40;
const int maxPWMWidth = 10000;

// microswitch macro
#define MCROSWC 7

// piston macros
#define PSTA 2
#define PSTB 3

// servo macros
#define SERVOPIN 6
Servo srv;
//int srvPos = 0;

///

void setup() {
  Serial.begin(9600);

  //

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);

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

  extendPiston();
  
  //

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
const int aimingTiming[] = {145, 80, 260, 100, 225};
const int aimingDirection[] = {1, 1, 0, 1, 1}; // 1 is to right, 0 is left
int aimingIndex = 0;
int aimingTimingCount = 0;

void loop() {

  Serial.println("waiting for press");
  if (getSwitchPressed()){
    Serial.println("fire");
    awaitBall();
    delay(2000);
    fireBall();
  }
  delay(100);

  /*if (!hasFinishedRunning){
    if (loopOrderIndex == 0){
      if (aimingIndex >= goalCount){
        hasFinishedRunning = true;
      }
      else{
        //awaitBall();
        Serial.println("Delay");
        delay(2000);
        loopOrderIndex++;
      }
    }
    else if (loopOrderIndex == 1){
      aimingIteration();
    }
    else if (loopOrderIndex == 2){
      awaitBall();
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
  }*/

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
  retractPiston();
  delay(100);
  while (!getSwitchPressed()){
    Serial.print("awaiting ball for goal #");
    //Serial.println(aimingIndex+1);
    delay(1);
  }

  lockServo();
}

void fireBall(){
  unlockServo();

  retractPiston();
  delay(10);

  extendPiston();
  delay(1000);
  retractPiston();
  delay(1000);
}

// motor controller helper functions

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
  updateServoPos(145);
  delay(500);
}

void unlockServo(){
  //Serial.println("Stop");
  updateServoPos(180);
  delay(500);
}

void updateServoPos(int p){
  srv.write(p);
}

// switch helper functions

int getSwitchPressed(){
  return digitalRead(MCROSWC);
}

// pneumatic helper functions

void resetPiston(){
  digitalWrite(PSTA, LOW);
  digitalWrite(PSTB, LOW);
}

void retractPiston(){
  digitalWrite(PSTA, HIGH);
  digitalWrite(PSTB, LOW);
}

void extendPiston(){
  digitalWrite(PSTA, LOW);
  digitalWrite(PSTB, HIGH);
}

