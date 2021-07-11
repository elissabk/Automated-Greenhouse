/*
 Copyright 2019 Elissa Bou Karam 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <SimpleDHT.h> //temperature sensor library

//constant values to be used later in the program
#define DRY 0
#define MOIST 400
#define WET 650
#define DARK 200
#define HOT 24
#define ANGLE 80
#define ALERT 60

//constant values used to assign number of digital pins
#define valve2 26
#define valve3 29
#define valve4 30
#define valve5 31
#define valve6 27
#define valve7 28
#define RED 9
#define GREEN 10
#define BLUE 11
#define buzzer 12
#define flame_sensor 13
#define trigPin 22
#define echoPin 23
#define pinDHT11 24
#define fan 8

//variables used to assign number analog pins
int pumpt = A7;
const int ldrPin = A0;

//variables to be used to store and calculate values
int flame_detected;
long duration;
int distance;

//defining the temperature sensor pin
SimpleDHT11 dht11(pinDHT11);

//defining void functions to be used
void water();
void sunlight();
void flame();
void intruder();
void heat();

//setup code to initialize the system
void setup() {
  Serial.begin(9600); //must be the same for all sensors

  //setting the mode of the digital pins (input or output)
  pinMode(ldrPin, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinDHT11, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(valve2,OUTPUT);
  pinMode(valve3,OUTPUT);
  pinMode(valve4,OUTPUT);
  pinMode(valve5,OUTPUT);
  pinMode(valve6,OUTPUT);
  pinMode(valve7,OUTPUT);
  pinMode(pumpt,OUTPUT);

  //initializing the signal of all devices connected to relays (HIGH is off, LOW is on)
  digitalWrite(buzzer,LOW);
  digitalWrite(valve2,HIGH);
  digitalWrite(valve3,HIGH);
  digitalWrite(valve4,HIGH);
  digitalWrite(valve5,HIGH);
  digitalWrite(valve6,HIGH);
  digitalWrite(valve7,HIGH);
  digitalWrite(fan,HIGH);
  digitalWrite(RED,HIGH);
  digitalWrite(GREEN,HIGH);
  digitalWrite(BLUE,HIGH);
}

//main code to be run repeatedly
void loop() {
  //calling all functions
  water();
  sunlight();
  flame();
  intruder();
  heat();

  //1.5s of delay between each loop
  delay(1500);
}

//function used to check soil moisture level and control the watering mechanism
void water(){
  //defining the soil moisture sensor analog pin numbers and mode of operation (Read, Write...)
  int sensorValue2 = analogRead(A8);
  int sensorValue3 = analogRead(A9);
  int sensorValue4 = analogRead(A10);
  int sensorValue5 = analogRead(A11);
  int sensorValue6 = analogRead(A12);
  int sensorValue7 = analogRead(A13);

  //setting the signal of the pump for it to be turned off (255 in analog is similar to HIGH in digital)
  analogWrite(pumpt, 255);
  
  /*Serial.print("plant 1: ");
  Serial.println(sensorValue2);
  Serial.print("plant 2: ");
  Serial.println(sensorValue3);
  Serial.print("plant 3: ");
  Serial.println(sensorValue4);
  Serial.print("plant 4: ");
  Serial.println(sensorValue5);
  Serial.print("plant 5: ");
  Serial.println(sensorValue6);
  Serial.print("plant 6: ");
  Serial.println(sensorValue7);*/

  //testing the soil moisture level and acting upon that reading
  if (sensorValue2>=DRY && sensorValue2<MOIST){ //waters the plants
    //Serial.println(sensorValue2);
    //Serial.println("Soil for plant 1 is dry.");
    analogWrite(pumpt,0); //sends a 0 signal to the relays to turn on the pump, similar to LOW in digital
    digitalWrite(valve2,LOW);
    Serial.print("Plant 1 is being watered.\n");
    delay(1000);
    analogWrite(pumpt,255); //pump should be turned off before valve to prevent errors in the pipes
    delay(100);
    digitalWrite(valve2,HIGH);
    Serial.println("Water for plant 1 is turned off.");
  }
  else if(sensorValue2>=MOIST && sensorValue2<WET){ //no water is supplied to the plants
    //Serial.println(sensorValue2);
    //Serial.println("Soil for plant 1 moist.");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve2,HIGH);
    //Serial.println("Water for plant 1 is off");
  }
  else if(sensorValue2>=WET){ //no water is supplied to the plants
    //Serial.println(sensorValue2);
    //Serial.println("Soil for plant 1 wet");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve2,HIGH);
  } //these conditions are applied to all 6 soil moisture sensors and valves
  
  if (sensorValue3>=DRY && sensorValue3<MOIST){
    //Serial.println(sensorValue3);
    Serial.println("Soil for plant 2 dry");
    analogWrite(pumpt,0);
    digitalWrite(valve3,LOW);
    Serial.println("Plant 2 is being watered");
    delay(1000);
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve3,HIGH);
    Serial.println("Water for plant 2 is turned off");
  }
  else if(sensorValue3>=MOIST && sensorValue3<WET){
    //Serial.println(sensorValue3);
    //Serial.println("Soil for plant 2 moist");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve3,HIGH);
  }
  else if(sensorValue3>=WET){
    //Serial.println(sensorValue3);
    //Serial.println("Soil for plant 2 wet");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve3,HIGH);
  }

  if (sensorValue4>=DRY && sensorValue4<MOIST){
    //Serial.println(sensorValue4);
    Serial.println("Soil for plant 3 dry");
    analogWrite(pumpt,0);
    digitalWrite(valve4,LOW);
    Serial.println("Plant 3 is being watered");
    delay(1000);
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve4,HIGH);
    Serial.println("Water for plant 3 is turned off");
  }
  else if(sensorValue4>=MOIST && sensorValue4<WET){
    //Serial.println(sensorValue4);
    //Serial.println("Soil for plant 3 moist");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve4,HIGH);
  }
  else if(sensorValue4>=WET){
    //Serial.println(sensorValue4);
    //Serial.println("Soil for plant 3 wet");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve4,HIGH);
  }

  if (sensorValue5>=DRY && sensorValue5<MOIST){
    //Serial.println(sensorValue5);
    Serial.println("Soil for plant 4 dry");
    analogWrite(pumpt,0);
    digitalWrite(valve5,LOW);
    Serial.println("Plant 4 is being watered");
    delay(1000);
    analogWrite(pumpt,255);   
    delay(100);
    digitalWrite(valve5,HIGH);
    Serial.println("Water for plant 4 is turned off");
  }
  else if(sensorValue5>=MOIST && sensorValue5<WET){
    //Serial.println(sensorValue5);
    //Serial.println("Soil for plant 4 moist");
    analogWrite(pumpt,255);   
    delay(100);
    digitalWrite(valve5,HIGH);
  }
  else if(sensorValue5>=WET){
    //Serial.println(sensorValue5);
    //Serial.println("Soil for plant 4 wet");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve5,HIGH);
  }

  if (sensorValue6>=DRY && sensorValue6<MOIST){
    //Serial.print("soil 5:");
    //Serial.println(sensorValue6);
    Serial.println("Soil for plant 5 dry");
    analogWrite(pumpt,0);
    digitalWrite(valve6,LOW);
    Serial.println("Plant 5 is being watered");
    delay(1000);
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve6,HIGH);
    Serial.println("Water for plant 5 is turned off");
  }
  else if(sensorValue6>=MOIST && sensorValue6<WET){
    //Serial.print("soil 5:");
    //Serial.println(sensorValue6);
    //Serial.println("Soil for plant 5 moist");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve6,HIGH);
  }
  else if(sensorValue6>=WET){
    //Serial.print("soil 5:");
    //Serial.println(sensorValue6);
    //Serial.println("Soil for plant 5 wet");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve6,HIGH);
  }

  if (sensorValue7>=DRY && sensorValue7<MOIST){
    //Serial.println(sensorValue7);
    Serial.println("Soil for plant 6 dry");
    analogWrite(pumpt,0);
    digitalWrite(valve7,LOW);
    Serial.println("Plant 6 is being watered");
    delay(1000);
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve7,HIGH);
    Serial.println("Water for plant 6 is turned off");
  }
  else if(sensorValue7>=MOIST && sensorValue7<WET){
    //Serial.println(sensorValue7);
    //Serial.println("Soil for plant 6 moist");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve7,HIGH);
  }
  else if(sensorValue7>=WET){
    //Serial.println(sensorValue7);
    //Serial.println("Soil for plant 6 wet");
    analogWrite(pumpt,255);
    delay(100);
    digitalWrite(valve7,HIGH);
  }
}

