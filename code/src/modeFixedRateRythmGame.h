#ifndef MODEFIXEDRATERYTHMGAME_H
#define MODEFIXEDRATERYTHMGAME_H

#include "Jewel.h"
#include "MAX9814.h"
#include "Metro.h"

bool tempo = false;
bool rythm = false;

Metro metroTempo(1000);
Metro metroDisplayTime(400);



void setRythmSuccess(Jewel* jewel, bool success) {
  uint16_t N = jewel->numberOfPixels();
  for (uint16_t i = 1; i < N; ++i) {
    if (success) {
      jewel->setPixelColor(i, 0, 5, 0, 0);
    } else {
      jewel->setPixelColor(i, 5, 0, 0, 0);
    }
  }
}

void modeFixedRateRythmeGame(Jewel* jewel, MAX9814* mic) {

  // Show the tempo to follow
  if (metroTempo.check()) {
    jewel->setPixelColor(0, 5, 5, 5, 0);
    metroDisplayTime.reset();
    tempo = true;
    rythm = false;
  } else if (metroDisplayTime.check()) {
    jewel->setPixelColor(0, 0, 0, 0, 0);
    tempo = false;
  }

  if (tempo) {
    if (!rythm) {
      uint16_t soundLevel = mic->soundLevel();
      rythm = soundLevel > 50;
    }
  } else {
    uint16_t soundLevel = mic->soundLevel();
    if (soundLevel > 50) {
      rythm = false;
    }
  }

  if (rythm) {
    setRythmSuccess(jewel, true);
  } else if (!tempo && !rythm) {
    setRythmSuccess(jewel, false);
  }


  // switch(state) {
  //   case START_SHOW:
  //     metro.interval(1000);
  //     metro.reset();
  //     state = SHOW;
  //     break;
  //
  //   case SHOW:
  //
  //     // Condition to change state
  //     if (numberOfShows >= 4) {
  //       numberOfShows = 0;
  //       state = START_LISTEN;
  //       return;
  //     }
  //
  //     // Show the rythm
  //     if (metro.check()) {
  //       jewel->setPixelsColor(5, 5, 5, 0);
  //       numberOfShows += 1;
  //     } else {
  //       jewel->setPixelsColor(0, 0, 0, 0);
  //     }
  //
  //     break;
  //
  //   case START_LISTEN:
  //     metro.interval(200);
  //     metro.reset();
  //     rythm = false;
  //     state = LISTEN;
  //     break;
  //
  //   case LISTEN:
  //     if (!metro.check()) {
  //       uint16_t soundLevel = mic->soundLevel();
  //       if (soundLevel > 100) {
  //         rythm = true;
  //         jewel->setPixelsColor(0, 5, 0, 0);
  //       }
  //     } else {
  //       state = RESULT;
  //     }
  //     break;
  //
  //   case RESULT:
  //     if (!rythm) {
  //       jewel->setPixelsColor(5, 0, 0, 0);
  //     }
  //     state = START_LISTEN;
  //     break;
  // }
}
#endif
