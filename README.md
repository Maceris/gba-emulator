# Game Boy Advance Emulator

This is an emulator for the Game Boy Advance. It emulates the hardware, but to use it you would need
to own a physical Game Boy Advance and game(s), and use specialized hardware to provide the
device boot ROM and game ROM from your hardware to the program.

Nintendo, Game Boy, and Game Boy Advance are trademarks of Nintendo. This software is not
associated with Nintendo, and only includes the name to indicate what hardware it is intended to
emulate.

## Sub-Projects

* common - Common code that is shared between projects, like logging or general utilities.
* emulator - The actual emulator code, which emulates GameBoy Advance hardware
* interface - Sits on top of the emulator and allows input and output, like keyboard/controller support, a GUI, and audio output.
* third_party - Third party libraries.

## Building

This program requires CMake (at least version 3.14) to build, and on Windows, Microsoft Visual Studio
should be installed as well (preferably a recent version).

To create the project or solution files for the project, you can run `regenerate-project.bat` or `regenerate-project.sh`. 
This will generate all of the project files in the `bin` folder. These scripts can be rerun at any time to wipe out the
whole bin directory again and regenerate the project contents from scratch, which should rarely need to happen.

If using Visual Studio, you can open the solution and build and run it from there.
