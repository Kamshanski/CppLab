#pragma once
#include "includeAll.h"

char chipToChar(Chip* chip);


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
    bool requestedToFinish = false;
    int moveCounter = 0;
    Field* field = new Field(FIELD_SIZE);

    bool doesFirstPlayerStart = true;
    Player* currentPlayer = nullptr;
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    GameListener* observer = nullptr;

    std::vector<Point*>* validMoves = nullptr;
    std::map<Point, vector<Point*>*>* aims = nullptr;


public:
    ReversiEngine();
    Field* getSnapshot() const;
    void startGame(Player* player1, Player* player2);
    std::vector<Point*>* getAvailableMoves();

    // small
    void setObserver(GameListener* observer);
    void removeObserver();
    bool isStarted() const;
    void requestToFinish();
    int getMoveCounter() const;
    void setFirstPlayerStarts();
    void setSecondPlayerStarts();
    PointsList* getAvailableAimsForMove(Point* point);
    int getPlayerNumber(Chip* chip);
private:
    void checkIsNotStarted() const;
    void checkIsStarted() const;
    void initDefaultValues();
    void mainLoop();
    bool mayFinish(bool hasMoves) const;
    PointsList* findAllPossibleMovesFor(Chip* player);
    Point* findMoveOtherSidePointFor(Chip* player, int fromX, int fromY, int dx, int dy);
    PointsList* findAllAimsFor(Chip* player, int x, int y);
    PointsList* findAimsOnDirectionFor(Chip* player, int x, int y, int dx, int dy);
    static PointsList* pointsBetween(int x1, int y1, int x2, int y2);
    static bool containsPoint(PointsList& list, Point* point);
    void switchPlayer();
};

