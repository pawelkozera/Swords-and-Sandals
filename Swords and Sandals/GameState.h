#pragma once

class GameState
{
public:
    enum class GameMode {
        MainMenu,
        InCity,
        InWeaponsmithShop,
        InArmorerShop,
        InArena,
        InCreationMenu,
    };

    GameState();
    void setMode(GameMode mode);
    GameMode getMode() const;
    bool isMainMenu() const;
    bool isInCity() const;
    bool InWeaponsmithShop() const;
    bool InArmorerShop() const;
    bool InArena() const;
    bool InCreationMenu() const;

private:
    GameMode currentMode;
};

