#include "GameManager.h"

GameManager::GameManager(TextureManager &textureManager) : textureManager(textureManager) {
    window.create(sf::VideoMode(1024, 900), "Swords and Sandals");

    buttonHandlers["backButton"] = [this]() {
        gameState.setMode(GameState::GameMode::InCity);
        shop.setMode(Shop::ShopMode::Nothing);
        shop.setSelectedArmorPiece(nullptr);
        shop.setSelectedWeapon(nullptr);
        shop.hideButtons();
        };
    buttonHandlers["buyButton"] = [this]() {
        shop.buyItem();
        };
    buttonHandlers["equipButton"] = [this]() {
        shop.equipItem();
        };
    buttonHandlers["unequipButton"] = [this]() {
        shop.equipItem();
        };
    buttonHandlers["helmetButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Head);
        };
    buttonHandlers["chestButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Chest);
        };
    buttonHandlers["shoulderButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Shoulder);
        };
    buttonHandlers["forearmButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Elbow);
        };
    buttonHandlers["armButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Arm);
        };
    buttonHandlers["pantsButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Pelvis);
        };
    buttonHandlers["thighButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Thigh);
        };
    buttonHandlers["calfButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Leg);
        };
    buttonHandlers["feetButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Foot);
        };
    buttonHandlers["swordButton"] = [this]() {
        shop.setMode(Shop::ShopMode::Sword);
        };
}
#include <iostream>
void GameManager::run() {
    setUp();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            keyboard.update(event);
        }

        window.clear();

        handleEvents();

        cursor.update();
        cursor.render();

        window.display();

        sf::Time elapsedTime = clock.restart();
        sf::sleep(timePerFrame - elapsedTime);

        if (keyboard.isKeyPressed(sf::Keyboard::Escape)) {
            gameState.setMode(GameState::GameMode::MainMenu);
        }
    }
}

void GameManager::setUp() {
    std::unordered_map<std::string, CharacterPart> characterPartsMap = createCharacterPartsMap();
    std::unordered_map<std::string, Button> cityCenterButtons = createCityCenterButtonsMap();
    std::unordered_map<std::string, Button> arenaButtons = createArenaButtonsMap();
    std::unordered_map<std::string, Button> arenaEntranceButtons = createArenaEntranceButtonsMap();
    std::unordered_map<std::string, Button> shopButtons = createShopButtonsMap();
    std::unordered_map<std::string, Button> playerCreationButtons = createPlayerCreationButtonsMap();
    std::unordered_map<std::string, Button> mainMenuButtons = createMainMenuButtonsMap();
    std::unordered_map<std::string, Button> settingsButtons = createSettingsButtonsMap();

    mainMenu = MainMenu(textureManager.getTexture("mainMenuBackground"), mainMenuButtons);

    enemy = Enemy(characterPartsMap);
    enemy.assembleBody();
    enemy.updateArmorAndWeaponPositions();
    enemy.setBodyPosition(sf::Vector2f(920, 630));

    player = Player(characterPartsMap);
    player.assembleBody();
    player.updateArmorAndWeaponPositions();

    playerInterface = PlayerInterface(textureManager.getTexture("coinIcon"));

    cityCenter = CityCenter(textureManager.getTexture("cityCenter"), cityCenterButtons);

    arena = Arena(textureManager.getTexture("arena"), arenaButtons);

    arenaEntrance = ArenaEntrance(textureManager.getTexture("arenaEntrance"), arenaEntranceButtons);

    shop = Shop(shopButtons, textureManager, &player);

    cityCenter.setUpPositionOfButtons();
    shop.setUpPositionOfButtons();
    arena.setUpPositionOfButtons(player);
    arenaEntrance.setUpPositionOfButtons();

    playerCreation = PlayerCreation(textureManager.getTexture("playerCreationBackground"), playerCreationButtons);
    playerCreation.setUpPositionOfButtons();

    settings = Settings(textureManager.getTexture("settingsBackground"), settingsButtons);
    settings.setUpPositionOfButtons();

    SoundManager::setUp();

    gameState = GameState();

    keyboard = KeyboardInput();

    cursor = Cursor(textureManager.getTexture("cursor"), window);
}

