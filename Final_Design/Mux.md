# Mux

[Back to Final Design](https://nas256.github.io/ece3400_team13/Final_Design)

## Overview

Our robot houses 4 line sensors, 3 wall sensors, 1 microphone, and 2 IR sensors, each of which outputs an analog signal that must be read by the Arduino. Since the Arduino only breaks out 6 analog inputs, we needed to add an analog mux to select between these different inputs and increase our effective number of analog pins. 

# Hardware

We used the CD4051B analog mux to select between 8 inputs to one output. A schematic of the mux is shown below:

![Mux Schematic](https://i.imgur.com/4wrk3EY.png)

We placed two decoupling capacitors on the input of the mux to reduce noise induced by various sources around the robot. The rest of the connections are fairly simple, going to the various analog sensors on the robot and a single Arduino analog pin.

# Software

In order to interface with the CD4051B mux, we created a series of functions to easily interface with the mux. The mux has three digital control signals that select which input is forwarded to the output. We can assert these inputs as follows: 

```cpp
void amux_select(char mux_input){
  // Update each pin according to the mux_input (0-7)
  digitalWrite(AMUX\_A, mux_input & (1<<0) ? HIGH : LOW);
  digitalWrite(AMUX\_B, mux_input & (1<<1) ? HIGH : LOW);
  digitalWrite(AMUX\_C, mux_input & (1<<2) ? HIGH : LOW);
}
```

The _amux\_select_ function takes a number from 0-7 and asserts the correct signals to select that input.


## References

[CD4051B Datasheet](http://www.ti.com/lit/ds/symlink/cd4051b.pdf)
