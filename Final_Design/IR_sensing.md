## IR Sensing

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design/finaldesign_home)

In our previous implementation for sensing IR, we simply polled every 250 milliseconds to check for treasure. We chose to change our implementation leading up to the competition, as we believed this design choice was fairly computationally expensive, and we could use a more efficient design. Instead, we chose to change our design to sense IR every time our robot crosses an intersection. This was relatively easy to change, as we had already written a function to perform the IR sensing, and our already code uses a thread that runs at every intersection. But after simply calling the function inside this thread, our design was still relatively unstable. We could detect treasures that lie on straightaways, but our robot had a lot of difficulty detecting treasures when turning. 

For our final code, we modified this implementation to poll the IR sensing function only during turns, while checking for treasure at intersections when driving straight. This design still missed one or two treasures during testing, but still appeared very robust and yielded satisfactory performance for the competition.
