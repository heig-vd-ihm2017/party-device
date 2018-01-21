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
  uint8_t direction[6][7];
  uint8_t i = 0;

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

    direction[0][0] = 1;
    direction[0][1] = 0;
    direction[0][2] = 4;
    direction[0][3] = 6;
    direction[0][4] = 5;
    direction[0][5] = 2;
    direction[0][6] = 3;

    direction[1][0] = 6;
    direction[1][1] = 0;
    direction[1][2] = 3;
    direction[1][3] = 5;
    direction[1][4] = 4;
    direction[1][5] = 1;
    direction[1][6] = 2;

    direction[2][0] = 2;
    direction[2][1] = 0;
    direction[2][2] = 5;
    direction[2][3] = 1;
    direction[2][4] = 6;
    direction[2][5] = 3;
    direction[2][6] = 4;

    direction[3][0] = 3;
    direction[3][1] = 0;
    direction[3][2] = 6;
    direction[3][3] = 2;
    direction[3][4] = 1;
    direction[3][5] = 4;
    direction[3][6] = 5;

    direction[4][0] = 4;
    direction[4][1] = 0;
    direction[4][2] = 1;
    direction[4][3] = 3;
    direction[4][4] = 2;
    direction[4][5] = 5;
    direction[4][6] = 6;

    direction[5][0] = 5;
    direction[5][1] = 0;
    direction[5][2] = 2;
    direction[5][3] = 4;
    direction[5][4] = 3;
    direction[5][5] = 6;
    direction[5][6] = 1;
  }

  virtual void apply() {
    uint8_t soundLevel = (float)_mic->soundLevel();

    if(soundLevel >= 30) {
      i = (i + 1) % 6;
    }

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

    _stripe->setPixelColor(direction[i][0], color[0], 0, 0, 0);
    _stripe->setPixelColor(direction[i][1], color[1], 0, 0, 0);
    _stripe->setPixelColor(direction[i][2], color[2], 0, 0, 0);

    _stripe->setPixelColor(direction[i][3], color[0], 0, 0, 0);
    _stripe->setPixelColor(direction[i][4], color[2], 0, 0, 0);

    _stripe->setPixelColor(direction[i][5], color[0], 0, 0, 0);
    _stripe->setPixelColor(direction[i][6], color[2], 0, 0, 0);
  }
};

#endif
