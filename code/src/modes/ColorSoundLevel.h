#ifndef COLORSOUNDLEVEL_H
#define COLORSOUNDLEVEL_H

#include <Metro.h>
#include "modes/Mode.h"

class ColorSoundLevel : public Mode {
public:
  ColorSoundLevel(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfJewels(stripe->numberOfJewels())
    {

    }
    
  /**
    This mode changes the color of a Jewel according to the sound level,
    from a blue-ish color for low to a pink-ish for loud.
  */
  virtual void apply() {
    uint8_t soundLevel = (float)_mic->soundLevel();
    //float ratio = soundLevel / 255;
    uint8_t red = (uint8_t) (soundLevel * 0.2f);

    _stripe->setPixelsColor(red, 1, 3, 0);
  }

private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfJewels;

};

#endif // COLORSOUNDLEVEL_H
