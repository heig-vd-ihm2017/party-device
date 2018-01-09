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
    JewelStripe(uint8_t pin, uint8_t numberOfJewels) :
        _numberOfJewels(numberOfJewels)
    {
        uint8_t numberOfPixels = Jewel::NUMBER_OF_PIXELS_PER_JEWEL * _numberOfJewels;
        _stripe = new Jewel(pin, numberOfPixels);
    }

    /**
     * JewelStripe Destructor.
     */
    ~JewelStripe() {
        delete _stripe;
    }

    /**
     * Set the color of a specific pixel of a specific jewel.
     * @param jewelNumber The jewel where the pixel is situated.
     * @param pixelNumber The pixel to apply the color.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelColorInJewel(uint8_t jewelNumber, uint8_t pixelNumber, uint32_t jewelColor) {
        uint8_t red = jewelColor>> 24;
        uint8_t green = jewelColor>> 16;
        uint8_t blue = jewelColor>> 8;
        uint8_t white = jewelColor>> 0;

        setPixelColorInJewel(jewelNumber, pixelNumber, red, green, blue, white);
    }

    /**
     * Set the color of a specific pixel of a specific jewel.
     * @param jewelNumber The jewel where the pixel is situated.
     * @param pixelNumber The pixel to apply the color.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelColorInJewel(uint8_t jewelNumber, uint8_t pixelNumber, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
        // Calculate the exact LED offset in the stripe
        uint16_t pixelInStripe = (jewelNumber - 1) * Jewel::NUMBER_OF_PIXELS_PER_JEWEL + pixelNumber;

        setPixelColor(pixelInStripe, red, green, blue, white);
    }

    /**
     * Set the color of a specific jewel.
     * @param jewelNumber The jewel to apply the color.
     * @param jewelColor The color represented in hexadecimal.
     */
    void setJewelColor(uint8_t jewelNumber, uint32_t jewelColor) {
        uint8_t red = jewelColor>> 24;
        uint8_t green = jewelColor>> 16;
        uint8_t blue = jewelColor>> 8;
        uint8_t white = jewelColor>> 0;

        setJewelColor(jewelNumber, red, green, blue, white);
    }

    /**
     * Set the color of a specific jewel.
     * @param jewelNumber The jewel to apply the color.
     * @param red The intensity of red for the color (between 0 and 255).
     * @param green The intensity of green for the color (between 0 and 255).
     * @param blue The intensity of blue for the color (between 0 and 255).
     * @param white The intensity of white for the color (between 0 and 255).
     */
    void setJewelColor(uint8_t jewelNumber, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
        // Calculate the range of LEDs
        uint16_t pixelStart = (jewelNumber - 1) * Jewel::NUMBER_OF_PIXELS_PER_JEWEL;
        uint16_t pixelEnd = jewelNumber * Jewel::NUMBER_OF_PIXELS_PER_JEWEL;
        uint8_t numberOfPixels = _stripe->numberOfPixels();

        // Check if the pixels are addressable
        if (pixelStart >= 0 && pixelStart <= numberOfPixels &&
            pixelEnd > 0 && pixelEnd <= numberOfPixels)
        {

            // Change the color of each LEDs in the range
            for (uint8_t pixelNumber = pixelStart; pixelNumber < pixelEnd; ++pixelNumber) {
                setPixelColor(pixelNumber, red, green, blue, white);
            }
        }
    }

    /**
     * Set the color of a specific pixel.
     * @param pixelNumber The pixel to apply the color.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelColor(uint8_t pixelNumber, uint32_t pixelColor) {
        _stripe->setPixelColor(pixelNumber, pixelColor);
    }

    /**
     * Set the color of a specific pixel.
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
     * Set the color for all pixels.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelsColor(uint32_t pixelColor) {
        _stripe->setPixelsColor(pixelColor);
    }

    /**
     * Set the color for all pixels.
     * @param red The intensity of red for the color (between 0 and 255).
     * @param green The intensity of green for the color (between 0 and 255).
     * @param blue The intensity of blue for the color (between 0 and 255).
     * @param white The intensity of white for the color (between 0 and 255).
     */
    void setPixelsColor(uint8_t red, uint8_t green,  uint8_t blue, uint8_t white) {
        _stripe->setPixelsColor(red, green, blue, white);
    }

    /**
     * Return the number of jewels.
     * @return The number of jewel composing the stripe.
     */
    uint8_t numberOfJewels() {
      return _numberOfJewels;
    }

    /**
     * Return the number of pixels.
     * @return The number of pixels composing the stripe.
     */
    uint8_t numberOfPixels() {
      return _stripe->numberOfPixels();
    }

protected:
    //! Stripe of jewels.
    Jewel* _stripe;

    //! Number of jewels composing the stripe.
    uint8_t _numberOfJewels;
};

#endif // JEWELSTRIPE_H
