#include <EnableInterrupt.h>

#include "MAX9814.h"
#include "Jewel.h"
#include "Button.h"
#include "Modes.h"

#define BTN_PIN 0 // NEED TO CHANGE THIS TO 0. CONNECT TO THE MIC PIN Pin on which the button is conncted (Gemma: D0)
#define LED_PIN 1 // Pin on which the NeoPixel is connected (Gemma: D1)
#define MIC_PIN 1 // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_PIXELS 7 // Number of pixels you are using

Button modeButton;
Jewel jewel(LED_PIN, NUMBER_OF_PIXELS);
MAX9814 mic(MIC_PIN);

void (*mode)(Jewel*, MAX9814*) = nullptr;

SoundLevel s = SoundLevel(&jewel, &mic);
FixedRateRythmGame f = FixedRateRythmGame(&jewel, &mic);

Mode* m = &s;

bool lol = false;

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, CHANGE);

    // Set the first mode
    mode = soundLevel;
}

Metro m2 = Metro(1000);

void loop()
{
    // if (modeButton.hasBeenPressed()) {
    //   // TODO change the mode of the party device
    //   mode = fixedRateRythmGame;
    //
    // } else {
    //   // Execute the current mode
    //   mode(&jewel, &mic);
    // }
    m->apply();

    if(m2.check()) {
      if (lol) {
        m = &f;
        lol = false;
      } else {
        m = &s;
        lol = true;
      }
    }

}
