#ifndef MODELOADER_H
#define MODELOADER_H

#include "Modes.h"

class ModeController {
public:
  ModeController(Mode* modes[], uint8_t numberOfModes) :
    _numberOfModes(numberOfModes),
    _index(0)
  {
      _modes = modes;
  }

  /**
    Finds the next mode in the array.
  */
  virtual void loadNextMode() {
      _index = ++_index % _numberOfModes;
  }

  virtual void runMode() {
      _modes[_index]->apply();
  }

private:
  //! The available modes to use.
  Mode** _modes;

  //! The number of modes currently available.
  uint8_t _numberOfModes;

  //! Index of the current mode
  uint8_t _index;
};

#endif
