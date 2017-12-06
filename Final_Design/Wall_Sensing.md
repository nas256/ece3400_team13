# Wall Sensing

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

## Overview

There are many ways to go about sensing walls. The most stable and straightfoward way to do this is to use some sort of distance sensors. There are a lot of different types of distance sensors, ultrasonic, infrared, etc. We chose the infrared sensors because of their relatively simple interface (analog voltage output) and their in-lab availability. The sensors that we used did not have a linear voltage to distance relationship, but rather an exponential one. We therefore empirically measured voltage outputs of the sensor when the robot saw a wall and when it did not, and used a threshold-based system to detect the walls. This proved very stable and reliable.

## Modifications

Throughout most of the most of the semester we simply connected the wall sensors either directly to the Arduino or to the analog mux and used a digital filter to filter out noise. We then decided to add hardware filters as well, to help avoid false positive or false negative wall detections. 

**WE ADDED LOW PASS FILTERING ON INPUT OF THEM** --> do we rememebr the values?

The only modifications we made to wall sensing since milestone 4 is adding low pass filters to their signal paths before they go into the analog Mux.

<img src = "https://i.imgur.com/xlyItyB.png" width = "50%">

## References

[Short Range IR Sensors](http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a41sk_e.pdf)


