#ifndef MODESOUNDLEVEL_H
#define MODESOUNDLEVEL_H

#include "Jewel.h"
#include "MAX9814.h"

/**
  The modeSoundLevel is a mode that will turn on the a specific number of LEDs
  according to the sound level the mic perceives. The mic returns a sound level
  in the [0, 255] range. This range is subdivided in the same number of intervals
  that the number of LEDs that are used.

  The mode will then turn on the LEDs that correspond to the intervals given
  they are inferior to the sound level perceived by the mic.
*/
void modeSoundLevel(Jewel* jewel, MAX9814* mic) {
  // Get the sound level and the number of pixels that are used
  uint16_t soundLevel = mic->soundLevel();
  uint16_t numberOfPixels = jewel->numberOfPixels();

  // Calculate the range size of each interval
  uint16_t rangeSize = 255 / numberOfPixels;

  // Turn off all pixels
  jewel->setPixelsColor(0, 0, 0, 0);

  // Turn on the one that are under the soundLevel
  for (uint16_t i = 0; i * rangeSize < soundLevel; ++i) {
    jewel->setPixelColor(i, 5, 5, 5, 0);
  }
}

#endif
