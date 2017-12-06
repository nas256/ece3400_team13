# Depth First Search Algorithm

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design)

## Overview

Our final robot design uses the depth-first search algorithm described in Milestone 3 for maze exploration. Most of the DFS code stayed the same from Milestone 3, however we fixed a bug that we discovered as we tested our robot on different mazes. We give an overview of how our robot uses DFS and explain the modifications made in our final design below.

### Robot DFS

Depth-first search (DFS) is an algorithm used for graph traversal that starts at a root node and explores as far as possible in one direction before backtracking and exploring other nodes. A Matlab simulation demonstrating DFS maze exploration which we wrote before implementing the algorithm on our robot is shown below.

[![Matlab DFS Video](https://img.youtube.com/vi/3pxyapwlsh0/0.jpg)](https://www.youtube.com/watch?v=3pxyapwlsh0)

## Modifications

### DFS Bug

As we were testing our robot on different mazes, we found a bug in our initial DFS algorithm. A video of the maze that exposed the bug is shown below, although the video of the robot is taken after we resolved the bug.

[![DFS Edge case](https://img.youtube.com/vi/ITbs1UXNAfc/0.jpg)](https://youtu.be/ITbs1UXNAfc)

When the robot got to tile (2,1), the robot had walls to its left and right, and it had already added the tile in front of it to the missed_op stack, so it would not add it again. Considering our DFS pseudocode included below, we want the robot to consider this condition as it being surrounded and therefore backtrack by popping the path stack and moving along it. However, in our initial implementation of DFS, we only considered ourselves surrounded if we had walls or visited tiles on all sides and did not consider tiles on the missed_op stack. Therefore, the robot tried to go to the tile popped off of the missed_op stack, which in this case was tile (1,1), and it crashed into the wall.

Old pseudocode:
```
sense walls to the left, right, and front

add all non-blocked directions to missed_oppertunities stack

if surounded by walls || visited tiles: // should also include tile previously added to missed_op stack
  pop path stack and move along it
else
  pop off missed_oppertunities and go to target
  push new location to path stack

Find the orientation of the target relative to the robot

Update maze array
```

### Fixing the Bug

To fix the bug, we modified our function at_intersection so that it counted this situation where there was a neighboring tile that had already been added to the missed_op stack and was not the next tile to be popped from the stack as equivalent to a wall or visited tile. In order to implement this, we added a none_added flag to indicate that no tile had been pushed onto the missed_op stack at that intersection. It was set high to start whenever the function at_intersection was called and low if a missed opportunity was added. We also added three conditions (front_is_missed, left_is_missed, right_is_missed) to indicate whether the neighboring tile was at the head of the missed_op stack, as shown in the code below.

```cpp
xy_pair recent_missed_op = s_peek(&missed_op);
uint8_t front_is_missed = ( front.x == recent_missed_op.x && front.y == recent_missed_op.y );
uint8_t left_is_missed = ( left.x == recent_missed_op.x && left.y == recent_missed_op.y );
uint8_t right_is_missed = ( right.x == recent_missed_op.x && right.y == recent_missed_op.y );

uint8_t none_added = 1;

if ( !wall_left  && !s_contains(&visited, left) && !s_contains(&missed_op, left) ){
  Serial.println("Add left");
  s_push( &missed_op, left );
  none_added = 0;
}

if ( !wall_right && !s_contains(&visited, right) && !s_contains(&missed_op, right) ){
  Serial.println("Add right");
  s_push( &missed_op, right );
  none_added =0 ;
}

if ( !wall_front && !s_contains(&visited, front) && !s_contains(&missed_op, front) ){
  Serial.println("Add front");
  s_push( &missed_op, front);
  none_added = 0;
}
```

To see whether we were surrounded, we first check that the none_added flag is high because if there a tile added to the missed_op stack then we are not really surrounded. Additionally, there either needs to be a wall, visited tile, or tile that had been added to the missed_op stack but is not at the head of the missed_op stack, in the left, right, and front directions. The revised code is shown below.

```cpp
xy_pair target;
// Check if we're surrounded by walls or visited or missed_op
if ( none_added && ((wall_front || !front_is_missed) && (wall_left || !left_is_missed) && (wall_right || !right_is_missed)) ){
    if (s_isEmpty(&missed_op)) return 255;
  target = s_pop(&path);
  Serial.print("P S: ");
  Serial.println(path.top+1);
}else{
  // Not surrounded
  if (s_isEmpty(&missed_op)) return 255;
  target = s_pop(&missed_op);
  s_push(&visited, target);
  Serial.print("M S: ");
  Serial.println(missed_op.top+1);
  s_push(&path, pos);
}
```

## References
[More on DFS](https://cei-lab.github.io/ece3400/lectures/171023-Algorithms_DFS_BFS.pdf)
