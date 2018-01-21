#include <EnableInterrupt.h>

#include "Modes.h"
#include "ModeController.h"
#include "io/MAX9814.h"
#include "io/JewelStripe.h"
#include "io/Button.h"

#define BTN_PIN 0 // Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_JEWELS 1 // Number of jewel you are using

// Define the input/output hardware
Button modeButton;
JewelStripe stripe(LED_PIN, NUMBER_OF_JEWELS);
MAX9814 mic(MIC_PIN);

// Define the mode controller and create the modes
ModeController modeController;
ModeTest1 modeTest1(stripe, mic);
ModeTest2 modeTest2(stripe, mic);
ModeTest3 modeTest3(stripe, mic);
ModeTest4 modeTest4(stripe, mic);
Mode* modes[] = {&modeTest1, &modeTest2, &modeTest3, &modeTest4};

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, FALLING);

    // Add the modes to the controller
    uint8_t numberOfModes = sizeof(modes) / sizeof(modes[0]);
    modeController.addModes(modes, numberOfModes);
}

void loop()
{
    while (true) {
        if (modeButton.hasBeenPressed()) {
            modeController.loadNextMode();
        } else {
            modeController.runMode();
        }
    }

}
