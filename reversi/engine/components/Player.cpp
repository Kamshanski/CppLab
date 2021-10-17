#include "includeAll.h"
class Player;
Chip *Player::getChip() const {
    return chip;
}

Chip *Player::getEnemyChip() const {
    return getChip()->getEnemy();
}

Player::Player(Chip *chip) {
    if (chip == Chip::NONE) {
        throw IllegalChipException(chip);
    }
    this->chip = chip;
}


