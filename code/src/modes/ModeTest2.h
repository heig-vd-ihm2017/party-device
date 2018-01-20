#ifndef MODETEST2_H
#define MODETEST2_H

#include "modes/Mode.h"

class ModeTest2 : public Mode {
public:
    ModeTest2(JewelStripe& stripe,
        MAX9814& mic)
    :
        _stripe(stripe),
        _mic(mic)
    {
        // Empty
    }

    virtual void apply() {
        _stripe.setPixelsColor(0, 5, 0, 0);
    }

private:
    JewelStripe _stripe;
    MAX9814 _mic;
};

#endif // MODETEST2_H
