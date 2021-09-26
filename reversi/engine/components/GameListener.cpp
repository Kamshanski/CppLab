#include "includeAll.h"

void GameListener::onSkipped(ReversiEngine *engine, Player *player) {}

void GameListener::onMoved(ReversiEngine *engine, Player *player, Point *move, std::vector<Point *> *switchedList) {}

void GameListener::onFinished(ReversiEngine *engine, Field *snap) {}

void GameListener::onStarted(ReversiEngine *engine) {}

void GameListener::onError(ReversiEngine *engine, std::exception& error) {}
