#ifndef MODETEST1_H
#define MODETEST2_H

#include "modes/Mode.h"

class ModeTest4 : public Mode {
public:
  ModeTest4(JewelStripe& stripe, MAX9814& mic) :
    _stripe(stripe),
    _mic(mic)
    {
    }

  virtual void apply() {
    _stripe.setPixelsColor(0, 0, 0, 5);
  }

private:
  JewelStripe _stripe;
  MAX9814 _mic;
};

#endif // SOUNDLEVEL_H
