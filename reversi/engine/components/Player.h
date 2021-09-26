#pragma once
#include "includeAll.h"
class Player : public GameListener {
    Chip* chip;

protected:
    Player(Chip *chip);

public:
    virtual Point* onMoveRequest(ReversiEngine* engine) = 0;
    Chip *getChip() const;
    Chip* getEnemyChip() const;
};

