#include "Servo.h"

int PWM2 = 11;
int PWM1 = 10;
//int val; 
//int y; 

Servo myservo1;
Servo myservo2; //Declare instance
  
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(PWM, OUTPUT);
  //pinMode(analogPin, INPUT);
  Serial.begin(9600);
  myservo2.attach(PWM2); //Attach the servo input to pin 11 (set it up as a pwm output, 20Hz)
  myservo1.attach(PWM1);
}

// the loop function runs over and over again forever
void loop() {

  //val = analogRead(analogPin);   // turn the LED on (HIGH is the voltage level)
  //Serial.println(val);
  //y = map(val,0,1023,0,180);
  //myservo1.write(120);
  //myservo2.write(93);
 // delay(10000);
  
  myservo1.write(120);   //0 is full speed reverse, 90 no speed, 180 full speed ahead
  myservo2.write(120);
  delay(10000);

  //myservo1.write(94);
  //myservo2.write(120);
  //delay(10000);


}
