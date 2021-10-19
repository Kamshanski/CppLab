#pragma once
#include "includeAll.h"
class ReversiEngine;
class Player;
class GameListener {
public:
    virtual void onSkipped(ReversiEngine *engine, Chip* player);
    virtual void onMoved(ReversiEngine *engine, Chip* player, Point move, PointsList* switchedList);
    virtual void onSwitchPlayers(ReversiEngine *engine);
    virtual void onWaitingForMove(ReversiEngine *engine);
    virtual void onStarted(ReversiEngine *engine);
    virtual void onFinished(ReversiEngine *engine, Field* snap);
    virtual void onError(ReversiEngine *engine, std::exception& error);
};

