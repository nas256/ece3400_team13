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

Servo stops when servo1.write is 94 not 90
(Aka some tuning was required)

TODO: Talk about duty cycles
TODO: Oscilloscope picture
TODO: Oscilloscope video
Duty Cycles
Minimum 0.5ms \
Stop at 1.5ms \
Maximum 2.4ms 

(Datasheet says 1.3ms, 1.5ms, 1.7ms)

### Driving a servo using Potentiometer Input

Now that we've driven a servo at different speeds using code, we want to map a potentiometer's position to the speed and direction of the servo.

To do this, we can use Arduino's built in `map` function to convert the 0-1023 output from the ADC to 0-180 for the servo `spin` method. 

Like in the previous section, some setup is required first, we need to initialize the servo library to a pin and setup pin A0 as an analog input:

```cpp
Serial.begin(9600);  // initialze uart debugging console
pinMode(A0, INPUT);  // set pin A0 as an input
servo1.attach(PWM);  // Attach the servo input to pin 11
```

Now we can spin the servo based on the potiometer position:

```cpp
pot_value = analogRead(A0); // read ADC value from pin A0
Serial.println(pot_value);  // print to serial console for debugging
servo_value = map(pot_value,0,1023,0,180); // map 0-1023 to 0-180
servo1.write(servo_value);
```

Here's a video of the system working!

[![Blinky](https://lh5.googleusercontent.com/C_pe3T5O9C1DY4FqcPiNIWOkkI5p_Xs66UtymkKIpmnhcqhQx4MquhRJjDSSDNmhPrrK9mFRxGCz-w=w1920-h1080-n-k-rw)](https://drive.google.com/open?id=0BwyuAcc6KNDnLXFGeFpsc0x4enc)