void GameManager::handleEvents() {
    switch (gameState.getMode()) {
    case GameState::GameMode::MainMenu:
        handleMainMenuEvents();
        break;
    case GameState::GameMode::InCity:
        cityCenter.displayBackground(window);
        playerInterface.displayInterface(window, player);
        cityCenter.displayButtons(window);
        handleCityCenterButtons();
        break;
    case GameState::GameMode::InWeaponsmithShop:
        handleShopEvents();
        playerInterface.displayInterface(window, player);
        break;
    case GameState::GameMode::InArmorerShop:
        handleShopEvents();
        playerInterface.displayInterface(window, player);
        break;
    case GameState::GameMode::InArena:
        handleArenaEvents();
        playerInterface.displayInterface(window, player);
        break;
    case GameState::GameMode::InArenaEntrance:
        handleArenaEntranceEvents();
        break;
    case GameState::GameMode::InCreationMenu:
        handlePlayerCreationEvents();
        break;
    case GameState::GameMode::InSettings:
        handleSettingsEvents();
        break;
    default:
        break;
    }
}

void GameManager::handleMainMenuEvents() {
    mainMenu.displayBackground(window);
    mainMenu.setUpPositionOfButtons();
    mainMenu.displayButtons(window);
    mainMenu.checkForClickedButton(cursor.getPosition(), player, enemy, gameState, textureManager, shop);
}

void GameManager::handleShopEvents() {
    if (shop.getAreButtonsHidden()) {
        shop.setUpPositionOfButtons();
    }

    shop.displayBackground(window);
    shop.displayInterface(window);
    shop.displayButtons(window);
    shop.displayItems(window);
    handleShopButtons();
    shop.checkForClickedItems(cursor.getPosition(), player);
    shop.displayStatsOfSelectedItem(window);
    
    player.updateArmorAndWeaponPositions();
    player.display(window);
}

void GameManager::handleArenaEvents() {
    arena.displayBackground(window);

    arena.checkForEndOfFight(player, enemy);

    if (!arena.getFightInProgress()) {
        arena.displayEndOfFight(window);
    }

    if (player.getAnimationRunning()) {
        player.resetAnimation();
    }

    if (enemy.getAnimationRunning()) {
        enemy.resetAnimation();
    }

    if (arena.getPlayerTurn()) {
        arena.checkForClickedButton(cursor.getPosition(), player, enemy, gameState, textureManager, shop);

        if (!player.getAnimationRunning()) arena.displayButtons(window);
    }
    else {
        if (arena.getFightInProgress()) {
            arena.handleEnemyMove(enemy, player);
        }
    }

    if (!arena.getPlayerTurn()) {
        enemy.display(window);
        player.display(window);
    }
    else {
        player.display(window);
        enemy.display(window);
    }
}

void GameManager::handleArenaEntranceEvents() {
    arenaEntrance.displayBackground(window);
    arenaEntrance.displayButtons(window);
    arenaEntrance.displayInterface(window, player, enemy);
    arenaEntrance.checkForClickedButton(cursor.getPosition(), gameState, player, enemy, arena);
}

void GameManager::handlePlayerCreationEvents() {
    playerCreation.displayBackground(window);
    playerCreation.displayInterface(window, player);
    playerCreation.displayButtons(window);
    playerCreation.checkForClickedButton(cursor.getPosition(), player, gameState);
}

void GameManager::handleSettingsEvents() {
    settings.displayBackground(window);
    settings.displayInterface(window);
    settings.displayButtons(window);
    settings.checkForClickedButton(cursor.getPosition(), gameState);
}

void GameManager::handleCityCenterButtons() {
    if (cityCenter.getButton("arena").isClicked(cursor.getPosition())) {
        arena.setUpPositionOfButtons(player);
        gameState.setMode(GameState::GameMode::InArenaEntrance);
        SoundManager::playUIButton();
    }
    else if (cityCenter.getButton("armorer").isClicked(cursor.getPosition())) {
        player.setBodyPosition(sf::Vector2f(800, 600));
        gameState.setMode(GameState::GameMode::InArmorerShop);
        shop.setShopToArmorer(true);
        shop.setUpPositionOfIconButtons();
        SoundManager::playUIButton();
    }
    else if (cityCenter.getButton("weaponsmith").isClicked(cursor.getPosition())) {
        player.setBodyPosition(sf::Vector2f(800, 600));
        gameState.setMode(GameState::GameMode::InWeaponsmithShop);
        shop.setShopToArmorer(false);
        shop.setUpPositionOfIconButtons();
        SoundManager::playUIButton();
    }
    else if (cityCenter.getButton("characterCreation").isClicked(cursor.getPosition())) {
        gameState.setMode(GameState::GameMode::InCreationMenu);
        SoundManager::playUIButton();
    }
}

