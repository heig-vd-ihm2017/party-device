/*
https://learn.adafruit.com/adafruit-agc-electret-microphone-amplifier-max9814
https://learn.adafruit.com/adafruit-microphone-amplifier-breakout
*/

#ifndef MAX9814_H
#define MAX9814_H

#include <Arduino.h>

#define SAMPLES     128
#define N_WAVE      256    /* full length of Sinewave[] */
#define LOG2_N_WAVE 8      /* log2(N_WAVE) */

/**
 * GainControl This specify which is the current applied gain for the microphone.
 * There are three gain control settings:
 *   - UNCONNECTED: Gain pin (Gain) is not connected to any other pins. Uncompressed gain set to 60dB.
 *   - GRD:         Gain pin (Gain) is connected to the ground pin (GRD). Gain set to 50dB.
 *   - VDD:         Gain pin (Gain) is connected to the power supply pin (Vdd). Gain set to 40dB.
 * This allows to reduce the gain if the sound is too loud and the microphone is satured.
 */
enum class GainControl : uint8_t { UNCONNECTED, GND, VDD };

/**
 * AttackReleaseRatio This specify which is the current applied attack and release ratio for the microphone.
 * There are three gain's levels:
 *   - UNCONNECTED: Attack and release pin (AR) is not connected to any other pins. Attack/Release Ratio is 1:4000.
 *   - VDD:         Attack and release pin (AR) is connected to the power supply pin (Vdd). Attack/Release Ratio is
 *                  1:2000.
 *   - GRD:         Attack and release pin (AR) is connected to the ground pin (GRD). Attack/Release Ratio is 1:500.
 * Use a short attack time to react quickly to transient signals or use a longer attack time to ignore short duration
 * peaks and the louder passages to be reduced in volume.
 */
enum class AttackReleaseRatio : uint8_t { UNCONNECTED, VDD, GND };

class MAX9814
{

public:

    /**
     * Microphone Constructor.
     * @param pin The pin number on which the microphone is connected.
     * @param sampleWindow The sample window width in milliseconds (50 mS = 20Hz).
     * @param gainControl The applied gain control for the microphone.
     * @param attackReleaseRatio The applied attack/release ratio for the microphone.
     */
    MAX9814(uint8_t pin,
        double samplingFrequency,
        GainControl gainControl = GainControl::UNCONNECTED,
        AttackReleaseRatio attackReleaseRatio = AttackReleaseRatio::UNCONNECTED)
    :
        pin(pin),
        samplingFrequency(samplingFrequency),
        gainControl(gainControl),
        attackReleaseRatio(attackReleaseRatio)
    {

    }

    //! Since we only use 3/4 of N_WAVE, we define only
    //! this many samples, in order to conserve data space.
    constexpr static int16_t Sinewave[] PROGMEM = {
        0, 3, 6, 9, 12, 15, 18, 21,
        24, 28, 31, 34, 37, 40, 43, 46,
        48, 51, 54, 57, 60, 63, 65, 68,
        71, 73, 76, 78, 81, 83, 85, 88,
        90, 92, 94, 96, 98, 100, 102, 104,
        106, 108, 109, 111, 112, 114, 115, 117,
        118, 119, 120, 121, 122, 123, 124, 124,
        125, 126, 126, 127, 127, 127, 127, 127,

        127, 127, 127, 127, 127, 127, 126, 126,
        125, 124, 124, 123, 122, 121, 120, 119,
        118, 117, 115, 114, 112, 111, 109, 108,
        106, 104, 102, 100, 98, 96, 94, 92,
        90, 88, 85, 83, 81, 78, 76, 73,
        71, 68, 65, 63, 60, 57, 54, 51,
        48, 46, 43, 40, 37, 34, 31, 28,
        24, 21, 18, 15, 12, 9, 6, 3,

        0, -3, -6, -9, -12, -15, -18, -21,
        -24, -28, -31, -34, -37, -40, -43, -46,
        -48, -51, -54, -57, -60, -63, -65, -68,
        -71, -73, -76, -78, -81, -83, -85, -88,
        -90, -92, -94, -96, -98, -100, -102, -104,
        -106, -108, -109, -111, -112, -114, -115, -117,
        -118, -119, -120, -121, -122, -123, -124, -124,
        -125, -126, -126, -127, -127, -127, -127, -127
    };

