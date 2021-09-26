#include "includeAll.h"

int coords[] = {
        3, 2,   2, 4,           3, 5,   2, 2,           5, 4,   6, 4,           5, 3,   5, 2,
        1, 3,   0, 4,           6, 2,   7, 2,           5, 5,   2, 6,           4, 6,   5, 7,
        1, 2,   5, 6,           1, 4,   1, 1,           3, 1,   1, 5,           0, 2,   4, 0,
        3, 0,   2, 0,           3, 6,   3, 7,           4, 2,   2, 1,           1, 0,   0, 0,
        7, 5,   4, 1,           7, 1,   0, 3,           7, 3,   7, 4,           5, 1,   5, 0,
        1, 7,   1, 6,           0, 5,   7, 0,           2, 3,   4, 5,           2, 5,   0, 6,
        0, 7,   6, 3,           6, 7,   7, 7,           0, 1,   6, 1,           6, 0,   6, 6,
        6, 5,   7, 6,           2, 7,   4, 7,
};


class TestConsoleReversi : public ConsoleReversi {
    int index = 0;

public:
    TestConsoleReversi();

    Point* nextPoint() {
        return new Point(coords[index++], coords[index++]);
    }
};

class TestPlayer : public Player {
    function<Point*()> pointProvider;
public:
    TestPlayer(Chip *chip, const function<Point *()> &pointProvider) : Player(chip), pointProvider(pointProvider) {}

private:
    Point *onMoveRequest(ReversiEngine *engine) override {
        return pointProvider();
    }
};

TestConsoleReversi::TestConsoleReversi() {
    player1 = new TestPlayer(Chip::BLACK(), [this]() -> Point* {return this->nextPoint();});
    player2 = new TestPlayer(Chip::WHITE(), [this]() -> Point* {return this->nextPoint();});
}

int main() {
    TestConsoleReversi().start();
    return 0;
}