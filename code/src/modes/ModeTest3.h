#ifndef MODETEST3_H
#define MODETEST3_H

#include "modes/Mode.h"

class ModeTest3 : public Mode {
public:
    ModeTest3(JewelStripe& stripe,
        MAX9814& mic)
    :
        _stripe(stripe),
        _mic(mic)
    {
        // Empty
    }

    virtual void apply() {
        _stripe.setPixelsColor(0, 0, 5, 0);
    }

private:
    JewelStripe _stripe;
    MAX9814 _mic;
};

#endif // MODETEST3_H
