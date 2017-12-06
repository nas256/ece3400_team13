# RF Communication

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

## Overview

In order to communicate between the base station and the robot, we utilized the nRF24L01+ 2.4 GHz transceiver. We used a packet size of 16 bits, with a single tile encoded in each of these packets. We only send packets to update tiles that change, to save us trasmitting time, as cpu time on the robot is no commodity. We use the same protocol as we do over SPI:

|15-14     |13-11     |10-9        |8-7    | 6-3      | 2         | 1            | 0         |
| -------- | -------- | ---------- | ----  |  ------- | --------- | ------------ | --------- |
| X coord  | Y coord  | Treasure   |  00   | Walls    | Traversed? | Current Loc? | Finished? |


## Modifications

The base code that was supplied by the course uses the slowest data rate and lowest power rating. We thought we could save some time by increasing the data rate and the transmit power. We do this with the following code:

```cpp
// Transmit at a higher level
radio.setPALevel(RF24_PA_HIGH);
// RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
radio.setDataRate(RF24_250KBPS);
```
