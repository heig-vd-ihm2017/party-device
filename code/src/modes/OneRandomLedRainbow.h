#ifndef ONERANDOMLEDRAINBOW_H
#define ONERANDOMLEDRAINBOW_H

#include "modes/Mode.h"

class OneRandomLedRainbow : public Mode {
public:
    OneRandomLedRainbow(JewelStripe* stripe,
        MAX9814* mic)
    :
        _stripe(stripe),
        _mic(mic),
        _numberOfPixels(stripe->numberOfPixels()),
        _selectedLed(0)
    {
        // Empty
    }

    virtual void apply() {

        uint8_t soundLevel = _mic->soundLevel();

        if(soundLevel >= 30) {
            _stripe->reset();

            _selectedLed = random(0, _numberOfPixels);
            red = random(0, 50);
            green = random(0, 50);
            blue = random(0, 50);
        }

        _stripe->setPixelColor(_selectedLed, red, green, blue, 0);
    }

private:

    //! The available stripe.
    JewelStripe* _stripe;

    //! The available microphone.
    MAX9814* _mic;

    //! Number of available pixels.
    uint8_t _numberOfPixels;

    //! The LED to begin with.
    uint8_t _selectedLed;

    //! Red color to apply to the LED.
    uint8_t red;

    //! Green color to apply to the LED.
    uint8_t green;

    //! Blue color to apply to the LED.
    uint8_t blue;

    //! White color to apply to the LED.
    uint8_t white;
};

#endif // ONERANDOMLEDRAINBOW_H
