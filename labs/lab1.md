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

TODO: Schematic \
TODO: Video

### Analog Output

We used the Arduino's pulse-width modulator (PWM) to control the brightness of an external LED. \

TODO: Video \
TODO: Code \
'''cpp
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

[![Blinky](https://lh5.googleusercontent.com/C_pe3T5O9C1DY4FqcPiNIWOkkI5p_Xs66UtymkKIpmnhcqhQx4MquhRJjDSSDNmhPrrK9mFRxGCz-w=w1920-h1080-n-k-rw)](https://drive.google.com/open?id=0BwyuAcc6KNDnLXFGeFpsc0x4enc)

### Soldering & Powering the Arduno from a USB Power Bank

Our robot can't be tethered to a computer forever, and since the ATMega328p has 32Kb of built in flash memory that we can store our programs on, we don't need the computer all the time anyway, all we really need is a power source.

The easiest way to power our robot is to attach a rechargeable USB power bank to the bot and draw power from it's USB port. To do this, we need to solder wires onto a USB connector to route the power back to the Arduino. For reference, here is the pinout of a standard USB A connector:

![UsbAPinout](https://i.stack.imgur.com/5IOnM.jpg)

After we were done soldering, this is what the connector looked like:

![Soldering](https://lh4.googleusercontent.com/sGGWRm2oLoq9DZ4ZxJu5t549kWO7cEsXd8bHokipveiLnmlrj-oygsiIK8rDA4tyza0lGA_oxxlfrA=w1533-h782-rw)

We used red for +5V and black for GND, to easily identify the two wires.

Now all we need to do is plug in the USB connector and power the arduino!

![powerusb](https://lh4.googleusercontent.com/QmfInmeFZL_uhT-dKPj5BqXLHMwY2wS8u8bP9hLG0pvUBL0yWc7M39auhiiIH1pIzNpfHjoawMAHUg=w1533-h782-rw)

This isn't the clearest picture, but you should be able to see that the arduino is being powered solely by the usb power bank with no connection to the computer!
