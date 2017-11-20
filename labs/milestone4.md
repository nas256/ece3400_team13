### Nicholas Sarkis, Norman Chen, Eric Cole, Julia Currie, Divya Gupta, Wenhan Xia
# Milestone 4: Putting it All Together

##Introduction
The main goal of milestone 4 was to integrate all the previous labs and milestones into one seamless system. For this milestone, we were tasked with demonstrating that our robot can sucessfully communicate with the basestation and have it display walls and treasures as the robot finds them, and signal "done" on both the screen and the speakers when the robot has finished a maze. With the completion of this milestone, our robot and basestation will essentially be competition ready, and the rest of our time in lab will be spent making performance optimizations on the robot.

## FPGA Graphics
### Walls
### Treasure

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
Here's a video of the robot completing a simple maze! 
[![Demo without treasure](https://img.youtube.com/vi/AXLjUVhm9pc/0.jpg)](https://youtu.be/AXLjUVhm9pc)


## Conclusion
