#ifndef CASCADESOUNDLEVEL_H
#define CASCADESOUNDLEVEL_H

#include <Metro.h>
#include "modes/Mode.h"

class CascadeSoundLevel : public Mode {
private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfJewels;

  uint8_t fade[3];

public:
  CascadeSoundLevel(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfJewels(stripe->numberOfJewels())
  {
    fade[0] = 200;
    fade[1] = 200;
    fade[2] = 200;
  }

  virtual void apply() {
    uint8_t soundLevel = (float)_mic->soundLevel();


    // The middle pixel is always on
    fade[0] *= 0.9999;
    fade[1] *= 0.999;
    fade[2] *= 0.99;
    _stripe->setPixelColor(1, fade[0], 0, 0, 0);
    _stripe->setPixelColor(0, fade[1], 0, 0, 0);
    _stripe->setPixelColor(4, fade[2], 0, 0, 0);

  }
};

#endif
