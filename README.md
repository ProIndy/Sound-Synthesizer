# Minisynth, with C and Raylib

This was a 48-hour Rush project at Hive Helsinki. The task was to create a program that could play the songs given in a specific format. The choice of tools was free. Me and Atte used Raylib, as it seemed do be simple enough for sound output.

Our program calculates the song in real time, 44100 samples a second. Four differend wave types are available: sine, square, triangle and saw.

### Prerequisites:

**For Mac :**
> brew install pkgconfig raylib

**For Linux :**
> sudo bash compile_raylib_linux.sh


### To compile :
Compile with Makefile


### Run the program with a songfile as argument :
> ./minisynth <file>

Sample files are found in rush_sound_synthesis_examples/

# Good luck !
