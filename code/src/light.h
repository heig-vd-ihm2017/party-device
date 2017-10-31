/*
https://learn.adafruit.com/adafruit-neopixel-uberguide
https://learn.adafruit.com/jewel-hair-stick/arduino-code
*/

#ifndef LIGHT_H
#define LIGHT_H

#include <Adafruit_NeoPixel.h>

class Light {

public:

    /**
     * Light Constructor.
     * @param pin The pin number on which the NeoPixel is connected.
     * @param numberOfPixels The number of NeoPixels connected
     */
    Light(uint8_t pin, uint16_t numberOfNeoPixels, neoPixelType type = NEO_GRBW + NEO_KHZ800) :
        numberOfNeoPixels(numberOfNeoPixels)
    {
        pixels = Adafruit_NeoPixel(numberOfNeoPixels, pin, type);
        pixels.begin();

        // Set the brightness to the max
        pixels.setBrightness(255);

        // Shut down every LEDs
        pixels.show();
    }

    /**
     * Set the colors of a specific pixel.
     * @param pixelNumber The pixel to apply the color.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelColor(uint16_t pixelNumber, uint64_t pixelColor)
    {
        uint16_t red = pixelColor >> 24;
        uint16_t green = pixelColor >> 16;
        uint16_t blue = pixelColor >> 8;
        uint16_t white = pixelColor >> 0;

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
    void setPixelColor(uint16_t pixelNumber, uint8_t red, uint8_t green,  uint8_t blue, uint8_t white)
    {
        pixels.setPixelColor(pixelNumber, red, green, blue, white);
        pixels.show();
    }

    /**
     * Set the colors for all pixels.
     * @param pixelColor The color represented in hexadecimal.
     */
    void setPixelsColor(uint64_t pixelColor)
    {
        uint16_t red = pixelColor >> 24;
        uint16_t green = pixelColor >> 16;
        uint16_t blue = pixelColor >> 8;
        uint16_t white = pixelColor >> 0;

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
        for (uint8_t pixelNumber = 0; pixelNumber < numberOfNeoPixels; pixelNumber++)
        {
            setPixelColor(pixelNumber, red, green, blue, white);
        }
    }

protected:

    //! The number of NeoPixels.
    uint16_t numberOfNeoPixels;

    //! The NeoPixel's object.
    Adafruit_NeoPixel pixels;

};

#endif // LIGHT_H
