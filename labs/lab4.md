# Lab 4: Radio Communication and Map Drawing
## Objective
The objective of this lab was to build off of the work we did in Lab 3 to draw a full maze on a VGA monitor while updating it in real time with information recieved from our robot. This information is transmitted through radio communication from our robot to our base station

While we had similair teams as the previous Lab, we all came together to agree on a communication protocol and worked together to combine the code. So all members gained experience with the VGA and radio communication elements.
In the end we were succesful in implementing a protocol for the robot to accurately communicate to the base station about the current state of the maze: robot's current position, unexplored, and explored areas. The protocol also currently dicatates what bits are set aside for relaying walls, presence and frequency of treasures, and a done signal. 

# Radio Team:
### Members: Norman, Divya, Wenhan

## Materials:
- 2 Nordic nRF24L01+ transceivers
- 2 Arduino Unos
- 2 USB A/B cables
- 2 radio breakout boards with headers

## Procedure

### Sending information wirelessly between Arduino’s
First, we connected the radios to the special circuit boards, and plugged a radio into each of the two Arduinos with a supply voltage of 3.3V. 
![Radio](https://imgur.com/a/O9Cy5.png)

We downloaded the [RF24 Arduino Libray](https://github.com/maniacbug/RF24) and added it to our Arduino library directory. Next, we replaced the Getting Started code in the RF24 library with the “Getting Started” sketch from the course repository. In the Getting Started example code, we changed the identifier numbers to 0x000000002CLL and  0x000000002DLL using the handout formula: 2 ( 3D + N ) + X. 

To test the radios, we connected both Arduinos to the lab computer and programmed the sketch to them. We chose one Arduino as transmitter, and typed “T” in its serial monitor. In the screenshot below, the left side serial monitor corresponds to the transmitter, and the right side serial monitor corresponds to the receiver. The signal sent by the transmitter was received by the receiver and sent back to the transmitter. The transmitter’s serial monitor also showed the round-trip delay. 
![Signal](https://imgur.com/a/IDXIk.png)

Now that the wireless communication between the two Arduino was established, we increased the distance between the two radios to see if the transmitted signal can still be received. In fact, the information transmission worked well up to around 20 feet, at which dropped packets occurred, and the communication failed at around 30 feet.
 
### Sending the entire maze

### Updating the maze array, dependent only on the updated robot information


# FPGA Team:
### Members: Nick, Eric, Julia

## Materials
- FPGA
- 1 Arduino Uno
- 1 VGA cable
- 1 VGA connector
- 1 VGA switch
- Various resistors (for voltage divider)

## Procedure
### Making our grid display the full 4x5 grid
### Receiving packets from the arduino
Using the packet format that you have agreed on with the radio team, write a module to read packets from the Arduino. Use the communication protocol you decided on in the pre-lab. To test your packet receiver, consider using the on-board LEDs and output signals onto GPIO pins and viewing them using a scope.

### Highlight the robot’s current location based on packet information
Now that you can receive packets, parse this data and use it to display the robot’s current location in the 4x5 grid.

### Marking explored territory
Finally, add additional support to display any previously-visited locations.

## Results

# Conclusion


