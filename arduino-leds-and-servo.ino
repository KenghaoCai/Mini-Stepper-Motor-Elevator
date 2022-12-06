#include <Servo.h>
Servo servo;
int angle = 130;
bool doorsignal = false;
int currfloor = 1;
int targetfloor = 1;
const int elevatorUp = 13;
const int elevatorDown = 12;
int upSignal = 0;
int downSignal = 0;
const int floor1summon = 15;      //A1
const int floor2summonup = 16;    //A2
const int floor2summondown = 17;  //A3
const int floor3summon = 18;      //A4
int floor1signal, gofloor1signal = 0;
int floor2signalup, gofloor2signal = 0;
int floor2signaldown = 0;
int floor3signal, gofloor3signal = 0;
const int gofloor1 = 2;
const int gofloor2 = 3;
const int gofloor3 = 4;
const int led1 = 5;
const int led2 = 6;
const int led3 = 7;
int ADCvalue = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(8);
  servo.write(angle);
  pinMode(elevatorUp, OUTPUT);
  pinMode(elevatorDown, OUTPUT);
  pinMode(floor1summon, INPUT);
  pinMode(floor2summonup, INPUT);
  pinMode(floor2summondown, INPUT);
  pinMode(floor3summon, INPUT);
  pinMode(gofloor1, INPUT);
  pinMode(gofloor2, INPUT);
  pinMode(gofloor3, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() {
  ADCvalue = analogRead(A0);
  if (ADCvalue > 600) {
    //********* Floor level display **********
    if (currfloor == 3) {
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
    } else if (currfloor == 2) {
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led3, LOW);
    } else if (currfloor == 1) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    //************* OPEN ELEVATOR DOOR *************
    if (doorsignal == true) {  //to open
      for (angle = 130; angle > 75; angle--) {
        servo.write(angle);
        delay(30);
      }
      delay(1000);  // auto close after 1 sec
      for (angle = 75; angle < 130; angle++) {
        servo.write(angle);
        delay(30);
      }
      doorsignal = false;
    } else {
      servo.write(angle);
    }
    //************* END *************
    //********* Elevator Summon *********
    floor1signal = digitalRead(floor1summon);
    floor2signalup = digitalRead(floor2summonup);
    floor2signaldown = digitalRead(floor2summondown);
    floor3signal = digitalRead(floor3summon);
    gofloor1signal = digitalRead(gofloor1);
    gofloor2signal = digitalRead(gofloor2);
    gofloor3signal = digitalRead(gofloor3);
    delay(100);
    if (floor1signal == LOW || gofloor1signal == LOW) {
      targetfloor = 1;
    } else if (floor2signaldown == LOW || gofloor2signal == LOW) {
      targetfloor = 2;
    } else if (floor2signalup == LOW || gofloor2signal == LOW) {
      targetfloor = 2;
    } else if (floor3signal == LOW || gofloor3signal == LOW) {
      targetfloor = 3;
    }
    if (currfloor - targetfloor < 0) {
      while (targetfloor - currfloor > 0) {
        digitalWrite(elevatorUp, HIGH);
        delay(2900);
        digitalWrite(elevatorUp, LOW);
        currfloor++;
      }
      doorsignal = true;
    } else if (currfloor - targetfloor > 0) {
      while ((currfloor - targetfloor) > 0) {
        digitalWrite(elevatorDown, HIGH);
        delay(2900);
        digitalWrite(elevatorDown, LOW);
        currfloor--;
      }
      doorsignal = true;
    } else if (currfloor == targetfloor && (floor1signal == LOW || floor2signalup == LOW || floor2signaldown == LOW || floor3signal == LOW)) {
      doorsignal = true;
    } else {
      doorsignal = false;
    }
    //************* END *************
  } else {
    delay(100);
  }
}
