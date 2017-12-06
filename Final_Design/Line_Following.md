# Line Following

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design)

## Overview
Our line following algorithm remains the same as from milestone 1. Below is a reiterated description of that algorithm.
### Hardware
We placed two line sensors right next to each other in the forward center of the chassis and two more sensors placed about 1.5cm farther out and about 1cm in front of the two center ones. We used this arrangment so that we would be able to continue line sensing while also being able to detect upcoming intersections in the grid. This layout also makes turning easier, because we are able to lock back onto the line much faster. 

### Code
Our main strategy for line following is to scale the motor speeds based on the relative darkness of the light sensor. In order to maximize speed, we run the motors at max speed, and subtract a value from one side's motor if we need to realign on the black line.

The algorithm goes as follows:

```cpp
// Initialize slowdown variables
int slowdown_left = 0, slowdown_right = 0;

// ... below this line is looped

// Update the line sensor values
line_left_value = analogRead(P_LINE_SENSOR_1);  // 0-1023
line_right_value = analogRead(P_LINE_SENSOR_2); // 0-1023

// Line following adjustments
if ( abs(line_left_value - line_right_value) < LIGHT_TOLERANCE ){
    // drive straight
    slowdown_left = slowdown_right = 0;
}else if (line_left_value > line_right_value){
    // turn left
    slowdown_left = map(line_left_value-line_right_value, 0, BLACK_VALUE-WHITE_VALUE, 0, 20);
    slowdown_right = 0;
}else if (line_left_value < line_right_value){
    // turn right
    slowdown_left = 0;
    slowdown_right = map(line_right_value-line_left_value, 0, BLACK_VALUE-WHITE_VALUE, 0, 20);
}
```

## References

[Line Following Sensor](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/QRE1113.pdf)
