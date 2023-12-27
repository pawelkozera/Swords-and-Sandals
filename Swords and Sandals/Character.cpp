#include "Character.h"

std::random_device Character::rd;

Character::Character()
{
}

Character::Character(std::unordered_map<std::string, CharacterPart> &characterParts)
	: characterParts(characterParts), 
    strength(1),
    agility(1),
    attack(1),
    defence(1),
    vitality(1),
    charisma(1),
    stamina(1),
    availablePoints(5),
    hp(10 + vitality*2),
    animationRunning(false)
{
    bodyPosition = sf::Vector2f(800.0f, 600.0f);

    std::mt19937 generator(rd());
}

void Character::assembleBody() {
    sf::Vector2f chestPosition = bodyPosition;

    sf::Vector2f headOffset(characterParts.at("chest").getSpriteRect().width / 8, -characterParts.at("head").getSpriteRect().height + 10.0f);
    sf::Vector2f shoulderLeftOffset(characterParts.at("shoulderLeft").getSpriteRect().width - 6.0f, characterParts.at("chest").getSpriteRect().height / -10);
    sf::Vector2f shoulderRightOffset(characterParts.at("chest").getSpriteRect().width + characterParts.at("shoulderRight").getSpriteRect().width - 6.0f, characterParts.at("chest").getSpriteRect().height / 10);
    sf::Vector2f elbowLeftOffset(0.0f, characterParts.at("shoulderLeft").getSpriteRect().height - 5.0f);
    sf::Vector2f elbowRightOffset(0.0f, characterParts.at("shoulderRight").getSpriteRect().height - 5.0f);
    sf::Vector2f armLeftOffset(0.0f, characterParts.at("elbowLeft").getSpriteRect().height - 5.0f);
    sf::Vector2f armRightOffset(0.0f, characterParts.at("elbowRight").getSpriteRect().height - 5.0f);
    sf::Vector2f pelvisOffset(characterParts.at("chest").getSpriteRect().width / 4, characterParts.at("chest").getSpriteRect().height - 5.0f);
    sf::Vector2f thighLeftOffset(characterParts.at("pelvis").getSpriteRect().width / -2, characterParts.at("pelvis").getSpriteRect().height / 3);
    sf::Vector2f thighRightOffset(characterParts.at("pelvis").getSpriteRect().width * 1.5, characterParts.at("pelvis").getSpriteRect().height / 3);
    sf::Vector2f legLeftOffset(0.0f, characterParts.at("thighLeft").getSpriteRect().height - 6.0f);
    sf::Vector2f legRightOffset(0.0f, characterParts.at("thighRight").getSpriteRect().height - 6.0f);
    sf::Vector2f footLeftOffset(characterParts.at("footLeft").getSpriteRect().width / -1.7f, characterParts.at("legLeft").getSpriteRect().height - 10.0f);
    sf::Vector2f footRightOffset(characterParts.at("footRight").getSpriteRect().width / 1.7f, characterParts.at("legRight").getSpriteRect().height - 10.0f);

    sf::Vector2f headPosition = chestPosition + headOffset;
    sf::Vector2f shoulderLeftPosition = chestPosition - shoulderLeftOffset;
    sf::Vector2f shoulderRightPosition = chestPosition + shoulderRightOffset;
    sf::Vector2f elbowLeftPosition = shoulderLeftPosition + elbowLeftOffset;
    sf::Vector2f elbowRightPosition = shoulderRightPosition + elbowRightOffset;
    sf::Vector2f armLeftPosition = elbowLeftPosition + armLeftOffset;
    sf::Vector2f armRightPosition = elbowRightPosition + armRightOffset;
    sf::Vector2f pelvisPosition = chestPosition + pelvisOffset;
    sf::Vector2f thighLeftPosition = pelvisPosition + thighLeftOffset;
    sf::Vector2f thighRightPosition = pelvisPosition + thighRightOffset;
    sf::Vector2f legLeftPosition = thighLeftPosition + legLeftOffset;
    sf::Vector2f legRightPosition = thighRightPosition + legRightOffset;
    sf::Vector2f footLeftPosition = legLeftPosition + footLeftOffset;
    sf::Vector2f footRightPosition = legRightPosition + footRightOffset;

    characterParts.at("head").setPosition(headPosition);
    characterParts.at("chest").setPosition(chestPosition);
    characterParts.at("shoulderLeft").setPosition(shoulderLeftPosition);
    characterParts.at("shoulderRight").setPosition(shoulderRightPosition);
    characterParts.at("elbowLeft").setPosition(elbowLeftPosition);
    characterParts.at("elbowRight").setPosition(elbowRightPosition);
    characterParts.at("armLeft").setPosition(armLeftPosition);
    characterParts.at("armRight").setPosition(armRightPosition);
    characterParts.at("pelvis").setPosition(pelvisPosition);
    characterParts.at("thighLeft").setPosition(thighLeftPosition);
    characterParts.at("thighRight").setPosition(thighRightPosition);
    characterParts.at("legLeft").setPosition(legLeftPosition);
    characterParts.at("legRight").setPosition(legRightPosition);
    characterParts.at("footLeft").setPosition(footLeftPosition);
    characterParts.at("footRight").setPosition(footRightPosition);
}

