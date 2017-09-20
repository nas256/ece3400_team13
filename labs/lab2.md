# Lab 2: Analog Circuitry and FFTs

## Overview
The goal of this singal-processing lab was to become familiar with the Open Music Lab FFT Library, analog filters, and op-amps. These three items were needed to implement both the IR sensors and the microphone circuitry. The microphone will be used for hearing the 660Hz starting signal in competition, while the use of the IR sensor is essential to finding and catagorizing the 'treasures' throughout the maze. 
In order to accomplish this lab in the time given, we split up into two teams: the Acoustics Team and the Optical Team. The acoustics team was comprised of Norman Chen, Wenhan Xia, Eric Cole, and they were responsible for the pre-lab and the microphone circuitry. The optical team was comprised of Nick Sarkis, Divya Gupta, Julia Currie, and they were responsible for implementing the IR circuitry and merging of the code between groups. 

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

Objective: Be able to detect a 7, 12, 17kHz IR beacon with an Arduino using the FFT library.

Materials:
- Arduino Uno
- IR receiver (phototransistor) ([datasheet](http://optoelectronics.liteon.com/upload/download/DS-50-93-0013/LTR-301.pdf))
- Treasure board 
- Resistors: 300, 1.8k, 5k, 16k, 100k
- 0.01 uF capacitor
- Operational amplifier ([datasheet](http://www.ti.com/lit/ds/symlink/lm358.pdf))

#### Building a Basic Sensor using a Phototransistor 
  We started by building a basic sensor using a phototransistor in our circuit as shown below. As the phototransistor receives more light, it lets more current pass and the voltage drop across the resistor is larger. Therefore, the output voltage increases as a result.
  
 <img src = "https://i.imgur.com/Pv4VCBv.png" width = "300">
 
  
##### Adding a High Pass Filter 
  
  Since we only wanted our sensor to detect light in the IR spectrum, we had to design a high pass filter to remove lower frequency signals. The lowest frequency signal we wanted to detect was 7kHz, and so we set a cutoff frequency of roughly 1kHz which be high enough to filter out the fluorescent light in the room (roughly 120Hz). Using this cutoff frequency, we chose resistor and capacitor values of 10kΩ and 0.01uF, respectively, and built a simple RC high pass filter into our circuit as shown below.
  
  f<sub>c</sub> = 1/(2πRC)

#### Preparing the Treasure 
  
  Our second step was to set up the treasure board. We powered the board with a 3.3V coin cell battery and turned on the power switch. In order to get our treasure board to flash at the desired frequency of either 7kHz or 12kHz (depending on the position of the switch), we had to measure the frequency output of the sensor on an oscilloscope and tune the according potentiometer until it reached the right value. 
  
![Treasure board](https://cei-lab.github.io/ece3400/images/Treasure_Pot.JPG)
  
#### Adding an Amplifier 

   We could see from our treasure board frequency measurements that the sensing circuit was working; it was only passing a signal when the treasure board was near it and not when light from our phones or from the fluorescent lights overhead shone on it. However, the amplitude of the sensor output was small and we had to hold our treasure board very close to the sensor in order to detect the signal. Therefore, we decided to build an amplifying circuit so that we could detect the board from a realistic distance that it would be in the maze. 

To build our amplifying circuit, we used the LM358 dual operational amplifier chip. Our circuit is as follows:

![IR Amplifier Circuit](https://i.imgur.com/bbulIQy.png)

Our circuit consists of 3 main stages: an input stage, a high pass filter stage, and an amplifying stage.
 - The input stage consists of a photostransistor that conducts current relative to the amount of IR light it is receiving. As it conducts more current, more current passes through the resistor creating a voltage that we can measure.
 - The high pass filter stage has a cutoff frequency of about 1kHz so that only AC signals pass through. This is to remove the DC offset caused by ambient light that would intefere with our amplification. It also blocks out the 60-120Hz oscillations due to many types of electric lighting. 
 - Finally, the gain stage allows us to read IR signals from farther distances. Empirically, we've found that 20x gain gives us about 4-5 inches of range. Should we find that our range is too small, we can always increase our circuit's gain by choosing a smaller resistance value for R3

### Arduino & FFT (include data from serial monitor)

In order to distinuguish between different treasure frequencies, we need to perform a Fourier Transform on the input received from our sensing circuit. A common method that many digital systems use to compute this transform is called a FFT, or "Fast Fourier Transform," which is an algorithm that approximates the frequency components of a signal into "bins" of a discrete size, allowing the system to distinguish different frequencies. 

A sample FFT output is shown below:

![FFT](https://i.imgur.com/HgkH4CI.png)

Conclusion

## Conclusion
Merged code

Wrapping up and next steps
