# Servos and Isolators

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

## Overview:
Throughout our testing, we realized that the behavior of our sensors was sometimes inconsistent, which we attributed to the servos being connected to the same voltage source as the sensors. In order to alleviate this problem, we added an optoisolator between the servos and the arduino so that the voltage changes in the servos do not affect the behavior of our line and wall sensors. Once we did this, we found that we had no more problems related to line sensing and wall detection.

## Modifications

## References