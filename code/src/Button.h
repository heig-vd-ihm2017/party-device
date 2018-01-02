#include <EnableInterrupt.h>

class Button {

public:
    Button() : _hasBeenPressed(false) {
    }

    void pressed() {
        _hasBeenPressed = true;
    }

    bool hasBeenPressed() {
        if (_hasBeenPressed == true) {
            _hasBeenPressed = false;
            return true;
        }

        return false;
    }

private:
    bool _hasBeenPressed;
};
