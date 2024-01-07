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
        InArenaEntrance,
        InCreationMenu,
        InSettings,
    };

    GameState();
    void setMode(GameMode mode);
    GameMode getMode() const;
    bool isMainMenu() const;
    bool isInCity() const;
    bool InWeaponsmithShop() const;
    bool InArmorerShop() const;
    bool InArena() const;
    bool InArenaEntrance() const;
    bool InCreationMenu() const;
    bool InMainMenu() const;
    bool InSettings() const;

private:
    GameMode currentMode;
};

