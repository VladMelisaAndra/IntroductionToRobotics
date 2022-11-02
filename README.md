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
<img src="https://user-images.githubusercontent.com/79593335/199613858-635ac53d-d6df-4ee6-805e-fd99982b8991.jpeg" width="300" height="350">

##### Video showcasing functionality:
https://youtube.com/shorts/qmHVIxeu4bo
