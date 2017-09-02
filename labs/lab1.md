# Lab 1

### Overview
 

### Modifying the Blink Sketch

TODO: Insert Video \
TODO: Insert code

### Reading a Potentiometer

TODO: Schematic \
TODO: Video

### Analog Output

We used the Arduino's pulse-width modulator (PWM) to control the brightness of an external LED. \

TODO: Video \
TODO: Code \
'''c
int analogPin = A0; // potentiometer output
int LED = 11; // PWM, connected to anode of external LED
int potValue;
int brightness;

void setup() {
  pinMode(analogPin, INPUT); // initialize analog pin as an input
  pinMode(LED, OUTPUT); // initialize digital pin as an output
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(analogPin); // read potentiometer output
  brightness = map(potValue,0,1023,0,255); // map potentiometer value to brightness value
  analogWrite(LED, brightness);   // PWM output
  delay(2);
}
'''
TODO: Oscilloscope picture

Using the oscilloscope, we were able to determine that the frequency of the signal was 50.02Hz. We could also observe the duty cycle of our PWM output vary as we tuned our potentiometer.

### Driving a Servo

TODO: Code
TODO: Video

Stops at 94 not 90

Minimum 0.5ms \
Stop at 1.5ms \
Maximum 2.4ms 

(Datasheet says 1.3, 1.5, 1.7)

### Driving a servo using Potentiometer Input

TODO: Video
