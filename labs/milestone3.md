### Nicholas Sarkis, Norman Chen, Eric Cole, Julia Currie, Divya Gupta, Wenhan Xia
# Milestone 3: Algorithms

## In Simulation:
4 points: Working algorithm that facilitates maze exploration.
1 point: Indicator that shows the robot is done (explored everything explorable)

### Algorithm: DFS in Matlab

[![Matlab simulation](https://img.youtube.com/vi/BW15qMcbeaY/0.jpg)](https://youtu.be/BW15qMcbeaY)

### Matlab Graphics
**talk about matlab graphics and the done indicator in simulation**

## On Maze:
4 points: Working algorithm that facilitates maze exploration.
1 point: Indicator that shows the robot is done (explored everything explorable)
You don’t have to worry about treasures/microphone circuitry yet, for either the simulation or the real-life maze exploration. You do have to include walls. We do not expect everyone to have a perfectly running system in this milestone, the goal is for everyone to start the implementation and think about (and convey on the website) what next tasks/improvements need to be done to compete in the final competition.

### Algorithm: DFS in C

**Coordinate System**

One of the major differences between our simulation and actual implementation is that the robot's orientation changes as it moves through the maze. Therefore, we must be able to translate between the robot's caridinal directions and the "true north" as seen by the DFS algorithm. In order to determine directions, we use a North, South, East, West cardinal direction system, the directions are encoded as follows:

| Direction | Encoding |
| --------- | -------- |
| North     | 0        |
| East      | 1        |
| South     | 2        |
| West      | 3        |

In order to convert between the robot's cardinal system and the "true north" cardinal system, we can use modular arithmetic using the encodings used above. If we keep track of the robot's orientation, then we can easily convert between the two systems:

```
dir_relative_to_truenorth = robot_orientation + dir_relative_to_robot (mod 4)
```

For example, if a robot see something to the West of it (3), and it is facing East (1), then the actual direction relative to true north is North (0) because 3 + 1 = 0 (mod 4). This also works in the reverse direction. We have used range checks and addition/subtraction to implement a less computationally expensive version of the mod (%) operator.

**Mapper Function**

We created a `mapper.c` file to handle all of the code that keeps track of the maze and decides which direction to turn. Each time the robot reaches an intersection, it calls the `at_intersection()` method, and passes in the current walls that it sees. `mapper.c` then stores these records internally. The method then returns which direction that the robot should turn based on a DFS algorithm, which is calculated based off the following pseudocode:

```
sense walls to the left, right, and front

add all non-blocked directions to missed_oppertunities stack

if surounded by walls || visited tiles:
  pop path stack and move along it
else
  pop off missed_oppertunities and go to target
  push new location to path stack

Find the orientation of the target relative to the robot

Update maze array
```

**Turning states**

In order to get the robot to move according to our algorithm, we need to map each direction that `at_intersection()` can return to a direction that the board should move. If the robot receives NORTH, then the robot goes into the FOLLOW_LINE state, which essentially just keeps the robot driving straight. If the robot receives SOUTH, then the robot goes into the TURN_180 state, which rotates the wheels opposite to each other in order to turn the robot 180 degrees. If the robot receives WEST, then the robot will turn left, and EAST will cause the robot to turn right. Here's a video of our robot moving according to our DFS algorithm.

[![DFS Trial](https://img.youtube.com/vi/KyGrfLteqN8/0.jpg)](https://youtu.be/KyGrfLteqN8)


### Robot's Done signal
Our done signal is just lighting up three LEDs on our robot. This involves first adding a signal which `at_intersection()` can return to tell the robot that it is indeed done. We added a new state called DONE, which causes the robot to stop its wheels and light up the LEDs. Here's a video of our robot completing a DFS!

**TODO: video of final dfs**


## Conclusion 
By the end of this milestone we were able to simulate DFS maze exploration and fully implement DFS on our robot and signal when the maze is fully traversed. Looking ahead, we need still need to support the ending tone once the robot is done exploring and  treasure identificatoin in our robot's implementation. We are also working on the layout for a PCB which should make our electronics more compact and reliable. 
