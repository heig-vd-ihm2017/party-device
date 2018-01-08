#ifndef SOUNDLEVEL_H
#define SOUNDLEVEL_H

#include "Jewel.h"
#include "MAX9814.h"
#include "Metro.h"
#include "modes/modeInterface.h"

class SoundLevel : public Mode {
public:
  SoundLevel(Jewel* jewel, MAX9814* mic) :
    jewel(jewel),
    mic(mic),
    displayTime(50)
    {
    }

  virtual void apply() {
    // // Get the sound level and the number of pixels that are used
    // uint16_t soundLevel = mic->soundLevel();
    // uint16_t numberOfPixels = jewel->numberOfPixels();
    //
    // // Calculate the range size of each interval
    // uint16_t rangeSize = 255 / numberOfPixels;
    //
    // // If display time has passed
    // if (displayTime.check()) {
    //   // Turn off all pixels
    //   jewel->setPixelsColor(0, 0, 0, 0);
    //
    //   // Turn on the one that are under the soundLevel
    //   for (uint16_t i = 0; i * rangeSize < soundLevel; ++i) {
    //     jewel->setPixelColor(i, 5, 5, 5, 0);
    //   }
    // }
    jewel->setPixelsColor(5, 0, 0, 0);
  }

private:
  Jewel* jewel;
  MAX9814* mic;
  Metro displayTime;
};

#endif // SOUNDLEVEL_H
