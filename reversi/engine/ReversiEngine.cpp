#include "includeAll.h"
#include "utilities.cpp"

bool ReversiEngine::isStarted() const {
    return _isStarted;
}

void ReversiEngine::requestToFinish() {
    checkIsStarted();
    requestedToFinish = true;
}

void ReversiEngine::mainLoop() {
    bool hasMoves = true;
    while (true) {
        if (mayFinish(hasMoves)) return;

        std::vector<Point*>* moves = getAvailableMoves();
        if (moves->empty()) {
            auto movesForEnemy = findAllPossibleMovesFor(currentPlayer->getChip()->getEnemy());
            if (movesForEnemy->empty()) {
                hasMoves = false;
            }

            if (mayFinish(hasMoves)) return;

            player1->onSkipped(this, currentPlayer);
            player2->onSkipped(this, currentPlayer);
            if (observer != nullptr) observer->onSkipped(this, currentPlayer);
        } else {
            Point* move;
            while (true) {
                move = currentPlayer->onMoveRequest(this);

                if (mayFinish(hasMoves)) return;

                vector<Point*>* availableMoves = getAvailableMoves();

                if (containsPoint(*availableMoves, move)) {
                    break;
                } else {
                    auto error = IllegalMoveException(currentPlayer->getChip(), move->getX(), move->getY());
                    currentPlayer->onError(this, error);
                    if (mayFinish(hasMoves)) return;
                }
            }

            PointsList* aimList = getAvailableAimsForMove(move);
            for (Point* aim : *aimList) {
                field->switchChip(aim->getX(), aim->getY());
            }
            field->setChip(move->getX(), move->getY(), currentPlayer->getChip());

            player1->onMoved(this, currentPlayer, move, aimList);
            player2->onMoved(this, currentPlayer, move, aimList);
            if (observer != nullptr) observer->onMoved(this, currentPlayer, move, aimList);
            delete move;
        }
        switchPlayer();
        moveCounter++;

        if (mayFinish(hasMoves)) return;

        clearVectorOfPointers(validMoves);
        clearMapOfVectorsOfPointers(aims);
        validMoves = nullptr;
        aims = nullptr;
    }
}

bool ReversiEngine::mayFinish(bool hasMoves) const {
    return requestedToFinish || !hasMoves;
}
// PUBLIC

void ReversiEngine::startGame(Player *player1, Player *player2) {
    checkIsNotStarted();
    this->player1 = requireNonNull(player1, "player1");
    this->player2 = requireNonNull(player2, "player2");

    initDefaultValues();

    _isStarted = true;

    if (observer != nullptr) observer->onStarted(this);
    player1->onStarted(this);
    player2->onStarted(this);


    mainLoop();


    player1->onFinished(this, getSnapshot());
    player2->onFinished(this, getSnapshot());
    if (observer != nullptr) observer->onFinished(this, getSnapshot());

    _isStarted = false;
}


Field *ReversiEngine::getSnapshot() const{
    checkIsStarted();
    return field->getSnapshot();
}

std::vector<Point *> *ReversiEngine::getAvailableMoves() {
    checkIsStarted();
    if (validMoves == nullptr) {
        validMoves = findAllPossibleMovesFor(currentPlayer->getChip());
    }
    return validMoves;
}

PointsList *ReversiEngine::getAvailableAimsForMove(Point *point) {
    checkIsStarted();
    PointsList* availableMoves = getAvailableMoves();
    if (!containsPoint(*availableMoves, point)) {
        throw IllegalMoveException(currentPlayer->getChip(), point->getX(), point->getY());
    }

    if (aims == nullptr) {
        aims = new map<Point, PointsList*>();
    }

    PointsList* aimList = getOrNull(*aims, *point);
    if (aimList == nullptr) {
        aimList = findAllAimsFor(currentPlayer->getChip(), point->getX(), point->getY());
        if (aims != nullptr)
            (*aims)[*point] = aimList;
    }
    return aimList;
}

// PRIVATE

