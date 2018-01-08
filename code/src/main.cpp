#include <EnableInterrupt.h>

#include "MAX9814.h"
#include "JewelStripe.h"
#include "Button.h"
#include "Modes.h"

#define BTN_PIN 0 // NEED TO CHANGE THIS TO 0. CONNECT TO THE MIC PIN Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_JEWELS 1 // Number of jewel you are using

Button modeButton;
JewelStripe stripe(LED_PIN, NUMBER_OF_JEWELS);
MAX9814 mic(MIC_PIN);

void (*mode)(JewelStripe*, MAX9814*) = nullptr;

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, CHANGE);

    // Set the first mode
    mode = soundLevel;
}

void loop()
{
    if (modeButton.hasBeenPressed()) {
      // TODO change the mode of the party device
      mode = fixedRateRythmGame;

    } else {
      // Execute the current mode
      mode(&stripe, &mic);
    }
}
