#include "ReversiAi.h"

Point ReversiAi::chooseMove(ReversiEngine *engine, Chip *aiChip) {
    auto availableMoves = engine->getAvailableMoves();
    size_t maxChips = 0;
    Point point(-1,-1);
    for (Point* p: *availableMoves) {
        auto enemiesDefeated = engine->getAvailableAimsForMove(*p)->size();
        if (enemiesDefeated > maxChips) {
            maxChips = enemiesDefeated;
            point = *p;
        }
    }
    return point;
}
