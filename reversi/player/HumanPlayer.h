#pragma once
#include "includeAll.h"
class HumanPlayer : public Player {
public:
    HumanPlayer(Chip *chip);

    Point *onMoveRequest(ReversiEngine *engine) override;
};

