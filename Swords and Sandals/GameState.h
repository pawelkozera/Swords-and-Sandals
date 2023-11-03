#pragma once

class GameState
{
private:
    enum class GameMode {
        MainMenu,
        InCity,
        InWeaponsmithShop,
        InArmorerShop,
        InArena,
    };

    GameMode currentMode;
public:
    GameState();
    void setMode(GameMode mode);
    GameMode getMode() const;
    bool isMainMenu() const;
    bool isInCity() const;
    bool InWeaponsmithShop() const;
    bool InArmorerShop() const;
    bool InArena() const;
};

