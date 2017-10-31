#include "light.h"
#include "microphone.h"

#define LED_PIN             1  // Pin on which the NeoPixel is connected (Gemma: D0)
#define MIC_PIN             1  // Pin on which the microphone is conncted (Gemma: D2/A1)

#define NUMBER_OF_PIXELS    7  // Number of pixels you are using

Light light = Light(LED_PIN, NUMBER_OF_PIXELS);
Microphone microphone = Microphone(MIC_PIN);

void setup()
{
}

void loop()
{
    int volume = microphone.soundLevel();

    if (volume <= 50)
    {
        light.setPixelsColor(20, 0, 0, 0);
    }
    else if (volume <= 100)
    {
        light.setPixelsColor(20, 20, 0, 0);
    }
    else if (volume <= 150)
    {
        light.setPixelsColor(0, 20, 20, 0);
    }
    else if (volume <= 200)
    {
        light.setPixelsColor(0, 0, 20, 20);
    }
    else if (volume <= 250)
    {
        light.setPixelsColor(20, 20, 20, 0);
    }
    else if (volume > 250)
    {
        light.setPixelsColor(20, 20, 20, 20);
    }
}