void GameManager::handleShopButtons() {
    for (const auto& pair : shop.getButtons()) {
        const std::string& buttonName = pair.first;
        const Button& button = pair.second;

        if (button.isClicked(cursor.getPosition())) {
            if (buttonHandlers.find(buttonName) != buttonHandlers.end()) {
                buttonHandlers[buttonName]();
                shop.setUpItemsPosition();
                SoundManager::playUIButton();
                break;
            }
        }
    }
}

std::unordered_map<std::string, CharacterPart> GameManager::createCharacterPartsMap() {
    std::unordered_map<std::string, CharacterPart> characterPartsMap;

    CharacterPart characterPartHead(textureManager.getTexture("head"));
    CharacterPart characterPartChest(textureManager.getTexture("chest"));
    CharacterPart characterPartShoulder(textureManager.getTexture("shoulder"));
    CharacterPart characterPartElbow(textureManager.getTexture("elbow"));
    CharacterPart characterPartArm(textureManager.getTexture("arm"));
    CharacterPart characterPartPelvis(textureManager.getTexture("pelvis"));
    CharacterPart characterPartThigh(textureManager.getTexture("thigh"));
    CharacterPart characterPartLeg(textureManager.getTexture("leg"));
    CharacterPart characterPartFoot(textureManager.getTexture("foot"));

    characterPartsMap.insert_or_assign("head", characterPartHead);
    characterPartsMap.insert_or_assign("chest", characterPartChest);
    characterPartsMap.insert_or_assign("shoulderLeft", characterPartShoulder);
    characterPartShoulder.flipSprite();
    characterPartsMap.insert_or_assign("shoulderRight", characterPartShoulder);
    characterPartsMap.insert_or_assign("elbowLeft", characterPartElbow);
    characterPartElbow.flipSprite();
    characterPartsMap.insert_or_assign("elbowRight", characterPartElbow);
    characterPartsMap.insert_or_assign("armLeft", characterPartArm);
    characterPartArm.flipSprite();
    characterPartsMap.insert_or_assign("armRight", characterPartArm);
    characterPartsMap.insert_or_assign("pelvis", characterPartPelvis);
    characterPartsMap.insert_or_assign("thighLeft", characterPartThigh);
    characterPartThigh.flipSprite();
    characterPartsMap.insert_or_assign("thighRight", characterPartThigh);
    characterPartsMap.insert_or_assign("legLeft", characterPartLeg);
    characterPartLeg.flipSprite();
    characterPartsMap.insert_or_assign("legRight", characterPartLeg);
    characterPartsMap.insert_or_assign("footLeft", characterPartFoot);
    characterPartFoot.flipSprite();
    characterPartsMap.insert_or_assign("footRight", characterPartFoot);

    return characterPartsMap;
}

