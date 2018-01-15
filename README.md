# Party device
A device for parties with lights that react to sounds.

## Principles
A core device listens to sounds with a microphone. Multiple lights can be connected to this core device in chains that can be independently addressed.

The core device can have different modes stored in it. A button allows to cycle in all the available modes.

Depending on the environment volume and the current mode used, the core device pilots the lights and can react differently.

See [Applications](#applications) section for some examples.

The device can be used as a wearable device with batteries or as a standalone device directly connected to the wall.

## Applications
This kind of device can have multiples usages.

Here are some examples to illustrate the usages:

- Installed inside a bar, the device can change the lights colors based on the playing music.
- Attached to a cosplay costume, the device can add animations to the costume based on the environment sound level.
- A rhythm game where you have to stay in rhythm with the lights to keep them green. When an error is made, the lights turn red.
- A multi-player game where each player has its own Jewel. The Jewel are randomly turned on and the corresponding player had to do some sound before its Jewel turns off. If the corresponding player didn't make sound in time, all the Jewel turn red and the player lost.
- As a kind of alarm device that triggers the lights when the sound level is too high.

## Limitations
Currently, the device can only use the sound level of the environment. Some work has been done to implement a [Fast Fourier Transform (FFT)](https://en.wikipedia.org/wiki/Fast_Fourier_transform) to be able to get the sound's frequency but it is not ready for production yet.

In a multi-player game, the device cannot verify if the right player did the sound or if it's another player who did it. The players have to check who did the sound and keep the game going.

## Best practices, user-friendliness and love
For the entire project, we tried to apply some good practices.

We tried to apply the [KISS principle](https://en.wikipedia.org/wiki/KISS_principle) as well as the best practices in design based on Don Norman's [The Design of Everyday Things](https://en.wikipedia.org/wiki/The_Design_of_Everyday_Things) book.

For the projects, we had two main aspects: the "real-life" device and the software aspects.

For the real-life device, we wanted to make some custom cases with the following aspects:

1. Have some cases that could be easily made, opened and customized if needed
2. Have some easy-to-use cases
3. Be able to place the lights where we wanted
4. Have easy access to the Inputs / Outputs ports for power supply and development
5. Cycle in the available modes with a simple button
6. Change the microphone sensitivity from the outside

And we tried to address all these points with the following ones:

1. We created some cases with a laser cutter with some Plexiglas that can mounted with only some screws. All the files to cut the cases are, of course, available. As a mater of facts, the cases can be easily opened and customized.
2. There are only a few I/O ports:
    - Mode cycler, to cycle in the modes
    - Microphone sensitivity switcher, to adjust the sensitivity with the environment
    - An output to connect the Jewels
    - An input for the power supply
    - The USB port for developers
3. As the Core case and the Jewel case are separated and some connectors allows to connect them, the user can have a cable with a custom length to place the Core case and the Jewel case where needed.
4. The power supply and USB ports can be easily accessed from the outside of the case to add some new modes or change the power supply.
5. The user can press the modes cycler button whenever he wants and the Core device will change the mode.
6. The microphone has three levels of sensitivity that allows to adjust the microphone to the environment sound level. For example, the microphone sensitivity can be adjusted if the bar is too noisy and the core device is not able to get differences in the sound level as the microphone is saturated.

For the software, we wanted to let the user the opportunity to create his own new modes. We designed a custom framework to add some new modes in a breeze.

## Components
The components used to create the device are the following ones:

- 1x [Adafruit Gemma v2](https://www.adafruit.com/gemma/) - The microcontroller controlling everything.
- 1x [Electret Microphone Amplifier](https://www.adafruit.com/product/1713) - The microphone used to listen to sounds.
- 1 or more [NeoPixel Jewel](https://www.adafruit.com/product/2226) - The lights that can be chained.
- 1x [Tactile button switch](https://www.adafruit.com/product/367) and 1x [10K ohm resistor](https://www.adafruit.com/product/2784) - The button used to cycle the modes.
- Electrical wires
- Three pins connectors (males and females)
- Custom cases


## Custom cases
The custom cases are made with a laser cutter. All files are available here.

There are two cases for this project: the core device's case and the jewel's case.

### Core case
The Core case has the Gemma v2 and the microphone.

A button allows to cycle the modes. The user can press this button whenever he wants and a slide switch allows to change the gain of the microphone.

The power supply allows to power the device with some batteries or from a wall charger.

The USB port allows the user to develop some new modes and reprogram the device.

The output allows to connect the first Jewel.

### Jewel case
The Jewel case has the Jewel and two connectors: one for the input and the other for the output to connect an additional Jewel.

### Connectors
The Core and Jewel cases use a 4 pins connector. One of the pin is banned to create a keyed connector to be sure the user connects the cable correctly.

### Cables
To connect the Core and the Jewel case, a cable with three pins is needed. The user can decide to have the length of cable he wants to place the Jewel and the Core where needed.

## Programming concepts
For the software part, we tried to keep a high level of abstraction to add new modes and extend the software easily. We created the following structure:

```
io/                 # Contains all the I/O classes
   Button.h         # Abstract the button to get the button state
   Jewel.h          # Abstract the Jewel with some methods to set the LEDs color
   JewelStripe.h    # Abstract a stripe of Jewels where a specific Jewel in the stripe can be addressed
   MAX9814.h        # Abstract the microphone to get the sound volume
modes/              # Contains all the modes
    Mode.h          # Interface that all modes must extends
    Mode1.h         # The first mode
    Mode2.h         # The second mode
    [...]
    ModeN.h         # The last modes
main.cpp            # The main program where everything is created
ModeController.h    # The mode controller that loads the modes and switch between them
Modes.h             # A simple header including all the modes from the modes/ folder
```

This structure allows to add more sensor in the future or add new methods in `JewelStripe.h` or `MAX9814.h` without breaking the rest of the program.

### Program customs modes
*Follow the cloning process [here](#developers) before developing new modes.*

Here are the steps to add a new custom mode:

Copy the following code in a new file called `MyNewMode.h` placed inside the directory `modes`:

```
#ifndef MYNEWMODE_H
#define MYNEWMODE_H

#include "modes/Mode.h"

class MyNewMode : public Mode {
public:
    ModeTest1(JewelStripe& stripe,
        MAX9814& mic)
    :
        _stripe(stripe),
        _mic(mic)
    {
        // Empty
    }

    virtual void apply() {
        // Do something here with _stripe and _mic
    }

private:
    JewelStripe _stripe;
    MAX9814 _mic;
};

#endif // MYNEWMODE_H
```

Add the following line in the file `Modes.h`:

```
#include "modes/MyNewMode.h"
```

Then, you can edit the method `apply()` in `modes/MyNewMode.h` to do whatever you want with `_stripe` and `_mic`.

## Developers
Here are some resources for developers.

### IDE and libraries
We decided to use [PlatformIO](http://platformio.org/) as our main IDE. It helps to automate most of the process of building and uploading the program to the microcontroller.

We used the following libraries in our project as well:

- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) for the Jewels
- [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt) to monitor the pins to detect an interruption
- [Metro-Arduino-Wiring](https://github.com/thomasfredericks/Metro-Arduino-Wiring) to help implementing recurring timed events

### Cloning the repository and initialize modules
To clone the repository and initialize the program, type the following lines in a terminal:
```
git clone git@github.com:heig-vd-ihm2017/party-device.git
cd party-device
git submodule init
git submodule update
```

#### Updating modules
Modules will have their `HEAD` disconnected from the master branch. You have update them manually:
```
cd code/lib/<module>
git checkout master
git pull
```

### Documentation
Here are some documentation we used and found useful for the project:

- [Adafruit NeoPixel Überguide]( https://learn.adafruit.com/adafruit-neopixel-uberguide) - The ultimate guide about NeoPixel.
- [Recommendations for laser cutter with Inkscape](http://www.cutlasercut.com/resources/drawing-guidelines/styles-examples) for thickness and colors to use.
-  [learn.adafruit.com](http://learn.adafruit.com/) for examples and guides
