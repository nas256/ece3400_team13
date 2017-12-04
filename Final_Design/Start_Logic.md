# Starting Logic

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

## Overview

For the competition, we were tasked with waiting till a 660kHZ sound was played in order to start traversing the maze. We were also allowed to use a button instead, but it would result in a 2pt reduction. We had the microphone working successfully, however we decided to cut our loses and stick with the button on the robot to perserve time and increase reliability.

## Microphone

The microphone inputs the signal to our system. In order to filter out the high frequency noise and keep the 660 Hz signal, the signal from the microphone should first be filtered with a lowpass or bandpass filter. After the filter, an amplifying circuit is needed to amplify the signal before it is sent to the Arduino. Since the microphone we were given already had a highpass filter and amplifiers built inside, we just implemented an extra circuit outside to further amplify the signal received by the Arduino. We tried multiple different circuits including both non-inverting amplifier and inverting amplifier, but we were not able to get any obvious further gain. We also tried many resistors with different values, but still failed to see a clear gain even though the large resistors such as 1 kΩ gave a cleaner signal. 

We had a spot for the microphone on the PCB, however we soon found out that we needed to further amplify the signal and we felt as if spending the extra time implementing the extra circuitry on the robot was worth tthe 2 point reduction in competition.

**ADD PICS**

## Start Button

The start button was a simple switch that shorted its two contacts together when pressed. We connected the button between a arduino digital pin and ground. We used the arduino's internal pull up resistors to keep the pin HIGH, unless it was pressed in which case it was pulled low. In our code we simply waited for this signal to break out of a while() loop to begin our DFS code.

```cpp
pinMode(INPUT_PULLUP, P_START_BUTTON);
digitalWrite(P_START_BUTTON, HIGH);
````

**ADD PICTURE**


