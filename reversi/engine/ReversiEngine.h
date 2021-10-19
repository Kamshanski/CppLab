#pragma once
#include "includeAll.h"

char chipToChar(Chip* chip);

enum GameState {FINISHED, MAY_MOVE, SKIPPED};
template<typename T>
T* requireNonNull(T* obj, const string& varName);


template<typename T>
bool contains(vector<T*> &v, std::function<bool(T*)> comparator);

template<typename K, typename V>
V* getOrNull(map<K, V*> &m, K &key);

int sign(int num);

template<typename T>
void clearVectorOfPointers(vector<T*>* v);

template<typename K, typename V>
void clearMapOfVectorsOfPointers(map<K, V*>* m);
class Player;
class GameListener;
class ReversiEngine {
private:
    bool _isStarted = false;
    int moveCounter = 0;
    Field* field = new Field(FIELD_SIZE);

    Chip* player1 = Chip::BLACK;
    Chip* player2 = Chip::WHITE;
    Chip* currentPlayer = nullptr;

    GameListener* observer = nullptr;

    PointsList* availableMoves = nullptr;
    PointsList* enemyMoves = nullptr;
    std::map<Point, PointsList*>* aims = nullptr;


public:
    ReversiEngine();
    Field* getSnapshot() const;
    void startGame();
    GameState analyseGame();
    void move(Point point, Chip* player);
    void finishGame();

    // small
    void setObserver(GameListener* observer);
    void removeObserver();
    bool isStarted() const;
    int getMoveCounter() const;
    bool setFirstBlackSecondWhite();
    bool setFirstWhiteSecondBlack();
    PointsList* getAvailableMoves();
    PointsList* getAvailableAimsForMove(Point point);
    int getPlayerNumber(Chip* chip);
    Chip* getPlayersChip(int playerNum);
    Chip* getCurrentPlayer();
    Chip* getChipOn(Point point);
private:
    void checkIsStarted() const;
    void initDefaultValues();
    PointsList* findAllPossibleMovesFor(Chip* player);
    Point* findMoveOtherSidePointFor(Chip* player, int fromX, int fromY, int dx, int dy);
    PointsList* findAllAimsFor(Chip* player, Point point);
    PointsList* findAimsOnDirectionFor(Chip* player, int x, int y, int dx, int dy);
    static PointsList* pointsBetween(int x1, int y1, int x2, int y2);
    static bool containsPoint(PointsList* list, Point point);
    void switchPlayer();
    void notifyWaitingForMove();
    void clearMoveData();
    void tryToNotifyOnError(std::exception* ex) const;
    IllegalGameStateException* gameStateException() const;
};

