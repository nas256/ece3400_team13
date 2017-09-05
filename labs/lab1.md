# Lab 1

### Overview
 

### Modifying the Blink Sketch

In order to make the external LED blink, we wrote the following code. 
```cpp
void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH); //Turn on LED
    delay(1000); // wait for a second
    digitalWrite(ledPin, LOW); // Turn off LED
    delay(1000); // wait for a second
}
```
Here's a video of our blinking LED in action:
[Blinking LED](https://youtu.be/Q5QZIRb2aYM)

As you can see in our video, we added a 300 Ohm resistor in series with the LED in order to protect the output pin.

### Reading a Potentiometer

Now, we want to play with Arduino's analog input pins and print out various analog voltages reading from a potentiometer. The potentiometer we used is 3306F-103. Its datasheet link and schematic are attached here.
[DataSheet](http://www.bourns.com/data/global/pdfs/3306.pdf)

![alt text](https://media.digikey.com/pdf/Catalog%20Drawings/Pots/ART-3306F%20%5EA.jpg)

By simply wiring up Potentiometer's output pin with Arduino's pin A5 (analog input), supply with GND, and input with Arduino's Vcc, we set up the circuit. After programming the code below to Arduino, we can see different voltage values printed out on the screen as we rotated the potentiometer. 

```c
int analogPin = A5;
int val;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  val = analogRead(analogPin);   // turn the LED on (HIGH is the voltage level)
  Serial.println(val);
  delay(2);
}
```
Here is a video for reading a potentiometer:
[Reading Potentiometer](https://youtu.be/aUDEQ5ryWt4)

### Analog Output

Next, we used the Arduino's pulse-width modulator (PWM) to control the brightness of an external LED. 

[![Demo of using potentiometer analog output to adjust LED brightness](http://img.youtube.com/vi/gkdc-MALRLY/default.jpg)](https://www.youtube.com/watch?v=gkdc-MALRLY)

```c
int analogPin = A0; // potentiometer output 
int LED = 11; // PWM, connected to anode of external LED int potValue; 
int brightness;

void setup() 
{ 
pinMode(analogPin, INPUT); // initialize analog pin as an input
pinMode(LED, OUTPUT); // initialize digital pin as an output 
Serial.begin(9600); 
}

void loop() { 
potValue = analogRead(analogPin); // read potentiometer output 
brightness = map(potValue,0,1023,0,255); // map potentiometer value to brightness value 
analogWrite(LED, brightness); // PWM output 
delay(2); 
} 
``` 

Using the oscilloscope, we were able to determine that the frequency of the analog output signal was 50.02Hz. We could also observe the duty cycle of our PWM output vary as we tuned our potentiometer.

[![PWM duty cycle varying with changing analog values](http://img.youtube.com/vi/FmR-_lkGAR0/default.jpg)](https://www.youtube.com/watch?v=FmR-_lkGAR0)

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

To do this, we can use Arduino's built in `map` function to convert the 0-1023 output from the ADC to 0-180 for the servo `write` method. 

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

[![Servo Spin With Potentiometer](https://img.youtube.com/vi/cf2zTpaFqKs/0.jpg)](https://www.youtube.com/watch?v=cf2zTpaFqKs)

### Soldering & Powering the Arduno from a USB Power Bank

Our robot can't be tethered to a computer forever, and since the ATMega328p has 32Kb of built in flash memory that we can store our programs on, we don't need the computer all the time anyway, all we really need is a power source.

The easiest way to power our robot is to attach a rechargeable USB power bank to the bot and draw power from it's USB port. To do this, we need to solder wires onto a USB connector to route the power back to the Arduino. For reference, here is the pinout of a standard USB A connector:

![UsbAPinout](https://i.stack.imgur.com/5IOnM.jpg)

After we were done soldering, this is what the connector looked like:

![Soldering](http://i.imgur.com/qj263i1.jpg)

We used red for +5V and black for GND, to easily identify the two wires.

Now all we need to do is plug in the USB connector and power the arduino!

![powerusb](http://i.imgur.com/6IJ7hyO.jpg)

This isn't the clearest picture, but you should be able to see that the arduino is being powered solely by the usb power bank with no connection to the computer!
