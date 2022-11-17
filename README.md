# Introduction to Robotics (2022 - 2023)
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.
  
## Homework 1

##### Technical Task:
Use a separate potentiometer in controlling each of the color of the RGB led.  The control must be done with digital electronics, you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

##### Components: 
- 1 RBG  LED
- 3 Potentiometers
- Resistors and wires 

##### Setup picture:
<img src="https://user-images.githubusercontent.com/79593335/198230851-bb79c133-600a-43ac-9c9b-be94f285c07b.jpeg" width="300" height="400">

##### Video showcasing functionality:
https://youtube.com/shorts/5eQQ961vcYE

## Homework 2

##### Technical Task:
Building the traffic lights for a crosswalk. You
will use 2 LEDs to represent the traffic lights for people (red and green)
and 3 LEDs to represent the traffic lights for cars (red, yellow and green).
The system has the following states:
- State 1 (default, reinstated after state 4 ends): green light for cars,
red light for people, no sounds. Duration: indefinite, changed by
pressing the button.
- State 2 (initiated by counting down 8 seconds after a button press):
the light should be yellow for cars, red for people and no sounds.
Duration: 3 seconds.
- State 3 (initiated after state 2 ends): red for cars, green for people
and a beeping sound from the buzzer at a constant interval. Duration:
8 seconds.
- State 4 (initiated after state 3 ends): red for cars, blinking green
for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. This state should last 4
seconds.
Pressing the button in any state other than state 1 should
NOT yield any actions.

##### Components: 
- 5 LEDs
- 1 button
- 1 buzzer
- resistors and wires 

##### Setup picture:
<img src="https://user-images.githubusercontent.com/79593335/199613858-635ac53d-d6df-4ee6-805e-fd99982b8991.jpeg" width="300" height="320">

##### Video showcasing functionality:
https://youtube.com/shorts/qmHVIxeu4bo

## Homework 3

##### Technical Task:
You will use the joystick to control the position of the segment and ”draw” on the display. The movement between segments should be natural (meaning they should jump from the current position only to neighbors, but without passing through ”walls”. The system has the following states:
1. State  1 (default,  but  also  initiated  after  a  button  press  in  State 2): Current  position  blinking. Can  use  the  joystick  to  move  from one  position  to  neighbors.   Short  pressing  the  button  toggles  State 2.  Long pressing the button in State 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
2. State  2 (initiated  after  a  button  press  in  State  1): The  current segment  stops  blinking, adopting  the  state  of  the  segment  before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change  the  segment  state  from  ON  to  OFF  or  from  OFF  to  ON. Clicking the joystick should save the segment state and exit back to State 1.

##### Components: 
- 1 7-segment  display
- 1  joystick
- resistors  and  wires  

##### Setup picture:
<img src="https://user-images.githubusercontent.com/79593335/200953546-69170fc6-8ee9-465e-8ee5-3fb314e145c7.jpeg" width="300" height="420">

##### Video showcasing functionality:
https://youtube.com/shorts/LIXhU1B32pM

## Homework 4

##### Technical Task:
Use the joystick to move through the 4 digit 7
segment displays digits, press the button to lock in on the current digit
and use the other axis to increment or decrement the number. Keep the
button pressed to reset all the digit values and the current position to the
first digit in the first state.
The system has the following states:
1. First state: you can use a joystick axis to cycle through the 4 digits;
using the other axis does nothing. A blinking decimal point shows
the current digit position. When pressing the button, you lock in on
the selected digit and enter the second state.
2. Second state: in this state, the decimal point stays always on, no
longer blinking and you can no longer use the axis to cycle through
the 4 digits. Instead, using the other axis, you can increment on
decrement the number on the current digit IN HEX (aka from 0
to F, as in the lab). Pressing the button again returns you to the
previous state. 
3. Reset: toggled by long pressing the button only in the first state.
When resetting, all the digits go back to 0 and the current position
is set to the first (rightmost) digit, in the first state.

##### Components: 
- a joystick
- a 4 digit 7-segment display
- a 74hc595 shift register 

##### Setup picture:
<img src="https://user-images.githubusercontent.com/79593335/202384599-b3dc6036-38de-4590-b4f3-6c2379baa0ec.jpeg" width="300" height="320">

##### Video showcasing functionality:
https://www.youtube.com/shorts/ATGT2SNVan4
