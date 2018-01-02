#include "MAX9814.h"
#include "Jewel.h"

#define LED_PIN             1  // Pin on which the NeoPixel is connected (Gemma: D0)
#define MIC_PIN             1  // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_PIXELS 7 // Number of pixels you are using

Jewel jewel = Jewel(LED_PIN, NUMBER_OF_PIXELS);
MAX9814 mic = MAX9814(MIC_PIN);

void setup()
{

}

void loop()
{

}
