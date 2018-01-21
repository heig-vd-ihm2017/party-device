#ifndef FIXEDRATERYTHMGAME_H
#define FIXEDRATERYTHMGAME_H

#include <Metro.h>
#include "modes/Mode.h"

class FixedRateRythmGame : public Mode {
public:
  FixedRateRythmGame(JewelStripe* stripe, MAX9814* mic) :
    _stripe(stripe),
    _mic(mic),
    _numberOfJewels(stripe->numberOfJewels()),
    _tempo(false),
    _rythm(false),
    _metroTempo(1000),
    _displayTime(400)
    {}

  /**
    This mode is a fixed rate rythm game. The mode turns the central LED
    on and off following a fixed rate tempo. IF the player makes a sound loud enough
    when the LED is on, he is in rythm. If he misses the beat or makes sound when the
    LED is off, he is off-rythm.
  */
  virtual void apply() {
    // Show the tempo to follow
    if (_metroTempo.check()) {

      // Turn the central led on on each Jewel
      for (uint8_t i = 1; i <= _numberOfJewels; ++i ) {
        _stripe->setPixelColorInJewel(i, 0, 5, 5, 5, 0);
      }

      // Reset the timer of display time
      _displayTime.reset();

      // We are in the period of time the LED is on
      _tempo = true;

      // The player is not in rythm yet
      _rythm = false;
    } else if (_displayTime.check()) {
      // The LED display time has ended, turn it off on every Jewel
      for (uint8_t i = 1; i <= _numberOfJewels; ++i ) {
        _stripe->setPixelColorInJewel(i, 0, 0, 0, 0, 0);
      }

      // We are no longer in the tempo time period
      _tempo = false;
    }

    // If we are in the tempo period
    if (_tempo) {
      // ... and we have not yet detected that the player is in rythm
      if (!_rythm) {
        // Listen to the mic, and determine if the player made a noise
        uint16_t soundLevel = _mic->soundLevel();
        _rythm = soundLevel > 50;
      }
    } else {
      // If we are not in the tempo period, and the user makes a sound, he is off-rythm
      uint16_t soundLevel = _mic->soundLevel();
      if (soundLevel > 50) {
        _rythm = false;
      }
    }

    // Set the color of the other LEDs according to the rythm
    if (_rythm) {
      this->setRythmLedColor(true);
    } else if (!_tempo && !_rythm) {
      this->setRythmLedColor(false);
    }
  }

  /**
    Set the other LEDs to green (success = true) or red (success = false)
  */
  virtual void setRythmLedColor(bool success) {
    // For every jewel in the stripe
    for (uint16_t j = 1; j <= _numberOfJewels; ++j ) {
      // Set all but the center pixel to the wanted color
      for (uint16_t i = 1; i < Jewel::NUMBER_OF_PIXELS_PER_JEWEL; ++i) {
        if (success) {
            _stripe->setPixelColorInJewel(j, i, 0, 5, 0, 0);
        } else {
            _stripe->setPixelColorInJewel(j, i, 5, 0, 0, 0);
        }
      }
    }
  }

private:
  JewelStripe* _stripe;
  MAX9814* _mic;
  const uint8_t _numberOfJewels;

  /*
    The tempo variable represents whether we are inside the "tempo period", aka
    the period of time when the central LED is turned on.
  */
  bool _tempo;

  /*
    The rythm variable represents whether or not the user is in rythm, meaning
    if he makes sounds when the central LED is turned on, and doesn't make sound when
    the central led is turned off.
  */
  bool _rythm;
  Metro _metroTempo;
  Metro _displayTime;
};



#endif // FIXEDRATERYTHMGAME_H