//function to detect sunlight and control lighting conditions
void sunlight(){
  int ldrStatus = analogRead(ldrPin);
  //Serial.println(ldrStatus);
  if (ldrStatus >= DARK) {
    //Serial.println(ldrStatus);
    Serial.print("It’s DARK, LED turned on. \n");
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,LOW);
  } else {
    //Serial.println(ldrStatus);
    Serial.print("Its BRIGHT, LED turned off. \n");
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,HIGH);
  }
}

//function to detect fire and turn on alarm system
void flame(){
  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 0)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    digitalWrite(RED, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    digitalWrite(RED, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    digitalWrite(RED, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    digitalWrite(RED, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    digitalWrite(RED, LOW);
    delay(200);
  }
  else
  {
    //Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, LOW);
    //digitalWrite(LED, LOW);
  }
}

//function to detect the presence of any intruder and turn on alarm
void intruder(){
  //clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  //sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  //calculating the distance
  distance = duration*0.034/2;
  
  /*// Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);*/
  if(distance<ALERT){
    Serial.print("Warning! Intruder!");
    digitalWrite(buzzer,HIGH);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,HIGH);
    digitalWrite(RED,LOW);
    delay(200);
  }
  else{
    digitalWrite(buzzer,LOW);
  }
}

//function to measure temperature and control fan
void heat(){
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) { //detects reading error
    //Serial.print("Read DHT11 failed, err=");
    //Serial.println(err);
    delay(1000);
    return;
  }
  
  //Serial.print("Temperature: ");
  //Serial.print((int)temperature);
  //Serial.print(" *C \n"); 
  //Serial.print((int)humidity); Serial.println(" H");
  
  //tests temperature value and turns on/off fan
  if((int)temperature>=HOT){
    digitalWrite(fan,LOW);
    /*Serial.print("Temperature: ");
    Serial.print((int)temperature);*/
    Serial.print(" *C \n"); 
    Serial.print("Fan is on.\n");
  }
  else{
    digitalWrite(fan,HIGH);
    //Serial.print("Fan is off.\n");
  }
}
