#ifndef MODETEST1_H
#define MODETEST1_H

#include "modes/Mode.h"

class ModeTest1 : public Mode {
public:
    ModeTest1(JewelStripe& stripe,
        MAX9814& mic)
    :
        _stripe(stripe),
        _mic(mic)
    {
        // Empty
    }

    virtual void apply() {
        _stripe.setJewelColor(1, 0x05000000);
    }

private:
    JewelStripe _stripe;
    MAX9814 _mic;
};

#endif // MODETEST1_H
