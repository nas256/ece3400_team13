### Nicholas Sarkis, Norman Chen, Eric Cole, Julia Currie, Divya Gupta, Wenhan Xia
# Milestone 4: Putting it All Together

##Introduction
The main goal of milestone 4 was to integrate all the previous labs and milestones into one seamless system. For this milestone, we were tasked with demonstrating that our robot can sucessfully communicate with the basestation and have it display walls and treasures as the robot finds them, and signal "done" on both the screen and the speakers when the robot has finished a maze. With the completion of this milestone, our robot and basestation will essentially be competition ready, and the rest of our time in lab will be spent making performance optimizations on the robot.

## FPGA Graphics
### Walls
### Treasure
[![17kHz Sensing](https://img.youtube.com/vi/EHfJIytHCts/0.jpg)](https://youtu.be/EHfJIytHCts)


### Done Signal
A “done” signal was implemented to indicate that the maze searching was completed. According to our encoding in lab4, the last bit of the 16-bit input signal to the FPGA is set if the robot reaches the end of the maze. In our code, a register play_sound takes the input signal “DATA_IN” ‘s last bit value. Once the play_sound register is set, the three-frequency tune implemented in lab 3 is played, and a green bar is drawn on the screen to signal that the process is complete.

```cpp
// Draw the done signal if done
if (PIXEL_X >= 10'd550 && PIXEL_X <= 10'd600) begin
 if (play_sound) COLOR_OUT = 8’b000_11_000;
 end
end 

// Audio integration
AUDIO audio(
 .CLOCK_50(CLK),
 .ENABLE( play_sound ),
 .GPIO_1_D( GPIO_1_D ),
);
```

## Radio Communication
### Robot
### Basestation
The basestation code remains relatively unchanged from lab 4. 

We first need to initialize the maze with the correct x and y values. Because we output the entire maze to the fpga, we need to make sure that every tile is correctly initialized such that the fpga does not overdraw a tile. 
```cpp
  // Initialize maze
  for (int i = 0; i < X_SIZE; i++) {
    for (int j = 0; j < Y_SIZE; j++) {
      maze[i][j] = 0;
      maze[i][j] |= ((i&3) << 14) | ((j&7) << 11);
      Serial.println(maze[i][j]);
    }
  }
```
Now that the maze is initialized, we can now wait to receive some data from the robot. 
```cpp
 while (timeout)
  {
    // Wait until we get data or timeout
    timeout = wireless_read( &got_data, sizeof(uint16_t) );
  } 
```
Once the above loop either gets some data or times out, we just transfer over SPI the entire maze updated with the new data we received. 
```cpp
if (got_data & 0x1) done = 1;

// First, stop listening so we can talk over SPI
radio.stopListening();

SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); //10MHz

unsigned char got_x = got_data >> 14;
unsigned char got_y = (got_data >> 11) & 7;
maze[got_x][got_y] = got_data;
for (uint16_t x = 0; x < X_SIZE; x++){
    for (uint16_t y = 0; y < Y_SIZE; y++){
        if (maze[x][y] == 0) continue;
        if ((x != got_x) || (y != got_y))  
            // Clear the current? bit
            maze[x][y] = maze[x][y] & 0xfffd;
        else
            // Set the current? bit    
            maze[x][y] = maze[x][y]  | 1 << 1;
        digitalWrite(7, LOW);
        delay(1);
        SPI.transfer16(maze[x][y] | done);
        digitalWrite(7, HIGH);
    }
}
```

Here's a video of the robot completing a simple maze with radio communication! 

[![Demo without treasure](https://img.youtube.com/vi/AXLjUVhm9pc/0.jpg)](https://youtu.be/AXLjUVhm9pc)


## Conclusion
This milestone was particularly challenging considering the combined code size of all our labs, and debugging was much more complicated since we were dealing with a much larger codebase than before. In the end, we were able to integrate all the labs and milestones throughout the semetester into one seamlessly working system. The next steps for us as a team is to continue to optimize both the design of the robot and the software in our system. In addition, we still need to integrate the microphone into the full system, as well as replacing our breadboard with the pcb we ordered. Here's a video that demonstrates our robot traversing a simple maze and displaying walls, treasures, and a done signal.

[![All Put Together](https://img.youtube.com/vi/tG9IEcegNAo/0.jpg)](https://youtu.be/tG9IEcegNAo)