PointsList* ReversiEngine::findAllPossibleMovesFor(Chip *player) {
    auto moves = new PointsList();
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            if (field->getChip(i, j) == Chip::NONE()) {
                for (Point dir: POSSIBLE_DIRECTIONS) {
                    Point* endPoint = findMoveOtherSidePointFor(player, i, j, dir.getX(), dir.getY());
                    bool isValidMove = endPoint != nullptr;
                    if (isValidMove) {
                        moves->push_back(new Point(i, j));
                        delete endPoint;
                        break;
                    }
                }
            }
        }
    }
    return moves;
}

PointsList *ReversiEngine::findAllAimsFor(Chip *player, int x, int y) {
    auto aimList = new PointsList();
    for (Point direction: POSSIBLE_DIRECTIONS) {
        PointsList* points = findAimsOnDirectionFor(player, x, y, direction.getX(), direction.getY());
        for (Point* p: *points) {
            aimList->push_back(p);
        }
        delete points;
    }
    return aimList;
}

PointsList *ReversiEngine::findAimsOnDirectionFor(Chip *player, int x, int y, int dx, int dy) {
    Point* endPoint = findMoveOtherSidePointFor(player, x, y, dx, dy);
    if (endPoint != nullptr) {
        return pointsBetween(x, y, endPoint->getX(), endPoint->getY());
    } else {
        return new PointsList();
    }
}

Point* ReversiEngine::findMoveOtherSidePointFor(Chip *player, int fromX, int fromY, int dx, int dy) {
    Chip* enemy = player->getEnemy();
    bool foundEnemy = false;

    int i = fromX + dx;
    int j = fromY + dy;
    while ((0 <= i && i < FIELD_SIZE) && (0 <= j && j < FIELD_SIZE)) {
        Chip* chip = field->getChip(i, j);
        if (chip == Chip::NONE()) {
            return nullptr;
        }

        if (chip == enemy) {
            foundEnemy = true;
        } else if (chip == player) {
            if (!foundEnemy) {
                return nullptr;
            }
            auto endPoint = new Point(i, j);
            return endPoint;
        }

        i += dx; j += dy;
    }

    return nullptr;
}

PointsList *ReversiEngine::pointsBetween(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int sx = sign(dx);
    int sy = sign(dy);
    int size = max(abs(dx), abs(dy));
    auto list = new PointsList();
    for (int i = 1; i < size; ++i) {
        list->push_back(new Point(x1 + i*sx, y1 + i*sy));
    }
    return list;
}

void ReversiEngine::initDefaultValues() {
    field->clear();
    moveCounter = 0;
    currentPlayer = (doesFirstPlayerStart) ? player1 : player2;
    clearVectorOfPointers(validMoves);
    clearMapOfVectorsOfPointers(aims);
    validMoves = nullptr;
    aims = nullptr;

    validMoves = nullptr;
    aims = nullptr;
    requestedToFinish = false;
}

void ReversiEngine::switchPlayer() {
    checkIsStarted();
    Chip* enemy = currentPlayer->getEnemyChip();
    if (player1->getChip() == enemy) {
        currentPlayer = player1;
    } else {
        currentPlayer = player2;
    }
}

int ReversiEngine::getPlayerNumber(Chip *chip) {
    if (player1->getChip() == chip) return 1;
    if (player2->getChip() == chip) return 2;
    return -1;
}

// small


int ReversiEngine::getMoveCounter() const {
    checkIsStarted();
    return moveCounter;
}

void ReversiEngine::setFirstPlayerStarts() {
    checkIsNotStarted();
    doesFirstPlayerStart = true;
}
void ReversiEngine::setSecondPlayerStarts() {
    checkIsNotStarted();
    doesFirstPlayerStart = false;
}

ReversiEngine::ReversiEngine() {
    initDefaultValues();
}

void ReversiEngine::checkIsNotStarted() const {
    if (_isStarted) {
        throw IllegalGameStateException(_isStarted);
    }
}
void ReversiEngine::checkIsStarted() const {
    if (!_isStarted) {
        throw IllegalGameStateException(_isStarted);
    }
}

void ReversiEngine::setObserver(GameListener* observer) {
    this->observer = observer;
}
void ReversiEngine::removeObserver() {
    this->observer = nullptr;
}

bool ReversiEngine::containsPoint(PointsList& list, Point *point) {
    function<bool(Point*)> comparator = [point](Point* p) -> bool {return *point == *p;};
    return contains(list, comparator);
}






