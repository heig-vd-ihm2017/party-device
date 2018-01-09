#ifndef MODE_H
#define MODE_H

#include "io/JewelStripe.h"
#include "io/MAX9814.h"

class Mode {
public:
    virtual void apply() = 0;
    virtual ~Mode() {};
};

#endif // MODE_H
