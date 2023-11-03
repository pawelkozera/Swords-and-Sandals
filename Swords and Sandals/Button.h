#pragma once

#include "Object.h"

class Button : public Object
{
private:
public:
	Button();
	Button(const sf::Texture& texture);
	const bool isClicked(const sf::Vector2f& mousePosition) const;
};

