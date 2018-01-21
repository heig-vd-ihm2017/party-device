#include <EnableInterrupt.h>

#include "Modes.h"
#include "ModeController.h"
#include "io/MAX9814.h"
#include "io/JewelStripe.h"
#include "io/Button.h"

#define BTN_PIN 0 // Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_JEWELS 2 // Number of jewel you are using

// Define the input/output hardware
Button modeButton;
JewelStripe stripe(LED_PIN, NUMBER_OF_JEWELS);
MAX9814 mic(MIC_PIN);

ModeController modeController;

// Define the modes
//FixedRateRythmGame mode1(&stripe, &mic);
//SoundLevel mode2(&stripe, &mic);
MovingPoint mode3(&stripe, &mic);
CascadeSoundLevel mode4(&stripe, &mic);
//OneRandomLedRainbow mode5(&stripe, &mic);
SideBySide mode6(&stripe, &mic);
Mode* modes[] = {
    //&mode1,
    //&mode2,
    &mode3,
    &mode4,
    //&mode5,
    &mode6
};

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, FALLING);

    // Add the modes to the controller
    uint8_t numberOfModes = sizeof(modes) / sizeof(Mode);
    modeController.addModes(modes, numberOfModes);
}

void loop()
{
    while (true) {
        if (modeButton.hasBeenPressed()) {
            stripe.reset();
            modeController.loadNextMode();
        } else {
            modeController.runMode();
        }
    }

}
