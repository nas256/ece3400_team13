# IR Sensing

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

## Overview

The competition required us to identify IR treasures along the maze that transmits at 7kHz, 12kHz, and 17kHz. We used a photo transistor, whose output was passed through a LM358 op-amp to achieve a 200x gain. The output signal was then fed into our analog mux. The arduino processed this data by finding the analog input's FFT spectrum. In order to do so, we need to change the ADC to free running mode in order to sample fast enough for the FFT. Once we collect this we look at the magnitude of a specific index which corresponds to one of the three frequencies. If there are above a specific threashold then we return from the function, saying that we have dedected a treasure. We also must change the ADC back into single acquistion mode, in order to not break all future AnalogRead() calls. 

<img src = "https://i.imgur.com/oGP2ja8.png" width = "50%">


## Modifications

The modifications that we made regarding IR include: increasing the gain of the op amp, remounting them on the robot to accomodate where they would be placed on the maze, and the IR polling code. 

In our previous implementation for sensing IR, we simply polled every 250 milliseconds to check for treasure. We chose to change our implementation leading up to the competition, as we believed this design choice was fairly computationally expensive, and we could use a more efficient design. Instead, we chose to change our design to sense IR every time our robot crosses an intersection. This was relatively easy to change, as we had already written a function to perform the IR sensing, and our code already uses a thread that runs at every intersection. But after simply calling the function inside this thread, our design was still relatively unstable. We could detect treasures that lie on straightaways, but our robot had a lot of difficulty detecting treasures when turning. 

For our final code, we modified this implementation to poll for treasure at intersections when driving straight. We then wait for the IR polling logic to finish before transmitting the details of that tile. This design still missed one or two treasures during testing, but still appeared very robust and yielded satisfactory performance for the competition. We were successful with identifying all 3 frequencies of treasure.


## References

[LM358 Datasheet](http://www.ti.com/lit/ds/symlink/lm158-n.pdf)

[IR Reciever Datasheet](http://optoelectronics.liteon.com/upload/download/DS-50-93-0013/LTR-301.pdf)
