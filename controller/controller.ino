#define PUL 9
#define DIR 10
#define ENA 11

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
}


///

int dirBin = 0; // 0 is clockwise, 1 is counterclockwise
int pwmWidth = 300;
const int minPWMWidth = 40;
const int maxPWMWidth = 10000;

void loop() {

  updateDirection();
  genPWM();

}

// helper functions

void enableMotor(){
  digitalWrite(ENA, LOw);
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


