#pragma once
#include "includeAll.h"
class ReversiEngine;
class Player;
class GameListener {
public:
    virtual void onSkipped(ReversiEngine *engine, Player* player);
    virtual void onMoved(ReversiEngine *engine, Player* player, Point* move, std::vector<Point*>* switchedList);
    virtual void onStarted(ReversiEngine *engine);
    virtual void onFinished(ReversiEngine *engine, Field* snap);
    virtual void onError(ReversiEngine *engine, std::exception& error);
};

