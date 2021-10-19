#include "includeAll.h"
#include "utilities.cpp"
#include "ReversiEngine.h"


bool ReversiEngine::isStarted() const {
    return _isStarted;
}

void ReversiEngine::finishGame() {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return;
    }

    auto snap = getSnapshot();

    _isStarted = false;

    clearVectorOfPointers(availableMoves);
    clearVectorOfPointers(enemyMoves);
    clearMapOfVectorsOfPointers(aims);
    availableMoves = enemyMoves = nullptr;
    aims = nullptr;

    observer->onFinished(this, snap);
    delete snap;

}

GameState ReversiEngine::analyseGame() {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return FINISHED;
    }

    availableMoves = findAllPossibleMovesFor(currentPlayer);
    enemyMoves = findAllPossibleMovesFor(currentPlayer->getEnemy());

    aims = new map<Point, PointsList*>();
    for (Point* p: *availableMoves) {
        PointsList* aimList = findAllAimsFor(currentPlayer, *p);
        if (aimList != nullptr) {
            (*aims)[*p] = aimList;
        }
    }

    if (!availableMoves->empty()) {
        return GameState::MAY_MOVE;
    } else {
        if (enemyMoves->empty()) {
            finishGame();
            return GameState::FINISHED;
        }
        observer->onSkipped(this, currentPlayer);
        clearMoveData();
        switchPlayer();
        moveCounter++;
        return GameState::SKIPPED;
    }
}

void ReversiEngine::move(Point target, Chip* player) {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return;
    }

    if (availableMoves == nullptr) {
        tryToNotifyOnError(new IllegalGameStateException(_isStarted,"You should start game and invoke analyseGame() before the first move()"));
        return;
    }
    if (!containsPoint(availableMoves, target)) {
        tryToNotifyOnError(new IllegalMoveException(currentPlayer, target.getX(), target.getY(), "Thus no aims can be found"));
        return;
    }
    if (player != currentPlayer) {
        tryToNotifyOnError(new IllegalChipException(player, "This player can't move now. It's enemy's turn"));
        return;
    }

    PointsList* aimList = getAvailableAimsForMove(target);
    for (Point* aim : *aimList) {
        field->switchChip(aim->getX(), aim->getY());
    }
    field->setChip(target.getX(), target.getY(), currentPlayer);

    observer->onMoved(this, currentPlayer, target, aimList);

    moveCounter++;
    clearMoveData();
    switchPlayer();
}

// PUBLIC

void ReversiEngine::startGame() {
    if (isStarted()) {
        tryToNotifyOnError(gameStateException());
        return;
    }
    this->player1 = requireNonNull(player1, "player1");
    this->player2 = requireNonNull(player2, "player2");

    initDefaultValues();

    _isStarted = true;

    if (observer != nullptr) observer->onStarted(this);

    notifyWaitingForMove();
}


Field *ReversiEngine::getSnapshot() const{
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return nullptr;
    }
    return field->getSnapshot();
}

PointsList* ReversiEngine::getAvailableMoves() {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return nullptr;
    }
    if (availableMoves == nullptr) {
        tryToNotifyOnError(new IllegalGameStateException(_isStarted, "You have to invoke analyseGame() before the first move()"));
        return nullptr;
    }
    return availableMoves;
}

PointsList* ReversiEngine::getAvailableAimsForMove(Point point) {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return nullptr;
    }
    if (availableMoves == nullptr) {
        tryToNotifyOnError(
                new IllegalGameStateException(_isStarted, "You have to invoke analyseGame() before the first move()"));
        return nullptr;
    }

    PointsList* aimsList = getOrNull(*aims, point);
    return aimsList;
}

// PRIVATE

PointsList* ReversiEngine::findAllPossibleMovesFor(Chip *player) {
    auto moves = new PointsList();
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            if (field->getChip(i, j) == Chip::NONE) {
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

PointsList *ReversiEngine::findAllAimsFor(Chip *player, Point point) {
    auto aimList = new PointsList();
    for (Point direction: POSSIBLE_DIRECTIONS) {
        PointsList* points = findAimsOnDirectionFor(player, point.getX(), point.getY(), direction.getX(), direction.getY());
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
        if (chip == Chip::NONE) {
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
    currentPlayer = Chip::BLACK; // Black is always first
    clearVectorOfPointers(availableMoves);
    clearVectorOfPointers(enemyMoves);
    clearMapOfVectorsOfPointers(aims);
    availableMoves = enemyMoves = nullptr;
    aims = nullptr;
}

void ReversiEngine::switchPlayer() {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return;
    }
    Chip* enemy = currentPlayer->getEnemy();
    currentPlayer = enemy;
    if (observer != nullptr) observer->onSwitchPlayers(this);
    notifyWaitingForMove();
}

int ReversiEngine::getPlayerNumber(Chip *chip) {
    if (player1 == chip) return 1;
    if (player2 == chip) return 2;
    return -1;
}

// small


int ReversiEngine::getMoveCounter() const {
    if (!isStarted()) {
        tryToNotifyOnError(gameStateException());
        return -1;
    }
    return moveCounter;
}

bool ReversiEngine::setFirstBlackSecondWhite() {
    if (isStarted()) {
        tryToNotifyOnError(gameStateException());
        return false;
    }
    player1 = Chip::BLACK;
    player2 = Chip::WHITE;
    return true;
}
bool ReversiEngine::setFirstWhiteSecondBlack() {
    if (isStarted()) {
        tryToNotifyOnError(gameStateException());
        return false;
    }
    player1 = Chip::WHITE;
    player2 = Chip::BLACK;
    return true;
}

ReversiEngine::ReversiEngine() {
    initDefaultValues();
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

bool ReversiEngine::containsPoint(PointsList* list, Point point) {
    function<bool(Point*)> comparator = [&point](Point* p) -> bool {return point == *p;};
    return contains(*list, comparator);
}

Chip *ReversiEngine::getCurrentPlayer() {
    return currentPlayer;
}

void ReversiEngine::clearMoveData() {
    clearVectorOfPointers(availableMoves);
    clearVectorOfPointers(enemyMoves);
    clearMapOfVectorsOfPointers(aims);
    availableMoves = enemyMoves = nullptr;
    aims = nullptr;
}

Chip* ReversiEngine::getPlayersChip(int playerNum) {
    if (playerNum == 1) {
        return player1;
    } else if (playerNum == 2) {
        return player2;
    }
    tryToNotifyOnError(new IllegalPlayerNumberException(playerNum));
}

void ReversiEngine::tryToNotifyOnError(std::exception* ex) const {
    if (observer != nullptr)
        observer->onError(const_cast<ReversiEngine*>(this), *ex);
    else
        throw *ex;
}

IllegalGameStateException *ReversiEngine::gameStateException() const{
    return new IllegalGameStateException(isStarted());
}

Chip *ReversiEngine::getChipOn(Point point) {
    return field->getChip(point.getX(), point.getY());
}

void ReversiEngine::notifyWaitingForMove() {
    analyseGame();
    if (observer != nullptr) {
        observer->onWaitingForMove(this);
    }
}






