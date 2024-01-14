#include "KeyboardInput.h"

KeyboardInput::KeyboardInput() {
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        keyState[i] = false;
    }
}

void KeyboardInput::update(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        keyState[event.key.code] = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        keyState[event.key.code] = false;
    }
}

bool KeyboardInput::isKeyPressed(sf::Keyboard::Key key) const {
    return keyState[key];
}