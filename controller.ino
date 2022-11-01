#define PUL 9
#define DIR 10
#define ENA 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);

  //

  Serial.println("Enable motor");
  digitalWrite(ENA, LOW);
  delay(1000);

  //

  Serial.println("Direction set");
  digitalWrite(DIR, LOW);
  delay(1000);
}

int dirBin = 0; // 0 is clockwise, 1 is counterclockwise
int pwmWidth = 300;
const int minPWMWidth = 40;
const int maxPWMWidth = 10000;

void loop() {

  // direction change if statement
  if (digitalRead(DIR) != dirBin){
    digitalWrite(DIR, dirBin);

    //

    Serial.print("Direction Change = ");
    Serial.println(dirBin);

    //

    delayMicroseconds(10);
  }

  digitalWrite(PUL, LOW);
  delayMicroseconds(pwmWidth);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(pwmWidth);

}
