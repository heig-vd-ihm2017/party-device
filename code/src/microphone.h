/*
https://learn.adafruit.com/adafruit-agc-electret-microphone-amplifier-max9814
https://learn.adafruit.com/adafruit-microphone-amplifier-breakout
*/

#ifndef Microphone_H
#define Microphone_H

/**
 * GainControl This specify which is the current applied gain for the microphone.
 * There are three gain control settings:
 *   - UNCONNECTED: Gain pin (Gain) is not connected to any other pins. Uncompressed gain set to 60dB.
 *   - GRD:         Gain pin (Gain) is connected to the ground pin (GRD). Gain set to 50dB.
 *   - VDD:         Gain pin (Gain) is connected to the power supply pin (Vdd). Gain set to 40dB.
 */
enum class GainControl : uint8_t { UNCONNECTED, GND, VDD };

/**
 * AttackReleaseRatio This specify which is the current applied attack and release ratio for the microphone.
 * There are three gain's levels:
 *   - UNCONNECTED: Attack and release pin (AR) is not connected to any other pins. Attack/Release Ratio is 1:4000.
 *   - VDD:         Attack and release pin (AR) is connected to the power supply pin (Vdd). Attack/Release Ratio is 1:2000.
 *   - GRD:         Attack and release pin (AR) is connected to the ground pin (GRD). Attack/Release Ratio is 1:500.
 */
enum class AttackReleaseRatio : uint8_t { UNCONNECTED, VDD, GND };

class Microphone {

public:

    /**
     * Microphone Constructor.
     * @param pin The pin number on which the microphone is connected.
     * @param sampleWindow The sample window width in milliseconds (50 mS = 20Hz).
     * @param gainControl The applied gain control for the microphone.
     * @param attackReleaseRatio The applied attack/release ratio for the microphone.
     */
    Microphone(uint8_t pin, uint8_t sampleWindow = 50, GainControl gainControl = GainControl::UNCONNECTED, AttackReleaseRatio attackReleaseRatio = AttackReleaseRatio::UNCONNECTED) :
        pin(pin),
        sampleWindow(sampleWindow),
        gainControl(gainControl),
        attackReleaseRatio(attackReleaseRatio)
    {

    }

    /**
     * soundLevel Get the sound level from the microphone.
     * @return The sound level between 0 and 255.
     */
    uint16_t soundLevel()
    {
        uint16_t sample;

        uint16_t peakToPeak = 0;
        uint16_t signalMax = 0;
        uint16_t signalMin = 1024;

        uint32_t startChorno = millis();

        while (millis() - startChorno < sampleWindow)
        {
            sample = analogRead(pin);

            // Toss out spurious readings
            if (sample < 1024)
            {
                if (sample > signalMax)
                {
                    // Save just the max levels
                    signalMax = sample;
                }
                else if (sample < signalMin)
                {
                    // Save just the min levels
                    signalMin = sample;
                }
            }
        }

        peakToPeak = signalMax - signalMin;

        return map(peakToPeak, 0, 1023, 0, 255);
    }

protected:

    //! The pin used to access the microphone.
    uint8_t pin;

    //! The sample window to listen to sound.
    uint8_t sampleWindow;

    //! The current applied gain control for the microphone.
    GainControl gainControl;

    //! The current applied attack/release ratio for the microphone.
    AttackReleaseRatio attackReleaseRatio;

};

#endif // Microphone_H
