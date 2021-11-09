//Constants
#define NUM_JOY 2
#define MIN_VAL 0
#define MAX_VAL 1023
#include "Keyboard.h"

//Parameters
const int joyPin [2] = {A0, A1};
const int joyBtn  = 2;
const int joyOffset  = 0;

const int buttonPin = 7;
const int buttonPin_2 = 6;
const int ledPin = 8;
int buttonState = 0;
int buttonState_2 = 0;

//Variables
int joyVal [NUM_JOY] = {0, 0};

void setup() {
  //Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  //Init Joystick
  for (int i = 0; i < NUM_JOY; i++) pinMode(joyPin[i], INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin_2, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  firing_control();
  //Serial.println("eh");
  readJoystick();
  Serial.println("bulpup scheme uploaded");
  //delay(100);
}
void firing_control(){
  buttonState = digitalRead(buttonPin);
  buttonState_2 = digitalRead(buttonPin_2);
  if (buttonState == HIGH) {
      digitalWrite(ledPin, HIGH);
      //Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_RIGHT_CTRL);
      
      Keyboard.releaseAll();
      Serial.print("Firing da Missile\n");
      delay(100);
  }
  if (buttonState_2 == HIGH) {
      digitalWrite(ledPin, HIGH);
      //Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('c');
      Keyboard.releaseAll();
      Serial.print("Axis reset\n");
  }
  digitalWrite(ledPin, LOW);
}
void readJoystick( ) {
  int convY = 0;
  int convX = 0;
  for (int i = 0; i < NUM_JOY; i++) {
    joyVal[i] = analogRead(joyPin[i]);
  }
  for (int i = 0; i < NUM_JOY; i++) {
    //Serial.print(F("Conv")), Serial.print(i); Serial.print(F(" : ")); Serial.println(joyRawToPhys(joyVal[i]));
    convY = joyRawToPhys(joyVal[0]);
    convX = joyRawToPhys(joyVal[1]);
    //Serial.println(convY);
    //Serial.println(convX);   
  }
  if(convX >5){
      //Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.releaseAll();
      Serial.println('s');
  }
  if(convX <-5){
      //Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.releaseAll();
      Serial.println('z');
  }
  //Serial.println(convX);
  else if ((convX >= -5) && (convX <= -1) && (convX <= 5) && (convX >= 1)){
      Keyboard.press('c');
      Keyboard.releaseAll();
      Serial.println("axis reset");
  }
  //Serial.println(convX);
  if(convY >5){
      //Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
      Serial.println('q');
  }
  if(convY <-5){
      //Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.releaseAll();
      Serial.println('d');
  }
}

int joyRawToPhys(int raw) { /* function joyRawToPhys */
  float phys = map(raw, MIN_VAL, MAX_VAL, -100 + joyOffset, 100 + joyOffset) - joyOffset; //
  return phys;
}
