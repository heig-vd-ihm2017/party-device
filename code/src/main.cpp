#include <EnableInterrupt.h>

#include "ModeController.h"
#include "MAX9814.h"
#include "JewelStripe.h"
#include "Button.h"

#define BTN_PIN 0 // Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_JEWELS 1 // Number of jewel you are using

Button modeButton;

JewelStripe stripe(LED_PIN, NUMBER_OF_JEWELS);
MAX9814 mic(MIC_PIN);

ModeTest1 modeTest1(stripe, mic);
ModeTest2 modeTest2(stripe, mic);

Mode* modes[] = {&modeTest1, &modeTest2};

ModeController modeController(modes, 2);

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, CHANGE);
}

void loop()
{
    modeController.runMode();
    delay(1000);
    modeController.loadNextMode();
    modeController.runMode();
    delay(1000);

    /*
    if (modeButton.hasBeenPressed()) {
        modeLoader.loadNextMode();
        modeLoader.runMode();
    } else {

    }
    */
}
