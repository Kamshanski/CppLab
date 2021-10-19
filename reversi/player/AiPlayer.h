#pragma once
#include "includeAll.h"
class AiPlayer : public Player {
public:
    AiPlayer(Chip* chip);

public:
    Point *onMoveRequest(ReversiEngine *engine) override;
};

