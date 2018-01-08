#ifndef FIXEDRATERYTHMGAME_H
#define FIXEDRATERYTHMGAME_H

#include <Metro.h>

#include "Jewel.h"
#include "MAX9814.h"

/*
  The tempo variable represents whether we are inside the "tempo period", aka
  the period of time when the central LED is turned on.
*/
bool tempo = false;

/*
  The rythm variable represents whether or not the user is in rythm, meaning
  if he makes sounds when the central LED is turned on, and doesn't make sound when
  the central led is turned off.
*/
bool rythm = false;

// Timer to manage tempo
Metro metroTempo(1000);

// Timer to manage the amount of time the central LED is turned on
Metro metroDisplayTime(400);

/**
  Set the other LEDs to green (success = true) or red (success = false)
*/
void setRythmLedColor(JewelStripe* jewelStripe, bool success);

/**
  This mode is a fixed rate rythm game. The mode turns the central LED
  on and off following a fixed rate tempo. IF the player makes a sound loud enough
  when the LED is on, he is in rythm. If he misses the beat or makes sound when the
  LED is off, he is off-rythm.
*/
void fixedRateRythmGame(JewelStripe* jewelStripe, MAX9814* mic) {

  // Show the tempo to follow
  if (metroTempo.check()) {
    // Turn the central led on
    jewelStripe->setPixelColor(0, 5, 5, 5, 0);

    // Reset the timer of display time
    metroDisplayTime.reset();

    // We are in the period of time the LED is on
    tempo = true;

    // The player is not in rythm yet
    rythm = false;
  } else if (metroDisplayTime.check()) {
    // The LED display time has ended, turn it off
    jewelStripe->setPixelColor(0, 0, 0, 0, 0);

    // We are no longer in the tempo time period
    tempo = false;
  }

  // If we are in the tempo period
  if (tempo) {
    // ... and we have not yet detected that the player is in rythm
    if (!rythm) {
      // Listen to the mic, and determine if the player made a noise
      uint16_t soundLevel = mic->soundLevel();
      rythm = soundLevel > 50;
    }
  } else {
    // If we are not in the tempo period, and the user makes a sound, he is off-rythm
    uint16_t soundLevel = mic->soundLevel();
    if (soundLevel > 50) {
      rythm = false;
    }
  }

  // Set the color of the other LEDs according to the rythm
  if (rythm) {
    setRythmLedColor(jewelStripe, true);
  } else if (!tempo && !rythm) {
    setRythmLedColor(jewelStripe, false);
  }
}

void setRythmLedColor(JewelStripe* jewelStripe, bool success) {
  uint16_t N = jewelStripe->numberOfPixels();
  for (uint16_t i = 1; i < N; ++i) {
    if (success) {
      jewelStripe->setPixelColor(i, 0, 5, 0, 0);
    } else {
      jewelStripe->setPixelColor(i, 5, 0, 0, 0);
    }
  }
}

#endif // FIXEDRATERYTHMGAME_H
