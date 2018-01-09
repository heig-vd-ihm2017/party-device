#ifndef JEWELSTRIPE_H
#define JEWELSTRIPE_H

#include "Jewel.h"

class JewelStripe {

public:

    /**
     * JewelStripe Constructor.
     * @param pin The pin number on which the NeoPixel is connected.
     * @param numberOfJewels The number of Jewels composing the stripe.
     */
    JewelStripe(uint8_t pin, uint8_t numberOfJewels) {
        uint8_t numberOfPixels = Jewel::NUMBER_OF_PIXELS_PER_JEWEL * numberOfJewels;
        _stripe = new Jewel(pin, numberOfPixels);
    }

    ~JewelStripe() {
        delete _stripe;
    }

    /**
     * Set the colors of a specific pixel.
     * @param pixelNumber The pixel to apply the color.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelColor(uint8_t pixelNumber, uint32_t pixelColor) {
        _stripe->setPixelColor(pixelNumber, pixelColor);
    }

    /**
     * Set the colors of a specific pixel.
     * @param pixelNumber The pixel to apply the color.
     * @param red The intensity of red for the color (between 0 and 255).
     * @param green The intensity of green for the color (between 0 and 255).
     * @param blue The intensity of blue for the color (between 0 and 255).
     * @param white The intensity of white for the color (between 0 and 255).
     */
    void setPixelColor(uint8_t pixelNumber, uint8_t red, uint8_t green,  uint8_t blue, uint8_t white) {
        _stripe->setPixelColor(pixelNumber, red, green, blue, white);
    }

    /**
     * Set the colors for all pixels.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelsColor(uint32_t pixelColor) {
        _stripe->setPixelsColor(pixelColor);
    }

    /**
     * Set the colors for all pixels.
     * @param red The intensity of red for the color (between 0 and 255).
     * @param green The intensity of green for the color (between 0 and 255).
     * @param blue The intensity of blue for the color (between 0 and 255).
     * @param white The intensity of white for the color (between 0 and 255).
     */
    void setPixelsColor(uint8_t red, uint8_t green,  uint8_t blue, uint8_t white) {
        _stripe->setPixelsColor(red, green, blue, white);
    }

    /**
     * Return the number of pixels.
     */
    uint8_t numberOfPixels() {
      return _stripe->numberOfPixels();
    }

protected:
    //! Stripe of jewels
    Jewel* _stripe;
};

#endif // JEWELSTRIPE_H
