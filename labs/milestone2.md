# Milestone 2

## Introduction
The goal of this milestone is to add wall sensors to the robot and distinguish between 7, 12, and 17 kHz IR treasures.

## Wall Detection
We have chosen to use the short range ir sensors 	GP2Y0A41SK0F. In order to detect walls around the robot. We began by first testing our sensor, and based off of the following relationship between output voltage and distance of an obstacle listed in the [datasheet](http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a41sk_e.pdf)

<img src="https://i.imgur.com/zoSwWbM.png" width="400px" />

After testing a formula based off this graph to convert the analog voltage read by the sensor into a distance in centimeters, we performed some calibration on our sensor by placing a wooden plank a known distance from the sensor and comparing what the Arduino read versus the actual distance. We discovered there was a small offset, but since it was fairly constant over the entire sensing range, we deemed it insignificant in the long run.

In conjunction with the TAs, we found the minimum distance between an intersection and a wall, which we used as a threshold for wall detection in our code. In order to demonstrate that our robot could actually sense walls, we programmed the robot to turn right at any intersection with a wall in front of it. The video of this code in use is below: 

[![Wall Avoidance Video](https://img.youtube.com/vi/n1C5XcRkyyI/0.jpg)](https://youtu.be/n1C5XcRkyyI)

In the future, we also plan to implement left and right wall sensors to determine whether we can actually turn left or right. Unfortunately, the Arduino cannot accommodate more inputs, since the Arduino only has six analog input pins, and we already have nine input signals, including three for the wall sensors, four for the line sensors, one for the IR sensor, and one for the microphone. We will need to implement a CMOS multiplexer so that we can route various low-priority sensors to a single analog pin on the Arduino. This will allow us to follow a line, detect intersections, detect walls in front, to the left of, and to the right of our robot, detect IR beacons on both sides of our robot, and listen for a 660 Hz tone, all without any hardware changes.


## Distinguishing 7, 12, and 17 kHz IR Signals
Last week, we showed that our optical circuit could distinguish between a 7 and 12 kHz signal output from the treasure board. We did this by establishing a simple threshold check for the bins corresponding to a 7 kHz and 12 kHz signal at our sampling rate, which were bins 47 and 81 respectively. To be able to distinguish a 17 kHz signal as well, all we had to do was add another condition to our code which checked the bin corresponding to a 17 kHz signal. We expected this to be bin 14 (17,000 Hz/ 148.4 Hz/bin = 14) and confirmed by checking the FFT output on the serial monitor. The updated code and a video showing our optical circuit distinguishing a 17 kHz signal from a 7 kHz signal are shown below.

##<Insert video>
 
```cpp
/*
 adapted from OpenMusic's fft_adc_serial.pde
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x41; // use adc0 //40
  DIDR0 = 0x01; // turn off the digital input for adc0 //01
}

void loop() {
  while(1) { // reduces jitter
    
    cli();  // UDRE interrupt slows this way down on arduino1.0
    
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    
    sei();
    
    Serial.println("start"); 
    /*for (byte i = 0 ; i < FFT_N/2 ; i++) { 
      Serial.print(i);
      Serial.print(":");
      Serial.println(fft_log_out[i]); // send out the data
    } */
    delay(200); 
```
