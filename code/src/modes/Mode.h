#ifndef MODEINTERFACE_H
#define MODEINTERFACE_H

#include "io/JewelStripe.h"
#include "io/MAX9814.h"

class Mode {
public:
  virtual void apply() = 0;
  virtual ~Mode() {};
};

#endif
