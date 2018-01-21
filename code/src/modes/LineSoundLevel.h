#ifndef LINESOUNDLEVEL_H
#define LINESOUNDLEVEL_H

#include <Metro.h>
#include "modes/Mode.h"

/**
 * LineSoundLevel class
 *
 * This class displays a line. And when a sound is made, the line moves in
 * a circle. The line is red.
 */
class LineSoundLevel : public Mode {
private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfJewels;

  // Counter to loop
  uint8_t i;

public:
  LineSoundLevel(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfJewels(stripe->numberOfJewels())
  {
    i = 3;
  }

  virtual void apply() {
    uint8_t soundLevel = (float)_mic->soundLevel();

    // When a sound is made, resets the pixel and increments the counter
    if(soundLevel >= 30) {
      // Reset the previous extremity of the line
      _stripe->setPixelColor((i % 6) + 1, 0, 0, 0, 0);
      _stripe->setPixelColor(((i + 3) % 6) + 1, 0, 0, 0, 0);
      i++;
    }

    // The middle pixel is always on
    _stripe->setPixelColor(0, 50, 0, 0, 0);

    // Turn on the next extremity of the line
    _stripe->setPixelColor((i % 6) + 1, 50, 0, 0, 0);
    _stripe->setPixelColor(((i + 3) % 6) + 1, 50, 0, 0, 0);
  }
};

#endif // LINESOUNDLEVEL_H
