# Addition of a Printed Control Board

## Motivations

As we continue to add components and parts, our robot gets more and more bulky, and becomes very prone to wires coming loose or other random sources of failure. This has become more difficult to bug check. Because much of our basic design is completed after the labs and milestones, we will address these difficulties by incorporating a printed circuit board (PCB) into our design. A PCB is an insulator panel onto which conductive wires are laminated, allowing connection of different devices without the burden associated with using a breadboard and wires. 

Designing a PCB will allow us to translate our current design into a much more compact format, with a lot of benefits:

1) Our robot's structure will be a lot smaller and simpler. We will not need to worry about wires coming loose while working, and adding or removing components for future modifications will become much easier when our design is much less bulky.

2) Our robot will become lighter, increasing speed and efficiency during the competition. 

3) A PCB will make our robot more effective by reducing circuit noise.

4) Our final robot design will look much cleaner.


## Design

### Overview

Our PCB is the center of the robot, to which everything on our robot connects. We wanted to make it easy for ourselves to plug/unplug the various parts of our robot, so we have allocated spaces on the PCB for both right angle and vertical pin header connections. We have also had problems with noise due to paristics of stray wires, breadboards, bad connections, and many other unforseeable unidealities. The PCB itself should reduce noise significantly, but we determined that the servos were injecting a lot of noise onto our common ground. We therefore decided to optically isolate the motor circuitry from the arduino and sensor circutry, creating two separate power and grounds.

### Design Requirements

The board performs the following functions:
 - Serve as an arduino shield for easy mounting
 - House an analog mux to increase the number of available ADC channels
 - Filter and amplify 2 incoming infrared signals from 7-17 kHz
 - House a nRF24L01+ module
 - Provide connectors for:
   - 3 infrared wall sensors
   - 4 line sensors
   - 2 servos
- House a microphone
- Optically isolate 2 servos controlled by Arduino PWM pins

### Schematic

![PCB Schematic](https://i.imgur.com/AxAlWwW.png)

### Layout

![PCB Layout](https://i.imgur.com/3JtoCCO.png)

### End Product

![End Product](https://i.imgur.com/vxlOEil.png)

## Implementation

Once we recieved the board, we began immediately soldering all of the components to the board. The process went rather smoothly, until we noticed that whoever sent out the PCBs forgot to draw our power and ground planes on the top and bottom of the board! This made the implementation significantly more difficult, as we had to rework almost every power and ground together, which took a number of hours to complete. Once completed however, the stability granted by this new design is very desirable. The design works as intended, after the aforementioned modifications.

## Testing

We used an incremental population and testing strategy when populating the PCB. We first populated all of the power-related circuitry, and checked that each power and ground was correctly connected, and that the proper voltages were reaching all of the proper places. We then implemented each feature of the board separately. We started by connecting the analog mux, line sensors, and wall sensors. This worked quite well after changing a few #define's in our code to match the new pinouts. After these features were verified, we then moved on to the optisolator circuit. After populating the optoisolator ciruitry, we passed a PWM signal from the arduino to the servo output, and observed a clean and undistorted output signal. We went along like this, verifying all of the features on the PCB until we were confident in its design and then mounted it to the robot and resumed our testing and tuning.

## Conclusions

We feel that adding a PCB was a great idea. It forced us to solidify our design earlier on, implementing and testing designs earlier than we would have otherwise. The overall stability of our robot has also been greatly increased, with almost no random problems popping up due to a loose wire or a bad connection. We are happy with the design and hope it remains stable for the competition!