void Character::updateArmorPositions() {
    for (const auto& characterPartPair : characterParts) {
        const std::string& partKey = characterPartPair.first;
        if (armorPieces.find(partKey) != armorPieces.end()) {
            armorPieces.at(partKey).setPosition(characterPartPair.second.getPosition());
        }
    }
}

void Character::walkAnimation() {
    float angle = 15;

    rotateAndMovePart("thighRight", -angle, sf::Vector2f(0.0f, -4.0f), sf::Vector2f(0.0f, -4.0f));
    rotateAndMovePart("legRight", -angle, sf::Vector2f(12.0f, -4.0f), sf::Vector2f(12.0f, -4.0f));
    rotateAndMovePart("footRight", -angle, sf::Vector2f(24.0f, -8.0f), sf::Vector2f(24.0f, -8.0f));

    rotateAndMovePart("thighLeft", angle, sf::Vector2f(0.0f, -4.0f), sf::Vector2f(0.0f, -4.0f));
    rotateAndMovePart("legLeft", angle, sf::Vector2f(-12.0f, -4.0f), sf::Vector2f(-12.0f, -4.0f));
    rotateAndMovePart("footLeft", angle, sf::Vector2f(-24.0f, -8.0f), sf::Vector2f(-24.0f, -8.0f));

    animationRunning = true;
}

void Character::attackAnimation(bool rightHand) {
    float angle = 90;

    if (rightHand) {
        rotateAndMovePart("shoulderRight", angle, sf::Vector2f(-22.0f, 26.0f), sf::Vector2f(-22.0f, 26.0f));
        rotateAndMovePart("elbowRight", angle, sf::Vector2f(-49.0f, -4.0f), sf::Vector2f(-49.0f, -4.0f));
        rotateAndMovePart("armRight", angle, sf::Vector2f(-71.0f, -26.0f), sf::Vector2f(-71.0f, -26.0f));
    }
    else {
        rotateAndMovePart("shoulderLeft", -angle, sf::Vector2f(14.0f, 26.0f), sf::Vector2f(14.0f, 26.0f));
        rotateAndMovePart("elbowLeft", -angle, sf::Vector2f(45.0f, -2.0f), sf::Vector2f(45.0f, -2.0f));
        rotateAndMovePart("armLeft", -angle, sf::Vector2f(67.0f, -24.0f), sf::Vector2f(67.0f, -24.0f));
    }

    animationRunning = true;
}

void Character::rotateAndMovePart(const std::string& partName, float angle, const sf::Vector2f& moveCharacter, const sf::Vector2f& moveArmor) {
    if (characterParts.find(partName) != characterParts.end()) {
        characterParts.at(partName).rotateSprite(angle);
        characterParts.at(partName).setPosition(characterParts.at(partName).getPosition() + moveCharacter);
    }

    if (armorPieces.find(partName) != armorPieces.end()) {
        armorPieces.at(partName).rotateSprite(angle);
        armorPieces.at(partName).setPosition(armorPieces.at(partName).getPosition() + moveArmor);
    }
}

void Character::resetAnimation() {
    animationRunning = false;
    
    sf::sleep(sf::milliseconds(300));

    resetPart("thighRight");
    resetPart("legRight");
    resetPart("footRight");
    resetPart("thighLeft");
    resetPart("legLeft");
    resetPart("footLeft");
    resetPart("shoulderRight");
    resetPart("elbowRight");
    resetPart("armRight");
    resetPart("shoulderLeft");
    resetPart("elbowLeft");
    resetPart("armLeft");

    assembleBody();
    updateArmorPositions();
}

void Character::resetPart(const std::string& partName) {
    if (characterParts.find(partName) != characterParts.end()) {
        characterParts.at(partName).setRotationSprite(0);
    }

    if (armorPieces.find(partName) != armorPieces.end()) {
        armorPieces.at(partName).setRotationSprite(0);
    }
}

void Character::moveBody(sf::Vector2f movePosition) {
    this->bodyPosition += movePosition;
    assembleBody();
    updateArmorPositions();
}

void Character::setBodyPosition(sf::Vector2f bodyPosition) {
    this->bodyPosition = bodyPosition;
    assembleBody();
    updateArmorPositions();
}

