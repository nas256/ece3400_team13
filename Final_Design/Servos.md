# Servos and Isolators

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

## Overview:
Throughout our testing, we realized that the behavior of our sensors was sometimes inconsistent, which we attributed to the servos being connected to the same voltage source as the sensors. Servos and motors have pretty substantial power requirements and can often introduce noise in other electrical components when connected to circuits. In order to alleviate this problem, we added an optoisolator between the servos and the arduino so that the voltage changes in the servos do not affect the behavior of our line and wall sensors. Once we did this, we found that we had no more problems related to line sensing and wall detection.

Aside from this issue, we are lucky that our robot's movement has been quite consistent throughout the semester, and we have never needed to significantly change our algorithms to control the servos for turning. However, we occasionally have seen small hiccups where our robot has slightly fallen short when turning left, throwing our robot off the line (a pretty big problem). We believe that this may have happened as we added components to our robot and shifted its weight without changing our turning algorithm. Our simple fix was to retune the amount of time we spend turning left, fixing the issue entirely. 

## Design

An optoisolator is a device that uses an optical transmission path to pass an electrical signal between two circuit components, rather than through direct connection by a conducting wire. This allows us to electrically isolate two circuits, while still maintaining a connection between the two circuits. This yields the following benefits when using motors in a microcontroller system such as an Arduino:

1) Isolation eliminates the heavy noise that the motor's vibration introduces to the main circuit.

2) Connection to different power supplies means that the servo does not draw power from the Arduino, which may have a limited supply.

3) A larger power supply (such as 5V) can be used to power the servos directly, which can make them faster and more powerful.

In our implementation, the optoisolator will allow us to power the servos separately using a 9 V battery. For each servo, we will connect Vdd and ground wires to this separate power supply, and the Arduino's only connection to the motors will be the PWM logic signal through the isolator circuit.

## Modifications

<img src = "https://i.imgur.com/YgDfVJ1.png">

In our design, we added the 4N35 optoisolator to both of our servo connections. In both circuits, pin 1 (input to the diode) is connected the PWM signal, and pin 2 is connected to Arduino ground. The isolator then couples the PWM signal with pin 5, which is wired to the servo's control pin. Pins 6 and 4 are Vdd and ground for the motor's battery-powered circuit, respectively. 

## Conclusions

We noticed significant improvement after introducing optoisolation to our circuit, especially in increased servo performance. It is difficult to tell how much of a role this change played in fixing our other problems in wall and line sensing, as we changed other aspects of our design at the same time (especially with introduction of the PCB). However, the increase in performance after this change was very clear.

## References

[Opto-Isolators](https://www.vishay.com/docs/81181/4n35.pdf)
