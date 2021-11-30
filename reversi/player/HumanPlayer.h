#pragma once

#include "includeAll.h"

class HumanPlayer : public Player {
    std::function<Point*(ReversiEngine*)> actor;
public:
    HumanPlayer(Chip* chip, const function<Point*(ReversiEngine*)>& actor);


    Point* onMoveRequest(ReversiEngine* engine) override;
};

