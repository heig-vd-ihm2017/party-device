#include <Arduino.h>

#include "MAX9814.h"
#include "Jewel.h"

#define LED_PIN             1  // Pin on which the NeoPixel is connected (Gemma: D0)
#define MIC_PIN             1  // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_PIXELS 7 // Number of pixels you are using

Jewel jewel = Jewel(LED_PIN, NUMBER_OF_PIXELS);
MAX9814 mic = MAX9814(MIC_PIN, 600);

void setup()
{
}

void loop()
{
    mic.fft();

    uint16_t peakFreq = mic.getPeakFrequency();
    uint16_t highFreq = mic.getHighFrequency();
    uint16_t mediumFreq = mic.getMediumFrequency();
    uint16_t lowFreq = mic.getLowFrequency();

    uint16_t red = map(highFreq, 0, 64, 255, 0);
    uint16_t blue = map(lowFreq, 0, 64, 255, 0);
    uint16_t green = map(mediumFreq, 0, 64, 255, 0);

    if (red > blue)
    {
        jewel.setPixelsColor(red, 0, 0, 0);
    }
    else
    {
        jewel.setPixelsColor(0, 0, blue, 0);
    }

}
