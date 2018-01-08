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

//ModeLoader modeLoader(2, &jewel);

Mode* soundLevel = new SoundLevel(&jewel, &mic);
Mode* fixedRateRythmGame = new FixedRateRythmGame(&jewel, &mic);

Metro metro = Metro(2000);

Mode** modes = (Mode**) new Mode*[2];

int16_t index = 0;

Mode* mode = NULL;

void setup()
{
    // Enable interruption for the button
    enableInterrupt(BTN_PIN, []() { modeButton.pressed(); }, CHANGE);

    //modeLoader.addMode(&soundLevel);
    //modeLoader.addMode(&fixedRateRythmGame);

    //modes = (Mode**) malloc(2 * sizeof(Mode*));
    modes[0] = soundLevel;
    modes[1] = fixedRateRythmGame;

    mode = fixedRateRythmGame;
}

void loop()
{

    // if (modeButton.hasBeenPressed() || metro.check()) {
    //
    //     jewel.setPixelsColor(0, 0, 5, 0);
    // } else {
    //   jewel.setPixelsColor(0, 0, 5, 0);
    //     //modeLoader.runMode();
    // }

    // if (metro.check()) {
    //   if (lol) {
    //     modeLoader.loadNextMode();
    //     lol = false;
    //   } else {
    //     lol = true;
    //   }
    // }
    if (metro.check()) {
      index = (index + 1) % 2;
      metro.reset();
    }

    //modes[index]->apply();
    soundLevel->apply();

    //mode->apply();

    // if (index == 1) {
    //   jewel.setPixelsColor(0, 0, 5, 0);
    // } else {
    //   jewel.setPixelsColor(0, 0, 0, 0);
    //   //modes[index]->apply();
    // }
    //modeLoader.runMode();

}
