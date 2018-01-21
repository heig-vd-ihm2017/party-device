#ifndef CASCADESOUNDLEVEL_H
#define CASCADESOUNDLEVEL_H

#include <Metro.h>
#include "modes/Mode.h"

class CascadeSoundLevel : public Mode {
private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfJewels;

  uint8_t color[7];

public:
  CascadeSoundLevel(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfJewels(stripe->numberOfJewels())
  {
    color[0] = 230;
		color[1] = 80;
		color[2] = 150;
    color[3] = 220;
    color[4] = 220;
    color[5] = 150;
    color[6] = 80;
  }

  virtual void apply() {
    uint8_t soundLevel = (float)_mic->soundLevel();

    if(soundLevel >= 30) {
  		color[1] = (color[1] + 70) % 255;
  		color[2] = (color[2] + 70) % 255;
      color[3] = (color[3] + 70) % 255;
      color[4] = (color[4] + 70) % 255;
      color[5] = (color[5] + 70) % 255;
      color[6] = (color[6] + 70) % 255;
    }

    _stripe->setPixelColor(0, color[0], 0, 0, 0);
    _stripe->setPixelColor(1, color[1], 0, 0, 0);
    _stripe->setPixelColor(2, color[2], 0, 0, 0);
    _stripe->setPixelColor(3, color[3], 0, 0, 0);
    _stripe->setPixelColor(4, color[4], 0, 0, 0);
    _stripe->setPixelColor(5, color[5], 0, 0, 0);
    _stripe->setPixelColor(6, color[6], 0, 0, 0);
  }
};

#endif
