#ifndef CASCADESOUNDLEVEL_H
#define CASCADESOUNDLEVEL_H

#include <Metro.h>
#include "modes/Mode.h"

class CascadeSoundLevel : public Mode {
private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfJewels;

  uint8_t init_intensity = 200;
  float multiplier_down = 0.9f;
  float multiplier_up = 1.1f;

  float color[3];
  float multiplier[3];

public:
  CascadeSoundLevel(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfJewels(stripe->numberOfJewels())
  {
    color[0] = init_intensity + 55;
		color[1] = init_intensity + 25;
		color[2] = init_intensity;

		multiplier[0] = multiplier_down;
		multiplier[1] = multiplier_down;
		multiplier[2] = multiplier_down;
  }

  virtual void apply() {
    uint8_t soundLevel = (float)_mic->soundLevel();

		if (color[0] <= 10) {
			multiplier[0] = multiplier_up;
		} else if (color[0] >= init_intensity) {
			multiplier[0] = multiplier_down;
		}

		if (color[1] <= 10) {
			multiplier[1] = multiplier_up;
		} else if (color[1] >= init_intensity) {
			multiplier[1] = multiplier_down;
		}

		if (color[2] <= 10) {
			multiplier[2] = multiplier_up;
		} else if (color[2] >= init_intensity) {
			multiplier[2] = multiplier_down;
		}

    color[0] *= multiplier[0];
    color[1] *= multiplier[1];
    color[2] *= multiplier[2];

    _stripe->setPixelColor(6, color[0], 0, 0, 0);
    _stripe->setPixelColor(0, color[1], 0, 0, 0);
    _stripe->setPixelColor(3, color[2], 0, 0, 0);

    _stripe->setPixelColor(5, color[0], 0, 0, 0);
    _stripe->setPixelColor(4, color[2], 0, 0, 0);

    _stripe->setPixelColor(1, color[0], 0, 0, 0);
    _stripe->setPixelColor(4, color[2], 0, 0, 0);
  }
};

#endif
