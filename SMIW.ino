 //Display pins might be reverse to actual display
const int A = 2, B = 3, C = 4, D = 5, E = 6, F = 7, G = 8, DP = 9, DIG1 = 10, DIG2 = 11, DIG3 = 12, DIG4 = 13;

const int trigPin1 = A1, trigPin2 = A3;
const int echoPin1 = A0, echoPin2 = A2;
const int button = A4;
double distance1, distance2, angle;
const double sensorsDistance = 10;
int mode = 0, buttonPressed=0; //0 - Show angle, 1 - show distance1, 2 - show distance2

//Calculating distance for given sonar. Returns distance in centimeters
double sonar(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return (pulseIn(echoPin, HIGH)* 0.5)/29.1;
}

void clear(){
  for(int i=2;i<9;i++) digitalWrite(i,LOW);
}
//Set of functions to display digits
void zero()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(G,LOW);
}

void one()
{
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  digitalWrite(E,LOW);
  digitalWrite(F,LOW);
  digitalWrite(G,LOW);
}

void two()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,LOW);
  digitalWrite(G,HIGH);
}

void three()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,LOW);
  digitalWrite(F,LOW);
  digitalWrite(G,HIGH);
}

void four()
{
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,LOW);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void five()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,LOW);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void six()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void seven()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);
  digitalWrite(E,LOW);
  digitalWrite(F,LOW);
  digitalWrite(G,LOW);
}

void eight()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

void nine()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);
  digitalWrite(E,LOW);
  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
}

//Functions to choose what digit light up
void digit1(){
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, HIGH);
  digitalWrite(DP,LOW);
}

void digit2(){
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, HIGH);
  digitalWrite(DIG4, LOW);
  digitalWrite(DP,HIGH);
}

void digit3(){
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, HIGH);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, LOW);
  digitalWrite(DP,LOW);
}

void digit4(){
  digitalWrite(DIG1, HIGH);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, LOW);
  digitalWrite(DP,LOW);
}

//Give this function a digit, and it will print it out at the display
void number(int digit)
{
  switch(digit % 10)
  {
    case 0:
    zero();
    break;
    
    case 1:
    one();
    break;
    
    case 2:
    two();
    break;
    
    case 3:
    three();
    break;
    
    case 4:
    four();
    break;
    
    case 5:
    five();
    break;
    
    case 6:
    six();
    break;
    
    case 7:
    seven();
    break;
    
    case 8:
    eight();
    break;
    
    case 9:
    nine();
  }
}

void display(double value)
{
  //First digit n_.__
  number((int)(value/10));
  digit4();
  delay(10);
  //Second digit _n.__
  number((int)value);
  digit3();
  delay(10);
  //Third digit __.n_
  number((int)(value*10));
  digit2();
  delay(10);
  //Fourth digit __._n
  number((int)(value*100));
  digit1();
  delay(10);
}

void setup()
{
  //Serial port begin
  Serial.begin(9600);
  //Button
  pinMode(button, INPUT);
  //Setting all sensors pins inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  //Display pins
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  pinMode(DIG3, OUTPUT);
  pinMode(DIG4, OUTPUT);
}

void loop()
{
  //Getting distance from 1st sensor
  distance1 = sonar(trigPin1, echoPin1);
  delay(75);  //This delay prevents getting sound from the other sensor. Documentation recomments at least 60ms intervals between measurements
  //Getting distance from 2nd sensor
  distance2 = sonar(trigPin2, echoPin2);

  //Calculating and displaying the angle
  distance1 = distance1>distance2 ? distance1-distance2 : distance2 - distance1; //From now distance1 is an absolute value from the difference between distances
  angle = (atan(distance1/sensorsDistance))*RAD_TO_DEG; //Calculated angle in degrees

  /*if(mode == 0) {    */ Serial.print("Angle: ");    Serial.print(angle);     //}
  /*else if(mode == 1){*/ Serial.print("Distance1: ");  Serial.print(distance1); //}
  /*else if(mode == 2){*/ Serial.print("Distance2: ");Serial.println(distance2); //}

  if(digitalRead(button) == HIGH)
  {
    while(digitalRead(button) == LOW)
    {
     mode++;
     if(mode==3) mode = 0; 
    }
  }
  
  delay(75);
}
