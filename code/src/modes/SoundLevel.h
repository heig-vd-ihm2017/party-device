#ifndef SOUNDLEVEL_H
#define SOUNDLEVEL_H

#include <Metro.h>
#include "modes/Mode.h"

class SoundLevel : public Mode {
public:
  SoundLevel(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _displayTime(50),
    _numberOfJewels(stripe->numberOfJewels())
    {
    }

  /**
    This mode lights up the Leds of a Jewel according to the sound level of the
    mic. It will light up from 1 to 7 LEDs according to the sound level.
  */
  virtual void apply() {
    // Get the sound level and the number of pixels that are used
    uint16_t soundLevel = _mic->soundLevel();

    // Calculate the range size of each interval
    uint16_t rangeSize = 255 / Jewel::NUMBER_OF_PIXELS_PER_JEWEL;

    // If display time has passed
    if (_displayTime.check()) {
      // Turn off all pixels
      _stripe->setPixelsColor(0);

      // Turn on the one that are under the soundLevel
      for (uint8_t j = 1; j <= _numberOfJewels; ++j ) {
        for (uint16_t i = 0; i < 7; ++i) {
          if (i * rangeSize <= soundLevel) {
            _stripe->setPixelColorInJewel(j, i, 10, 2, 4, 0);
          }
        }
      }

    }
  }

private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  Metro _displayTime;
  uint8_t _numberOfJewels;
};

#endif // SOUNDLEVEL_H
