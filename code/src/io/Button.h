#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    /**
     * Button Constructor.
     */
    Button() : _hasBeenPressed(false) {
        // Empty
    }

    /**
     * Method called when the button is pressed.
     */
    void pressed() {
        _hasBeenPressed = true;
    }

    /**
     * Check if the button has been pressed.
     */
    bool hasBeenPressed() {
        if (_hasBeenPressed) {
            _hasBeenPressed = false;
            return true;
        }

        return false;
    }

private:
    //! Keep the state of the button.
    bool _hasBeenPressed;
};

#endif // BUTTON_H
