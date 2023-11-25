#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <unordered_map>

class PlaceInterface
{
private:
    sf::Sprite sprite;
    std::unordered_map<std::string, Button> buttons;
    bool areButtonsHidden;

public:
    PlaceInterface();
    PlaceInterface(sf::Texture& texture, std::unordered_map<std::string, Button>& buttons);
    const sf::Sprite getSprite() const;
    void setPosition(const sf::Vector2f position);
    void displayButtons(sf::RenderWindow& window);
    virtual void setUpPositionOfButtons();
    void hideButtons();
    void displayBackground(sf::RenderWindow& window);
    Button getButton(const std::string& buttonName);
    std::unordered_map<std::string, Button>& getButtons();
    void setSpriteTexture(sf::Texture &texture);
    const bool getAreButtonsHidden();
    void setButtonsHidden(bool buttonsHidden);
};

