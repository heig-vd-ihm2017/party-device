/*
https://learn.adafruit.com/adafruit-neopixel-uberguide
https://learn.adafruit.com/jewel-hair-stick/arduino-code
*/

#ifndef JEWEL_H
#define JEWEL_H

#include <Adafruit_NeoPixel.h>

class Jewel
{

public:

    static const uint8_t NUMBER_OF_PIXELS_PER_JEWEL;
    /**
     * Jewel Constructor.
     * @param pin The pin number on which the NeoPixel is connected.
     * @param numberOfPixels The number of NeoPixels connected
     */
    Jewel(uint8_t pin,
        uint8_t numberOfPixels = NUMBER_OF_PIXELS_PER_JEWEL,
        neoPixelType type = NEO_GRBW + NEO_KHZ800)
    :
        _numberOfPixels(numberOfPixels)
    {
        _pixels = Adafruit_NeoPixel(numberOfPixels, pin, type);
        _pixels.begin();

        // Set the brightness to the max
        _pixels.setBrightness(255);

        // Shut down every LEDs
        _pixels.show();
    }

    /**
     * Set the colors of a specific pixel.
     * @param pixelNumber The pixel to apply the color.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelColor(uint8_t pixelNumber, uint64_t pixelColor)
    {
        uint8_t red = pixelColor >> 24;
        uint8_t green = pixelColor >> 16;
        uint8_t blue = pixelColor >> 8;
        uint8_t white = pixelColor >> 0;

        setPixelColor(pixelNumber, red, green, blue, white);
    }

    /**
     * Set the colors of a specific pixel.
     * @param pixelNumber The pixel to apply the color.
     * @param red The intensity of red for the color (between 0 and 255).
     * @param green The intensity of green for the color (between 0 and 255).
     * @param blue The intensity of blue for the color (between 0 and 255).
     * @param white The intensity of white for the color (between 0 and 255).
     */
    void setPixelColor(uint8_t pixelNumber, uint8_t red, uint8_t green,  uint8_t blue, uint8_t white)
    {
        _pixels.setPixelColor(pixelNumber, red, green, blue, white);
        _pixels.show();
    }

    /**
     * Set the colors for all pixels.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelsColor(uint64_t pixelColor)
    {
        uint8_t red = pixelColor >> 24;
        uint8_t green = pixelColor >> 16;
        uint8_t blue = pixelColor >> 8;
        uint8_t white = pixelColor >> 0;

        setPixelsColor(red, green, blue, white);
    }

    /**
     * Set the colors for all pixels.
     * @param red The intensity of red for the color (between 0 and 255).
     * @param green The intensity of green for the color (between 0 and 255).
     * @param blue The intensity of blue for the color (between 0 and 255).
     * @param white The intensity of white for the color (between 0 and 255).
     */
    void setPixelsColor(uint8_t red, uint8_t green,  uint8_t blue, uint8_t white)
    {
        for (uint8_t pixelNumber = 0; pixelNumber < _numberOfPixels; ++pixelNumber)
        {
            setPixelColor(pixelNumber, red, green, blue, white);
        }
    }

    uint8_t numberOfPixels() {
      return _numberOfPixels;
    }

protected:

    //! The number of NeoPixels.
    uint8_t _numberOfPixels;

    //! The NeoPixel's object.
    Adafruit_NeoPixel _pixels;

};

const uint8_t Jewel::NUMBER_OF_PIXELS_PER_JEWEL = 7;

#endif // JEWEL_H
