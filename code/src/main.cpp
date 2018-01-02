#include <EnableInterrupt.h>

#include "MAX9814.h"
#include "Jewel.h"
#include "Button.h"

#define BTN_PIN 2 // NEED TO CHANGE THIS TO 0. CONNECT TO THE MIC PIN Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_PIXELS 7 // Number of pixels you are using

Button modeButton;
Jewel jewel(LED_PIN, NUMBER_OF_PIXELS);
MAX9814 mic(MIC_PIN);

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, CHANGE);
}

void loop()
{
    delay(3000);
    if (modeButton.hasBeenPressed()) {
        jewel.setPixelColor(1, 10, 0, 0, 0);
    } else {
        jewel.setPixelColor(1, 0, 10, 0, 0);
    }
}
