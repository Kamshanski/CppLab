#pragma once
#include "includeAll.h"

void printSnapshot(Field* snap);

void printStat(Field* snap, ReversiEngine* engine);

void printAvailableMoves(ReversiEngine* engine);

Point* readFromConsole(ReversiEngine* engine);

class BasicObserver : public GameListener {
    void onSkipped(ReversiEngine *engine, Chip* player) override;

    void onMoved(ReversiEngine *engine, Chip* player, Point move, PointsList* switchedList) override;

    void onStarted(ReversiEngine *engine) override;

    void onFinished(ReversiEngine *engine, Field *snap) override;
};

class ConsoleReversi {
protected:
    Player* player1{};
    Player* player2{};

    ReversiEngine* engine = new ReversiEngine();

public:
    virtual void start();
};

