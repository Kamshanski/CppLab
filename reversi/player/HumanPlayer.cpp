#include "includeAll.h"


HumanPlayer::HumanPlayer(Chip *chip, const function<Point *(ReversiEngine*)> &actor) : Player(chip), actor(actor) {}

Point *HumanPlayer::onMoveRequest(ReversiEngine *engine) {
    cout << "Player "
         << engine->getPlayerNumber(getChip())
         << " (" << getChip() << "): ";

    Point* p = actor(engine);
    return p;

}

