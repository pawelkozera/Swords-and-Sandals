#pragma once

#include <SFML/Graphics.hpp>

class KeyboardInput
{
private:
	bool keyState[sf::Keyboard::KeyCount];
public:
	KeyboardInput();
	void update(sf::Event& event);
	bool isKeyPressed(sf::Keyboard::Key key) const;
};

