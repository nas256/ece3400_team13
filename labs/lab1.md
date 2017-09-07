# Lab 1

### Overview
The Goal of this lab was to become accustomed with the arduino Uno and servo motors. These are important building blocks for creating our robot as the Arduino Uno serves as the brain. 

The procedure for this lab includes the following steps:
 - Created a HeartBeat with an external LED with a 50% duty cycle
 - Reading Analog Input controlled by a potentiometer
 - Utilized PWM to control the brightness of an external LED
 - Controlled the speed of a servo motor using a potentiometer
 
After completing this procedure, we gathered parts to assemble a barebones frame that could mount the two servo motors, arduino, bread board, and power bank. This allowed us to successfully drive forward and backwards on the floor of the labratory. 


### Modifying the Blink Sketch

We first loaded the sample code "Blink", which can be found in the Arduino IDE by going to File -> Examples -> 01.Basics -> Blink.

```cpp
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
}
```
We loaded the code onto the Arduino, and we were able to get the internal LED to blink.

In order to make the external LED blink, we modified the sample "Blink" code to use a digital output pin.

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

[![Blinking External LED](https://img.youtube.com/vi/Q5QZIRb2aYM/default.jpg)](https://youtu.be/Q5QZIRb2aYM)

As you can see in our video, we added a 300 Ohm resistor in series with the LED in order to protect the output pin.

### Reading a Potentiometer

Now, we want to play with Arduino's analog input pins and print out various analog voltages reading from a potentiometer. The potentiometer we used is 3306F-103. Its datasheet link and schematic are attached here.
[DataSheet](http://www.bourns.com/data/global/pdfs/3306.pdf)

<img src="https://media.digikey.com/pdf/Catalog%20Drawings/Pots/ART-3306F%20%5EA.jpg" width="300">

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
>>>>>>> 9a693777a182a7c26098e85e66da0a2e32d4d128

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

<img src="https://i.stack.imgur.com/5IOnM.jpg" width="300">

After we were done soldering, this is what the connector looked like:

<img src="http://i.imgur.com/qj263i1.jpg" width="300">

We used red for +5V and black for GND, to easily identify the two wires.

Now all we need to do is plug in the USB connector and power the arduino!

<img src="http://i.imgur.com/6IJ7hyO.jpg" width="300">

This isn't the clearest picture, but you should be able to see that the arduino is being powered solely by the usb power bank with no connection to the computer!

### Assembling Our Robot
Do we have pics of the different components?

### Driving Autonomously
To make our robot drive in a straight line autonomously, we uploaded the following code to our board.

```cpp
// the setup function runs once when you press reset or power the board
void setup() {
    myservo2.attach(PWM2); //Attach the servo input to pin 11 (set it up as a pwm output, 20Hz)
    myservo1.attach(PWM1);
    myservo1.write(120);   //0 is full speed reverse, 90 no speed, 180 full speed ahead
    myservo2.write(120);
}
```

Here's a video of our robot going in a straight line!
[![Robot driving](https://img.youtube.com/vi/PMXfH7eCFFc/0.jpg)](https://youtu.be/PMXfH7eCFFc)



