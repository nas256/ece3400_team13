# Lab 3

### Overview

The goal of this lab was to become familiar with using the DE0-Nano Development Board and complete two tasks that will help towards the design of our final system. During competition, our base station Arduino will transmit all maze information recorded by our robot to an FPGA, which will then draw a map of the maze on a VGA monitor. The FPGA will also generate a sound when the maze-mapping is finished.

In order to accomplish this lab in the time given, we split up into two teams: the Graphics Team and the Acoustic Team. The graphics team worked towards the first task, which was to take at least two external inputs of the FPGA and display them on a VGA monitor. This team was comprised of Nick Sarkis, Eric Cole, and Julia Currie. The acoustics team worked towards the second task, which was to output a short tune of at least three frequencies to a speaker via an 8-bit DAC after prompted by an external input to the FPGA. This team was comprised of Norman Chen, Wenhan Xia, and Divya Gupta.

### Graphics Team
# Members: Eric, Nick, Julia

## Objectives: 
Our goal was to begin building a fully-functional base station for our robot, with displaying a simplified version of the final maze grid. To accomplish this, we needed to display graphics on a VGA monitor using a FPGA. We had to write our own VGA controller and SPI protocol in order for the Arduino Uno to control the state of the grid displayed on the VGA monitor. While implementing this, we familiarized ourselves with the DE0-Nano FPGA board, SPI protocol, and how to interact with video memory and a VGA driver.
- Understand example code and building upon it → should i include block diagram or should we make our own???
- Design and code a memory system to draw blocks in a grid
- Create a communication method between the Arduino and FPGA

## Materials:
- FPGA DE0_nano development board
- Arduino Uno Board
- ? Ohm Resistors for voltage divider
- Bread Board
- VGA Connector
- VGA Cable
- VGA Monitor
- VGA Switch

## Procedure:
# VGA Setup
The VGA display has an internal resistance of 50 Ohms,therefore the VGA connector has the following resistor values...were chosen because…
Because the VGA cable that connects the FPGA to the monitor only has 1 wire for each color (red, green, and blue), which has only transmit values from 0 to 1 V. We need to convert our FPGA 3.3V digital output, which represents the color in 8 bits, to 1V analog signals for each color. The VGA connector takes care of this conversion for us with the Digital-to-Analog-Converter (DAC). 
[double check and get part numbers]

# FPGA Side:
Verilog Code:
VGA driver
SPI protocol
How we stored Color and Location

# Arduino Side:
Arduino Code:
SPI protocol
How we sent information to create the dance party

# Maze Representation: (how we plan to further implement this)
“You will need to represent both the full maze (4 by 5 squares) and walls, empty spaces, unexplored spaces, a robot, and treasures within it. Be sure to include a description of your plan on your team website.”

# Rubric: -->(temporary)
1 point: Reading external inputs to FPGA
1 point: Correctly updating a 4-bit array dependent on the inputs
1 point: Drawing one box on the screen
1 point: Description of how the DAC on the provided VGA connectors works and how the resistor values were chosen.
4 points: Mapping external inputs to four different outputs on the screen

## Resources:
Gif of dance party: https://media.giphy.com/media/3ohhwlafpV8BoABa24/giphy.gif
Video of hardware and screen: https://youtu.be/fSFf5c4tUkI

### Acoustic Team
Members: Divya, Wenhan, Norman

Objectives: Our ultimate goal was to play a short tune of at least three frequencies our our speakers when a switch on the FPGA is turned on. We broke this down into the following sequence of smaller steps:
Prepare the stereo phone jack socket in order to connect FPGA output to the speaker
Output a square wave to the speaker
Output a triangle and sawtooth wave to the speaker via an 8-bit DAC
Output a sine wave to the speaker
Output a tune of at least three different frequencies to the speaker