std::unordered_map<std::string, Button> GameManager::createCityCenterButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button arenaButton(textureManager.getTexture("arenaButton"));
    Button armorerButton(textureManager.getTexture("armorerButton"));
    Button weaponsmithButton(textureManager.getTexture("weaponsmithButton"));
    Button characterCreation(textureManager.getTexture("characterCreation"));

    Buttons.insert_or_assign("arena", arenaButton);
    Buttons.insert_or_assign("armorer", armorerButton);
    Buttons.insert_or_assign("weaponsmith", weaponsmithButton);
    Buttons.insert_or_assign("characterCreation", characterCreation);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createArenaButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button moveButtonForward(textureManager.getTexture("movePlayerForward"));
    Button movePlayerBackwards(textureManager.getTexture("movePlayerBackwards"));
    Button attackPlayer(textureManager.getTexture("attackPlayer"));
    Button restPlayer(textureManager.getTexture("restPlayer"));
    Button continueButton(textureManager.getTexture("continueButton"));
    Button startOverButton(textureManager.getTexture("startOverButton"));

    Buttons.insert_or_assign("movePlayerForward", moveButtonForward);
    Buttons.insert_or_assign("movePlayerBackwards", movePlayerBackwards);
    Buttons.insert_or_assign("attackPlayer", attackPlayer);
    Buttons.insert_or_assign("restPlayer", restPlayer);
    Buttons.insert_or_assign("continueButton", continueButton);
    Buttons.insert_or_assign("startOverButton", startOverButton);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createArenaEntranceButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button goToCityButton(textureManager.getTexture("goToCityButton"));
    Button fightButton(textureManager.getTexture("fightButton"));

    Buttons.insert_or_assign("goToCity", goToCityButton);
    Buttons.insert_or_assign("fight", fightButton);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createShopButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button backButton(textureManager.getTexture("backButton"));
    Button armButton(textureManager.getTexture("armIcon"));
    Button calfButton(textureManager.getTexture("calfIcon"));
    Button chestButton(textureManager.getTexture("chestIcon"));
    Button feetButton(textureManager.getTexture("feetIcon"));
    Button forearmButton(textureManager.getTexture("forearm_icon"));
    Button helmetButton(textureManager.getTexture("hemletIcon"));
    Button pantsButton(textureManager.getTexture("pantsIcon"));
    Button shoulderButton(textureManager.getTexture("shoulderIcon"));
    Button thighButton(textureManager.getTexture("thighIcon"));
    Button swordButton(textureManager.getTexture("swordIcon"));
    Button buyButton(textureManager.getTexture("buyButton"));
    Button equipButton(textureManager.getTexture("equipButton"));
    Button unequipButton(textureManager.getTexture("unequipButton"));

    Buttons.insert_or_assign("armButton", armButton);
    Buttons.insert_or_assign("calfButton", calfButton);
    Buttons.insert_or_assign("chestButton", chestButton);
    Buttons.insert_or_assign("feetButton", feetButton);
    Buttons.insert_or_assign("forearmButton", forearmButton);
    Buttons.insert_or_assign("helmetButton", helmetButton);
    Buttons.insert_or_assign("pantsButton", pantsButton);
    Buttons.insert_or_assign("shoulderButton", shoulderButton);
    Buttons.insert_or_assign("thighButton", thighButton);
    Buttons.insert_or_assign("swordButton", swordButton);

    for (auto& pair : Buttons) {
        Button& button = pair.second;
        button.setScale(0.15f, 0.15f);
    }

    Buttons.insert_or_assign("backButton", backButton);
    Buttons.insert_or_assign("buyButton", buyButton);
    Buttons.insert_or_assign("equipButton", equipButton);
    Buttons.insert_or_assign("unequipButton", unequipButton);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createPlayerCreationButtonsMap()
{
    std::unordered_map<std::string, Button> Buttons;

    Button plusButton(textureManager.getTexture("plusButton"));
    Button minusButton(textureManager.getTexture("minusButton"));
    Button goToCityButton(textureManager.getTexture("goToCityButton"));

    Buttons.insert_or_assign("plusStrengthButton", plusButton);
    Buttons.insert_or_assign("minusStrengthButton", minusButton);

    Buttons.insert_or_assign("plusAgilityButton", plusButton);
    Buttons.insert_or_assign("minusAgilityButton", minusButton);

    Buttons.insert_or_assign("plusAttackButton", plusButton);
    Buttons.insert_or_assign("minusAttackButton", minusButton);

    Buttons.insert_or_assign("plusDefenceButton", plusButton);
    Buttons.insert_or_assign("minusDefenceButton", minusButton);

    Buttons.insert_or_assign("plusVitalityButton", plusButton);
    Buttons.insert_or_assign("minusVitalityButton", minusButton);

    Buttons.insert_or_assign("plusCharismaButton", plusButton);
    Buttons.insert_or_assign("minusCharismaButton", minusButton);

    Buttons.insert_or_assign("plusStaminaButton", plusButton);
    Buttons.insert_or_assign("minusStaminaButton", minusButton);

    Buttons.insert_or_assign("goToCityButton", goToCityButton);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createMainMenuButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button continueButton(textureManager.getTexture("continueButton"));
    Button newGameButton(textureManager.getTexture("newGameButton"));
    Button loadGameButton(textureManager.getTexture("loadGameButton"));
    Button settingsButton(textureManager.getTexture("settingsButton"));
    Button quitButton(textureManager.getTexture("quitButton"));
    Button mainMenuLogoButton(textureManager.getTexture("mainMenuLogo"));

    Buttons.insert_or_assign("continue", continueButton);
    Buttons.insert_or_assign("newGame", newGameButton);
    Buttons.insert_or_assign("loadGame", loadGameButton);
    Buttons.insert_or_assign("settings", settingsButton);
    Buttons.insert_or_assign("quit", quitButton);
    Buttons.insert_or_assign("mainMenuLogo", mainMenuLogoButton);

    return Buttons;
}

std::unordered_map<std::string, Button> GameManager::createSettingsButtonsMap() {
    std::unordered_map<std::string, Button> Buttons;

    Button plusButton(textureManager.getTexture("plusButton"));
    Button minusButton(textureManager.getTexture("minusButton"));
    Button backButton(textureManager.getTexture("backButton"));

    Buttons.insert_or_assign("plusVolume", plusButton);
    Buttons.insert_or_assign("minusVolume", minusButton);
    Buttons.insert_or_assign("backButton", backButton);

    return Buttons;
}