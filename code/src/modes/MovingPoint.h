#ifndef MOVINGPOINT_H
#define MOVINGPOINT_H

#include <Metro.h>
#include "modes/Mode.h"

class MovingPoint : public Mode {
public:
  MovingPoint(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfPixels(stripe->numberOfPixels()),
    _metro(100),
    _pos(0)
    {

    }

  /**
    This mode moves a point of light across the stripe of jewels.
    It starts by listening for a sound and then runs a point of light.
  */
  virtual void apply() {
    // Listen
    if (_pos == 0) {
      _metro.reset();
      uint8_t soundLevel = _mic->soundLevel();
      if (soundLevel > 40) {
        _stripe->setPixelColor(_pos,0, 0, 0, 0);
        ++_pos;
      } else {
        _stripe->setPixelColor(_pos,20, 2, 6, 0);
        return;
      }
    } else {
      // Move the point
      if (_metro.check()) {
        _stripe->setPixelColor(_pos,0, 0, 0, 0);
        uint8_t nextPos = ++_pos % _numberOfPixels;
        _pos = nextPos;
      }
    }

    _stripe->setPixelColor(_pos,20, 2, 6, 0);
  }

private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfPixels;
  Metro _metro;
  uint8_t _pos;
};

#endif // MOVINGPOINT_H
