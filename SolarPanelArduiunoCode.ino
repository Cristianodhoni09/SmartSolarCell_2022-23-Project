#define ldrTr A4 
#define ldrTl A1
#define ldrBl A2
#define ldrBr A3
#define pot A0 //ENCODER (POTENTIOMETER)
#define m1 5    //vertical 
#define m2 6    //vertical
#define m3 9    //horizontal
#define m4 10    //horizontal

int topAverage, bottomAverage, leftAverage, rightAverage, encoderValue;

const int ldrLimit = 50;
const int encoderMin = 100;
const int encoderMax = 750;
const int motorSpeed = 80;

void setup(){
  Serial.begin(9600);  
  pinMode(ldrTl, INPUT);
  pinMode(ldrTr, INPUT);
  pinMode(ldrBl, INPUT);
  pinMode(ldrBr, INPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(pot, INPUT);
}

void loop(){
  ReadSensors();
  Serial.print(topAverage);
  Serial.print(" ");
  Serial.print(bottomAverage);
  Serial.print(" ");
  Serial.print(leftAverage);
  Serial.print(" ");
  Serial.print(rightAverage);
  Serial.println(" ");

  if (abs(topAverage - bottomAverage) > ldrLimit){
    if (topAverage > bottomAverage && encoderValue < encoderMax){
      analogWrite(m3, 0);
      analogWrite(m4, motorSpeed);
    } else if (topAverage < bottomAverage && encoderValue > encoderMin){
      analogWrite(m3, motorSpeed);
      analogWrite(m4, 0);
    } else {
      analogWrite(m3, 0);
      analogWrite(m4, 0);
    }
  } 
  
  if (abs(rightAverage - leftAverage) > ldrLimit){
    if (leftAverage > rightAverage){
      analogWrite(m1, motorSpeed / 2);
      analogWrite(m2, 0);
    } else if (leftAverage < rightAverage){
      analogWrite(m1, 0);
      analogWrite(m2, motorSpeed / 2);
    } else {
      analogWrite(m1, 0);
      analogWrite(m2, 0);
    }
  } 
  delay(100);
}

void ReadSensors(){
  int bottomRight = analogRead(ldrBr);
  int topRight = analogRead(ldrTr);
  int topLeft = analogRead(ldrTl);
  int bottomLeft = analogRead(ldrBl);
  encoderValue = analogRead(pot);
  
  topRight = map(topRight, 550, 775, 100, 900);
  topLeft = map(topLeft, 65, 260, 100, 900);
  bottomLeft = map(bottomLeft, 200, 470, 100, 900);
  bottomRight = map(bottomRight, 50, 300, 100, 900);

  encoderValue = map(encoderValue, 0, 1023, 0, 1023); // If potentiometer range is not 0-1023

  topAverage = (topLeft + topRight) / 2;
  bottomAverage = (bottomLeft + bottomRight) / 2;
  leftAverage = (topLeft + bottomLeft) / 2;
  rightAverage = (topRight + bottomRight) / 2;
}
