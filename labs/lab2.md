# Lab 2: Analog Circuitry and FFTs

## Overview

## FFT & Arduino
Explanation of basic FFT algorithm 

Open Music Labs Arduino FFT library 

Example sketch test using signal generator 

Compare ADC to AnalogRead 

## Pre-Lab: Amplifying and Filtering Design

## Acoustic Team: Assembling the Microphone Circuit

Members: 

Objective: 

Materials: (link to datasheets) 
- Arduino Uno 
- Electret microphone 
- 1 µF capacitor  
- 300 Ω resistors 
- ~3 kΩ resistor 
- 

## Optical Team: Assembling the IR Circuit

Members: Nick, Julia, Divya

Objective: Be able to detect a 7kHz IR beacon with an Arduino using the FFT library.

Materials: (link to datasheets)
- Arduino Uno
- IR receiver (phototransistor) ([datasheet](http://optoelectronics.liteon.com/upload/download/DS-50-93-0013/LTR-301.pdf))
- Treasure board 
- 300Ω resistors, 16kΩ resistor
- 0.01 uF capacitor
- Operational amplifier ([datasheet](http://www.ti.com/lit/ds/symlink/lm358.pdf))

#### Building a Basic Sensor using a Phototransistor 
  We started by building a basic sensor using a phototransistor in our circuit as shown below. As the phototransistor receives more light, it lets more current pass and the voltage drop across the resistor is larger. Therefore, the output voltage increases as a result.
  
  TODO: insert image
  
##### Adding a High Pass Filter 
  
  Since we only wanted our sensor to detect light in the IR spectrum, we had to design a high pass filter to remove lower frequency signals. The lowest frequency signal we wanted to detect was 7kHz, and so we set a cutoff frequency of roughly 1kHz which be high enough to filter out the fluorescent light in the room (roughly 120Hz). Using this cutoff frequency, we chose resistor and capacitor values of 10kΩ and 0.01uF, respectively, and built a simple RC high pass filter into our circuit as shown below.
  
  f<sub>c</sub> = 1/(2πRC)
  
  TODO: insert image

#### Preparing the Treasure 
  ![Treasure board](https://cei-lab.github.io/ece3400/images/Treasure_Pot.JPG)
  
  Our second step was to set up the treasure board. We powered the board with a 3.3V coin cell battery and turned on the power switch. In order to get our treasure board to flash at the desired frequency of either 7kHz or 12kHz (depending on the position of the switch), we had to measure the frequency output of the sensor on an oscilloscope and tune the according potentiometer until it reached the right value. 
  
#### Adding an Amplifier 

   We could see from our treasure board frequency measurements that the sensing circuit was working; it was only passing a signal when the treasure board was near it and not when light from our phones or from the fluorescent lights overhead shone on it. However, the amplitude of the sensor output was small and we had to hold our treasure board very close to the sensor in order to detect the signal. Therefore, we decided to build an amplifying circuit so that we could detect the board from a realistic distance that it would be in the maze. 

To build our amplifying circuit, we used the LM358 dual operational amplifier chip. Our circuit is as follows:

![IR Amplifier Circuit](https://i.imgur.com/bbulIQy.png)

Our circuit consists of 3 main stages: an input stage, a high pass filter stage, and an amplifying stage.
 - The input stage consists of a photostransistor that conducts current relative to the amount of IR light it is receiving. As it conducts more current, more current passes through the resistor creating a voltage that we can measure.
 - The high pass filter stage has a cutoff frequency of about 1kHz so that only AC signals pass through. This is to remove the DC offset caused by ambient light that would intefere with our amplification. It also blocks out the 60-120Hz oscillations due to many types of electric lighting. 
 - Finally, the gain stage allows us to read IR signals from farther distances. Empirically, we've found that 20x gain gives us about 4-5 inches of range. Should we find that our range is too small, we can always increase our circuit's gain by choosing a smaller resistance value for R3

Arduino & FFT (include data from serial monitor) \
Distinguishing 7kHz, 12kHz treasures
- include code 

Conclusion

## Conclusion
Merged code

Wrapping up and next steps