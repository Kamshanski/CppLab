#include "includeAll.h"

Point *AiPlayer::onMoveRequest(ReversiEngine *engine) {
    auto availableMoves = engine->getAvailableMoves();
    size_t maxChips = 0;
    Point point(-1,-1);
    for (Point* p: *availableMoves) {
        auto enemiesDefeated = engine->getAvailableAimsForMove(p)->size();
        if (enemiesDefeated > maxChips) {
            maxChips = enemiesDefeated;
            point = *p;
        }
    }
    return new Point(point);

}

AiPlayer::AiPlayer(Chip *chip) : Player(chip) {}
