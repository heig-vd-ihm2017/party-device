#ifndef MODEINTERFACE_H
#define MODEINTERFACE_H

class Mode {
public:
  virtual void apply() = 0;
  virtual ~Mode() {};
};

#endif
