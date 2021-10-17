#include "includeAll.h"

void GameListener::onSkipped(ReversiEngine *engine, Chip *player) {}

void GameListener::onMoved(ReversiEngine *engine, Chip *player, Point move, PointsList* switchedList) {}

void GameListener::onFinished(ReversiEngine *engine, Field *snap) {}

void GameListener::onSwitchPlayers(ReversiEngine *engine) {}

void GameListener::onStarted(ReversiEngine *engine) {}

void GameListener::onError(ReversiEngine *engine, std::exception& error) {}
