# Milestone 3: Algorithms
### Nicholas Sarkis, Norman Chen, Eric Cole, Julia Currie, Divya Gupta, Wenhan Xia

## In Simulation:
4 points: Working algorithm that facilitates maze exploration.
1 point: Indicator that shows the robot is done (explored everything explorable)

### Algorithm: DFS in Matlab
**talk about matlab algorithm code**

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


### Robot's Done signal

