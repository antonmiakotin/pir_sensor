/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified 2 Sep 2016
  by Arturo Guadalupi
*/

int sensorPin = 5;
int sensor2Pin = 2;
int volatile state = LOW;
int currentState = LOW;
int ledPin = 4;
int fadeStep = 15;
int sleep = 30;
boolean inTransition = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(sensorPin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor2Pin), handleInterrupt, CHANGE);
  currentState = state = readState();
  digitalWrite(ledPin, currentState);

  Serial.println("Setup done");
}

void handleInterrupt() {
  if(!inTransition){
    state = readState(); 
    Serial.println("Change interrupt: " + state);

  }else {
    Serial.println("Interrupt in transition");
  }
}

int readState(){
  return digitalRead(sensorPin) || digitalRead(sensor2Pin);
}

void loop() {
//  Serial.println("Starting loop");
  
  if (currentState == LOW && state == HIGH) {
    Serial.println("Motion start!");
    inTransition = true;
    fadeUp();
    Serial.println("Fade up end");
  } else if (currentState == HIGH && state == LOW) {
    inTransition = true;
    Serial.println("Motion end");
    fadeDown();
    Serial.println("Fade down end");
  }
  inTransition = false;
  currentState = state;
  state = readState();

//  Serial.println("Ending loop");
}

void fadeUp() {
  digitalWrite(ledPin, LOW);
  for (int i = 0; i < 1024; i += fadeStep) {
    analogWrite(ledPin, i);
    delay(sleep);
    delay(0);
  }
  analogWrite(ledPin, 1023);
  Serial.println("Full power");
}

void fadeDown() {
  digitalWrite(ledPin, HIGH);
  for(int i = 1023; i >= 0; i -= fadeStep) {
    analogWrite(ledPin, i);
    delay(sleep);
    delay(0);
  }
  analogWrite(ledPin, 0);

  Serial.println("Turned off");
}


