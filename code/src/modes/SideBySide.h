#ifndef SIDEBYSIDE_H
#define SIDEBYSIDE_H

#include "modes/Mode.h"

class SideBySide : public Mode {
public:
    SideBySide(JewelStripe* stripe,
        MAX9814* mic)
    :
        _stripe(stripe),
        _mic(mic),
        _numberOfJewels(stripe->numberOfJewels()),
        _selectedJewel(0)
    {
        // Empty
    }

    virtual void apply() {

        uint8_t soundLevel = _mic->soundLevel();

        if(soundLevel >= 30) {
            _stripe->reset();

            _selectedJewel = (_selectedJewel == 1) ? 2 : 1;
            red = random(0, 20);
            green = random(0, 20);
            blue = random(0, 20);
        }

        _stripe->setJewelColor(_selectedJewel, red, green, blue, 0);
        delay(50);
    }

private:

    //! The available stripe.
    JewelStripe* _stripe;

    //! The available microphone.
    MAX9814* _mic;

    //! Number of available pixels.
    uint8_t _numberOfJewels;

    //! The LED to begin with.
    uint8_t _selectedJewel;

    //! Red color to apply to the LED.
    uint8_t red;

    //! Green color to apply to the LED.
    uint8_t green;

    //! Blue color to apply to the LED.
    uint8_t blue;

    //! White color to apply to the LED.
    uint8_t white;
};

#endif // SIDEBYSIDE_H
