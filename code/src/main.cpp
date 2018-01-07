#include <EnableInterrupt.h>

#include "MAX9814.h"
#include "Jewel.h"
#include "Button.h"
#include "modeSoundLevel.h"
#include "modeFixedRateRythmGame.h"

#define BTN_PIN 2 // NEED TO CHANGE THIS TO 0. CONNECT TO THE MIC PIN Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_PIXELS 7 // Number of pixels you are using

Button modeButton;
Jewel jewel(LED_PIN, NUMBER_OF_PIXELS);
MAX9814 mic(MIC_PIN);

void (*mode)(Jewel*, MAX9814*) = NULL;

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, CHANGE);

    // Set the first mode
    mode = modeFixedRateRythmeGame;
}

void loop()
{
    if (modeButton.hasBeenPressed()) {

      // TODO change the mode of the party device


    } else {
      // Execute the current mode
      mode(&jewel, &mic);
    }
}