Materials:
FPGA DE0_nano development board
8-bit R2R DAC (datasheet:http://www.bourns.com/docs/Product-Datasheets/R2R.pdf)
Lab speakers
Stereo phone jack socket
Male to female jumper wires
Soldering the stereo phone jack socket

The stereo phone jack socket has three terminals. Both exterior pins are inputs and the center pin is ground. To prepare the socket to be integrated into our circuit so that we could connect the FPGA output to the speakers, we soldered the two socket input pins together and to a red wire. We also soldered a black wire to the ground pin of the socket.

PIC OF SOLDERED 3.5MM JACK

**Outputting a square wave to the speaker**
In this section, we generated a simple square wave with frequency 700 Hz and output it to a GPIO pin. The implementation idea is simple: for half of the signal’s period, the output is 1, for another half of the period, the output is toggled to 0. A parameter CLKDIVIDER_700 is set to the total number of clock cycles in half of the square wave’s period, 1/700/2. Since the system clock’s frequency is 25MHz, one period requires 25000000/700 cycles; thus CLKDIVDER_700 is set to 25000000/700/2 to represent half of a period. A counter was used to count down the clock cycles in half of a period. If the counter reaches 0, the counter is reset and the square wave’s value is toggled. Otherwise, the counter keeps counting down and the register “wave” retains the old value.

The code is attached below.

```verilog
parameter CLKDIVIDER_700 = 25000000/700/2;    // 700 Hz frequency

	//square wave parameters
	reg square;                       
	assign GPIO_0_D[0] = square;
	reg [15:0] counter;

	// Sound state machine
	always @ (posedge CLOCK_25) begin
	  if (counter == 0) begin
            // reset counter and toggle square every CLKDIVIDER_700 cycle
		 counter <= CLKDIVIDER_700 - 1; 	
	 	 square <= ~square;      
	  end
	  else begin
		 counter <= counter - 1;  //count down
		 square <= square;
        end
      end
```
With the above implementation, we were able to see a correct square wave with frequency of 700 Hz on the oscilloscope.

<img src="https://i.imgur.com/eV2XOb5.jpg" width="300">  

 After we had verified the square waveform on the oscilloscope, we connected this GPIO pin to the red wire tied to the input of the stereo phone jack socket and connected one of the FPGA ground pins to the black wire tied to the ground pin of the socket. We plugged the speaker jack into the socket and were able to hear the sound of the 700 Hz square wave.

[![Square Wave](https://img.youtube.com/vi/vv4YD9C_X_A/0.jpg)](https://youtu.be/vv4YD9C_X_A)  


**Setting up the DAC**

We wanted to use Verilog and the FPGA to generate a tune that included at least three different frequencies. Before we did this, we had to set up the 8-bit DAC to take in the digital signal from the FPGA and convert it to an analog signal for the 3.5mm auxiliary output. Our digital signal is outputted through GPIO_1 pins 7 to 0, which requires us to connect each of these pins to an input on the 8 bit DAC.

<img src="https://imgur.com/fBWRC3c.jpg" width="300">  

In the picture above, you can see eight wires connecting each of the output pins to a input on the DAC, with the output connected to positive end of the scope probe.

**Outputting a triangle wave**

In order to test this connection, we added a simple triangle wave to the Verilog module provided in the lab writeup.
```verilog
reg [7:0] triangle;
reg [7:0] counter;
reg flag;
assign GPIO_1_D[7:0] = triangle;
// Sound state machine
always @ (posedge CLOCK_25) begin
    if (counter == 0) begin
        counter  <= CLKDIVIDER_700 - 1; // reset clock
        flag <= ~flag;
    end
    else begin
        counter    <= counter - 1;
        if (flag) begin
            triangle <= triangle + 1;
        end
	  else begin
            triangle <= triangle - 1;
        end
    end
end
```

With this code, we were able to get a clean triangle wave on the scope display.

<img src="https://imgur.com/6DjoHtC.jpg" width="300">

Once we had verified the correct triangle wave on the oscilloscope, we connected the output (pin 16) of the DAC to the input of the stereo phone jack socket (one of the exterior pins) and again connected one of the FPGA ground pins to the ground pin of the socket (setup shown below). We plugged the speaker jack into the socket and were able to hear the sound of the triangle wave.

INSERT TRIANGLE PIC

INSERT TRIANGLE VIDEO


**Outputting a simple sine wave**

With the triangle wave working, we knew that our DAC circuit was correct and that we could move on to generating a sine wave. To do this, we had to first implement a sine table ROM within our Verilog module. We first created a Matlab script which would generate the sine table and print it out in Verilog syntax.

```matlab
sine_table = zeros(1024, 'int8');
fileID = fopen('sine_table.txt','w');
for k = 0:1024
    % cast to int8 for an 8-bit DAC.
    fprintf(fileID, 'sin_table[%d] = %d;\r\n', k,   
            int8(sin(k*2*pi/1024)*5000/128+40));
end
```

Using this script, we could take the output and copy it into our Verilog module.

```verilog
//Initialize the sine rom with samples.
initial begin
    sin_table[0] = 40;
    sin_table[1] = 40;
    sin_table[2] = 40;
    sin_table[3] = 41;
    …
    sin_table[1023] = 40;
end
```

Now that we had this sine table, it was relatively simple for us to generate the sine wave. We wanted to generate a XX Hz sine wave, and so we had to increment the index of the 1024-entry sine table by one every 74 clock cycles. This is implemented with the following code. Note that we use a switch on the FPGA so that it outputs the sine wave when in the “ON” position and outputs nothing when “OFF”. This is the external input to the FPGA (during competition, this indicates that maze-mapping is complete!) that will prompt it to generate a sound.

```verilog
always@ (posedge(CLOCK_50)) begin
    if (~SW[3]) begin
freq <= freq + 1; // freq acts as a counter
// Changing the value from 74 will change the tone frequency 	
if (freq == 74) begin
           freq <= 0;
           data_out <= sin_table[i];
           i <= i+ 1;
           if(i == 1023) begin
               i <= 0;
           end
        end
end
```

To listen to what the sine wave sounded like, we again connected the output of the DAC to the stereo phone jack socket and plugged in the speakers. We could hear the sine wave at a constant frequency of XX Hz.

[![single sine wave](https://img.youtube.com/vi/WbqZ9BlY6jg/0.jpg)](https://youtu.be/WbqZ9BlY6jg)


**Outputting 3 different frequencies**

With the simple sine wave working, we could move on to generating the three tones. We decided to have a repeating sequence of three tones, with the second tone lower in frequency than the first and the third lower than the second, and to have each tone last a duration of one second. We wrote our Verilog code such that it would walk through this sine table at different frequencies.

```verilog
always@ (posedge(CLOCK_50)) begin
    if (~SW[3]) begin
        if (tone_counter == 0) begin
            if (tone_duration < ONE_SEC) begin
                tone_duration <= tone_duration + 1;
                freq1 <= freq1 + 1;
	            // Changing freq1 will change the
	            // frequency of the tone
                if (freq1 == 74) begin
                    freq1 <= 0;
                    data_out <= sin_table[i];
                    i <= i+ 1;
                    if(i == 1023) begin
                        i <= 0;
                    end
                 end
             end
             else begin
                 tone_duration <= 0;
                 tone_counter <= tone_counter + 1;
              end
         end
```

The code above shows how we walked through the sine table. We alter the frequency by adjusting how many clock cycles the code waits before it reads each index of the sine table ROM. We keep track of which tone (one, two, or three) is being played with the reg “tone_counter” and how long it has played with the reg “tone_duration”. We repeat the code snippet two more times in order to generate the three tones.

To listen to the sound of the three-frequency tune, we again connected the output of the DAC to the stereo phone jack socket and plugged in the speakers. We could hear our simple tune playing on the speakers!

[![three tone sine wave](https://img.youtube.com/vi/EllUivv1c50/0.jpg)](https://youtu.be/EllUivv1c50)


**Conclusion**

Our team was able to successfully complete both tasks in Lab 3. The acoustic team was able to react to an external input to the FPGA (turning a switch on) and play a short three-frequency tune on the lab speakers. And the graphics team ….  <insert here>

Completing these two tasks was good practice with using the DE0-Nano Development Board and gave us a good start on the base station design for our final system. One the acoustic side, we still need to implement a way for the base station Arduino to trigger the three-tone sound instead of using a physical switch on the FPGA as we did in this lab. This should be relatively easy to implement by having the FPGA either poll an output pin from the Arduino or receive an interrupt when maze-mapping is complete. On the graphics side, ….. <insert here>
