#ifndef MODELOADER_H
#define MODELOADER_H

#include "Modes.h"
#include "Jewel.h"

class ModeLoader {
public:
  ModeLoader(uint8_t numberOfModes, Jewel* jewel) :
    jewel(jewel),
    _numberOfModes(numberOfModes),
    _index(0),
    _tail(0)
  {
    modes = (Mode**) malloc(numberOfModes * sizeof(Mode*));
    for (uint8_t i = 0; i < numberOfModes; ++i) {
      modes[i] = NULL;
    }
  }

  /**
    Add a Mode to the array of modes, given the array isn't full yet.
    Does nothing if the array is already full.
  */
  virtual void addMode(Mode* mode) {
    if (_tail < _numberOfModes) {
      modes[_tail++] = mode;
    }
  }

  /**
    Finds the next mode in the array.
  */
  virtual void loadNextMode() {
    uint8_t startIndex = _index;

    // Go forward in the array until we have looped or until the next mode is found
    do {
      _index = _index + 1 % _numberOfModes;
    } while (modes[_index] == NULL && _index != startIndex);
  }

  virtual void runMode() {
    //modes[_index]->apply();
    if (modes[_index] != NULL) {
      modes[_index]->apply();
      //jewel->setPixelsColor(5, 0, 0, 0);

    }
  }

  virtual ~ModeLoader() {
    free(modes);
  }

private:
  uint8_t _numberOfModes;
  uint8_t _index;

  // The index in the array where to add the next mode
  uint8_t _tail;
  Mode** modes;

  Jewel* jewel;
};

#endif
