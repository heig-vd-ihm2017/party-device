#ifndef MODEFIXEDRATERYTHMGAME_H
#define MODEFIXEDRATERYTHMGAME_H

#include "Jewel.h"
#include "MAX9814.h"
#include "Metro.h"

const uint8_t START_SHOW = 0, // Display the rythm four times
        SHOW = 1,
        START_LISTEN = 2,
        LISTEN = 3, // Listen for the mic
        RESULT = 4; // Show the result

uint8_t state = START_SHOW;

uint8_t numberOfShows = 0;

bool rythm = false;

Metro metro = Metro(1000);

void modeFixedRateRythmeGame(Jewel* jewel, MAX9814* mic) {


  switch(state) {
    case START_SHOW:
      metro.interval(1000);
      metro.reset();
      state = SHOW;
      break;

    case SHOW:

      // Condition to change state
      if (numberOfShows >= 4) {
        numberOfShows = 0;
        state = START_LISTEN;
        return;
      }

      // Show the rythm
      if (metro.check()) {
        jewel->setPixelsColor(5, 5, 5, 0);
        numberOfShows += 1;
      } else {
        jewel->setPixelsColor(0, 0, 0, 0);
      }

      break;

    case START_LISTEN:
      metro.interval(200);
      metro.reset();
      rythm = false;
      state = LISTEN;
      break;

    case LISTEN:
      if (!metro.check()) {
        uint16_t soundLevel = mic->soundLevel();
        if (soundLevel > 100) {
          rythm = true;
          jewel->setPixelsColor(0, 5, 0, 0);
        }
      } else {
        state = RESULT;
      }
      break;

    case RESULT:
      if (!rythm) {
        jewel->setPixelsColor(5, 0, 0, 0);
      }
      state = START_LISTEN;
      break;
  }
}

#endif