void Character::display(sf::RenderWindow& window) {
    std::vector<std::string> const renderOrderBody = {
        "chest", "head", "shoulderLeft", "shoulderRight", "elbowLeft", "elbowRight", "armLeft", "armRight", 
        "thighLeft", "thighRight", "pelvis", "legLeft", "legRight", "footLeft", "footRight"
    };

    for (const std::string &partName : renderOrderBody) {
        if (characterParts.find(partName) != characterParts.end()) {
            const CharacterPart& part = characterParts.at(partName);
            window.draw(part.getSprite());
        }
    }

    std::vector<std::string> const renderOrderArmor = {
        "pelvis", "chest", "head", "shoulderLeft", "shoulderRight", "elbowLeft", "elbowRight", "armLeft", "armRight",
        "thighLeft", "thighRight", "footLeft", "footRight", "legLeft", "legRight"
    };

    for (const std::string& partName : renderOrderArmor) {
        if (armorPieces.find(partName) != armorPieces.end()) {
            const ArmorPiece& part = armorPieces.at(partName);
            window.draw(part.getSprite());
        }
    }
}

void Character::addArmorPiece(std::string& characterPart,ArmorPiece& armorPiece) {
    armorPieces.insert_or_assign(characterPart, armorPiece);
}

void Character::addWeapon(std::string& characterPart, Weapon& weapon) {
    weapons.insert_or_assign(characterPart, weapon);
}

bool Character::isArmorPieceInMap(ArmorPiece* armorPiece) const {
    for (const auto& pair : armorPieces) {
        std::string armorInMapName = pair.second.getName() + pair.second.getType();
        std::string selectedArmor = armorPiece->getName() + armorPiece->getType();
        if (armorInMapName == selectedArmor) {
            return true;
        }
    }

    return false;
}

bool Character::isWeaponInMap(Weapon* weapon) const {
    for (const auto& pair : weapons) {
        std::string weaponInMapName = pair.second.getName() + pair.second.getType();
        std::string selectedWeapon = weapon->getName() + weapon->getType();
        if (weaponInMapName == selectedWeapon) {
            return true;
        }
    }

    return false;
}

void Character::removeArmorPiece(const std::string& characterPart) {
    auto it = armorPieces.find(characterPart);

    if (it != armorPieces.end()) {
        it->second.setPosition(sf::Vector2f(-100.0f, -100.0f));
        armorPieces.erase(it);
    }
}

void Character::removeWeapon(const std::string& characterPart) {
    auto it = weapons.find(characterPart);

    if (it != weapons.end()) {
        it->second.setPosition(sf::Vector2f(-100.0f, -100.0f));
        weapons.erase(it);
    }
}

void Character::attackEnemy(Character& enemy) {
    if (abs(this->getBodyPosition().x - enemy.getBodyPosition().x) < getReach()) {
        int numberRolled = rollDice(1, 100);
        int chance = 20 + attack*10 - enemy.defence*5;

        if (numberRolled <= chance) {
            int strengthDamage = rollDice(1, strength);
            enemy.hp -= 2 + strengthDamage;
        }
    }
}

void Character::rest() {
    this->setHp(-2);
}

int Character::rollDice(int min, int max) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(min, max);
    int number = distribution(generator);

    return number;
}

int Character::getReach() {
    return 90;
}

int Character::getSpeed() {
    return 20 + 5 * agility;
}

void Character::incrementStrength() {
    strength++;
}

void Character::decrementStrength() {
    strength--;
}

void Character::incrementAgility() {
    agility++;
}

void Character::decrementAgility() {
    agility--;
}

void Character::incrementAttack() {
    attack++;
}

void Character::decrementAttack() {
    attack--;
}

void Character::incrementDefence() {
    defence++;
}

void Character::decrementDefence() {
    defence--;
}

void Character::incrementVitality() {
    vitality++;
}

void Character::decrementVitality() {
    vitality--;
}

void Character::incrementCharisma() {
    charisma++;
}

void Character::decrementCharisma() {
    charisma--;
}

void Character::incrementStamina() {
    stamina++;
}

void Character::decrementStamina() {
    stamina--;
}

void Character::setHp(int hp) {
    this->hp = hp;
}

void Character::takeDamage(int damage) {
    hp -= damage;
}

const int Character::getStrength()
{
    return strength;
}

const int Character::getAgility()
{
    return agility;
}

const int Character::getAttack()
{
    return attack;
}

const int Character::getDefence()
{
    return defence;
}

const int Character::getVitality()
{
    return vitality;
}

const int Character::getCharisma()
{
    return charisma;
}

const int Character::getStamina()
{
    return stamina;
}

const int Character::getHp()
{
    return hp;
}

const int Character::getAvailablePoints()
{
    return availablePoints;
}

void Character::addAvailablePoints(int amount) {
    availablePoints += amount;
}

const sf::Vector2f Character::getBodyPosition() {
    return bodyPosition;
}

const bool Character::getAnimationRunning() {
    return animationRunning;
}