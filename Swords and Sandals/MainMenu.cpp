#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(sf::Texture& backgroundTexture, std::unordered_map<std::string, Button>& buttons) : PlaceInterface(backgroundTexture, buttons) {
    firstRun = true;
}

void MainMenu::setUpPositionOfButtons() {
    std::unordered_map<std::string, Button>& buttons = getButtons();
    
    if (buttons.find("mainMenuLogo") != buttons.end()) {
        buttons.at("mainMenuLogo").setPosition(sf::Vector2f(20.0f, 80.0f));
    }

    if (buttons.find("continue") != buttons.end()) {
        if (!firstRun) {
            buttons.at("continue").setPosition(sf::Vector2f(100.0f, 400.0f));
        }
        else {
            buttons.at("continue").setPosition(sf::Vector2f(-100.0f, -100.0f));
        }
    }

    if (buttons.find("newGame") != buttons.end()) {
        buttons.at("newGame").setPosition(sf::Vector2f(100.0f, 500.0f));
    }

    if (buttons.find("loadGame") != buttons.end()) {
        buttons.at("loadGame").setPosition(sf::Vector2f(100.0f, 600.0f));
    }

    if (buttons.find("settings") != buttons.end()) {
        buttons.at("settings").setPosition(sf::Vector2f(100.0f, 700.0f));
    }

    if (buttons.find("quit") != buttons.end()) {
        buttons.at("quit").setPosition(sf::Vector2f(100.0f, 800.0f));
    }
}

void MainMenu::checkForClickedButton(const sf::Vector2f& mousePosition, Player& player, Enemy& enemy, GameState& gameState, TextureManager& textureManager, Shop& shop) {
    for (auto& pair : getButtons()) {
        const std::string& buttonName = pair.first;
        Button& button = pair.second;

        if (button.isClicked(mousePosition)) {
            handleButtonClick(buttonName, player, enemy, gameState, textureManager, shop);
            SoundManager::playUIButton();
            break;
        }
    }
}

void MainMenu::handleButtonClick(const std::string& buttonName, Player& player, Enemy& enemy, GameState& gameState, TextureManager& textureManager, Shop& shop) {
    if (buttonName.find("continue") != std::string::npos) {
        gameState.setMode(gameState.getPreviousMode());
    }
    else if (buttonName.find("newGame") != std::string::npos) {
        player.resetStatsAndEq();
        enemy.resetStatsAndEq();
        shop.resetBoughtItems();
        player.setGold(300);
        player.resetRoundsWin();
        gameState.setMode(GameState::GameMode::InCreationMenu);

        firstRun = false;
    }
    else if (buttonName.find("loadGame") != std::string::npos) {
        SaveManager::loadCharacterStatsFromFile(player);
        SaveManager::loadBoughtItemsFromFile(shop);
        SaveManager::loadEquipedItemsFromFile(shop, player, true);
        SaveManager::loadEquipedItemsFromFile(shop, enemy, false);
        SaveManager::loadEnemyStatsFromFile(enemy);

        gameState.setMode(GameState::GameMode::InCity);

        firstRun = false;
    }
    else if (buttonName.find("settings") != std::string::npos) {
        gameState.setMode(GameState::GameMode::InSettings, false);
    }
    else if (buttonName.find("quit") != std::string::npos) {
        exit(0);
    }
}