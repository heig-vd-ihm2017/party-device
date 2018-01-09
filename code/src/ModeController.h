#ifndef MODELOADER_H
#define MODELOADER_H

#include "modes/Mode.h"

class ModeController {
public:

    /**
     * ModeController constructor.
     */
    ModeController() :
        _numberOfModes(0),
        _currentMode(0)
    {
        // Empty
    }

  /**
   * Add the modes to the controller.
   */
  virtual void addModes(Mode* modes[], uint8_t numberOfModes) {
      _modes = modes;
      _numberOfModes = numberOfModes;
  }

  /**
   * Finds the next mode in the array.
   */
  virtual void loadNextMode() {
      uint8_t nextMode = ++_currentMode % _numberOfModes;
      _currentMode = nextMode;
  }

  /**
   * Run the mode.
   */
  virtual void runMode() {
      _modes[_currentMode]->apply();
  }

private:
  //! The available modes to use.
  Mode** _modes;

  //! The number of modes currently available.
  uint8_t _numberOfModes;

  //! Index of the current mode
  uint8_t _currentMode;
};

#endif