    /**
     * fix_fft() - perform forward/inverse fast Fourier transform.
     * vReal[n],vImag[n] are real and imaginary arrays, both INPUT AND
     * RESULT (in-place FFT), with 0 <= n < 2**m; set inverse to
     * 0 for forward transform (FFT), or 1 for iFFT.
     */
    void fft()
    {
        sample();

        int m, mr, nn, i, j, l, k, istep, n, shift;
        char qr, qi, tr, ti, wr, wi;

        m = (LOG2_N_WAVE - 1);

        n = 1 << m;

        mr = 0;
        nn = n - 1;

        // decimation in time - re-order data
        for (m = 1; m <= nn; ++m)
        {
            l = n;

            do
            {
                l >>= 1;
            }
            while (mr + l > nn);

            mr = (mr & (l - 1)) + l;

            if (mr <= m)
            {
                continue;
            }

            tr = vReal[m];
            vReal[m] = vReal[mr];
            vReal[mr] = tr;
            ti = vImag[m];
            vImag[m] = vImag[mr];
            vImag[mr] = ti;
        }

        l = 1;
        k = LOG2_N_WAVE - 1;

        while (l < n)
        {

            // fixed scaling, for proper normalization --
            // there will be log2(n) passes, so this results
            // in an overall factor of 1/n, distributed to
            // maximize arithmetic accuracy.
            shift = 1;

            // it may not be obvious, but the shift will be
            // performed on each data point exactly once,
            // during this pass.
            istep = l << 1;

            for (m = 0; m < l; ++m)
            {
                j = m << k;

                wr =  pgm_read_word_near(Sinewave + j+N_WAVE/4);

                wi = -pgm_read_word_near(Sinewave + j);

                if (shift)
                {
                    wr >>= 1;
                    wi >>= 1;
                }

                for (i = m; i < n; i += istep)
                {
                    j = i + l;

                    tr = scale16(wr, vReal[j]) - scale16(wi, vImag[j]);
                    ti = scale16(wr, vImag[j]) + scale16(wi, vReal[j]);

                    qr = vReal[i];
                    qi = vImag[i];

                    if (shift)
                    {
                        qr >>= 1;
                        qi >>= 1;
                    }

                    vReal[j] = qr - tr;
                    vImag[j] = qi - ti;
                    vReal[i] = qr + tr;
                    vImag[i] = qi + ti;
                }
            }

            --k;
            l = istep;
        }

        highestFreqPeak = 1;
        highFreqPeak = 1;
        mediumFreqPeak = 22;
        lowFreqPeak = 43;

        // Get the absolute value of the transformation
        for (uint8_t i = 0; i < SAMPLES / 2; ++i)
        {
            vReal[i] = sqrt(vReal[i] * vReal[i] + vImag[i] * vImag[i]);
        }

        for (uint8_t i = 1; i < SAMPLES / 2 - 1; ++i)
        {
            if (vReal[i + 1] > vReal[highestFreqPeak])
            {
                highestFreqPeak = i + 1;
            }

            if (i < 22 && vReal[i + 1] > vReal[highFreqPeak])
            {
                highFreqPeak = i + 1;
            }
            else if (i < 43 && vReal[i + 1] > vReal[mediumFreqPeak])
            {
                mediumFreqPeak = i + 1;
            }
            else if (i < 64 && vReal[i + 1] > vReal[lowFreqPeak])
            {
                lowFreqPeak = i + 1;
            }
        }
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

        while (millis() - startChorno < 20)
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

    uint16_t getPeakFrequency()
    {
        return highestFreqPeak;
    }

    uint16_t getHighFrequency()
    {
        int16_t difference = highestFreqPeak - highFreqPeak;

        return sqrt(difference * difference);
    }

    uint16_t getMediumFrequency()
    {
        int16_t difference = highestFreqPeak - mediumFreqPeak;

        return sqrt(difference * difference);
    }

    uint16_t getLowFrequency()
    {
        int16_t difference = highestFreqPeak - lowFreqPeak;

        return sqrt(difference * difference);
    }

protected:

    //! The pin used to access the microphone.
    uint8_t pin;

    //! Sampling frequency (Hz).
    double samplingFrequency;

    //! The current applied gain control for the microphone.
    GainControl gainControl;

    //! The current applied attack/release ratio for the microphone.
    AttackReleaseRatio attackReleaseRatio;

    //! The index peak of the highest frequency.
    uint8_t highestFreqPeak;

    //! The index peak of the frequency in the high area.
    uint8_t highFreqPeak;

    //! The index peak of the frequency in the medium area.
    uint8_t mediumFreqPeak;

    //! The index peak of the frequency in the low area.
    uint8_t lowFreqPeak;

    //! Real numbers input and output vector computed results from FFT
    int8_t vReal[SAMPLES];

    //! Real numbers input and output vector computed results from FFT
    int8_t vImag[SAMPLES];

    /**
     * Sample the sound.
     */
    void sample()
    {

        for (uint8_t i = 0; i < SAMPLES; ++i) {

            delay(1000 / samplingFrequency);

            uint16_t sample = analogRead(pin);

            if (gainControl == GainControl::UNCONNECTED) {
                sample = sample;
            } else if(gainControl == GainControl::GND) {
                sample = sample / 4 - 128;
            } else if(gainControl == GainControl::VDD) {
                sample = sample / 4 - 128;
            }

            vReal[i] = sample;
            vImag[i] = 0;
        }
    }

    /*
     * FIX_MPY() - fixed-point multiplication & scaling.
     * Substitute inline assembly for hardware-specific
     * optimization suited to a particluar DSP processor.
     * Scaling ensures that result remains 16-bit.
     */
    int8_t scale16(int8_t a, int8_t b)
    {
        // shift right one less bit (i.e. 15-1)
        int8_t c = (a * b) >> 6;

        // last bit shifted out = rounding-bit
        b = c & 0x01;

        // last shift + rounding bit
        a = (c >> 1) + b;

        return a;
    }



};

constexpr int16_t MAX9814::Sinewave[] PROGMEM;

#endif // MAX9814_H
