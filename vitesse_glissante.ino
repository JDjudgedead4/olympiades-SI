#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

Servo myservo;
float mySensVals[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float somme;
float moyenne;
float vitesse;
int GT1 = 20;
int GT2 = 19;
float distance1 = 0;
float distance2 = 0;
float deltadistance = 0;

void setup() {
  myservo.attach(4);  
  myLidarLite.begin(0,true);
  myLidarLite.configure(0);
  Serial.begin(115200);
}

void loop() {
  distance1 = (myLidarLite.distance());
  if (distance1 > 10) {  
  deltadistance = distance1 - distance2;
  if (deltadistance < 0) {
    deltadistance = 1;
  }
  delay(100); 
  distance2 = distance1;
  
  for (int i = 0; i <= 20; i++) {
    GT1 = GT1 - i;
    GT2 = GT2 - i;
    mySensVals[GT1] = mySensVals[GT2];
  }

  mySensVals[0] = deltadistance;
  for (int i = 0; i <= 20; i++) {
   somme =mySensVals[i] + somme;
  }
  moyenne = somme / 10;
  vitesse = moyenne *3.6;
  Serial.println(vitesse);
  
  } 
}
