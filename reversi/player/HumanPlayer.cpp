#include "includeAll.h"


HumanPlayer::HumanPlayer(Chip *chip) : Player(chip) {}

Point *HumanPlayer::onMoveRequest(ReversiEngine *engine) {
    cout << "Player "
         << engine->getPlayerNumber(getChip())
         << " (" << getChip() << "): ";

    Point* p = readFromConsole(engine);
    return p;

}
