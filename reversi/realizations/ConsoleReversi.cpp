#include "ConsoleReversi.h"

void ConsoleReversi::start() {
    engine->setObserver(new BasicObserver());

    engine->startGame(player1, player2);
}

void printSnapshot(Field* snap) {
    int snapSize = snap->getSize();
    int hugeSize = snapSize + 2;
    int last = hugeSize - 1;

    char charSnap[hugeSize][hugeSize];
    for (int i = 0; i < snapSize; ++i) {
        for (int j = 0; j < snapSize; ++j) {
            charSnap[j+1][i+1] = chipToChar(snap->getChip(i, j));
        }
    }

    for (int i = 0; i < snapSize; ++i) {
        char ch = '0' + i;
        charSnap[i + 1][0] = ch;
        charSnap[i + 1][last] = ch;
        charSnap[0][i + 1] = ch;
        charSnap[last][i + 1] = ch;
    }

    char corner = ' ';
    charSnap[0][0] = corner;
    charSnap[0][last] = corner;
    charSnap[last][last] = corner;
    charSnap[last][0] = corner;

    for (int i = 0; i < hugeSize; ++i) {
        for (int j = 0; j < hugeSize; ++j) {
            cout << setw(2) << charSnap[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void printStat(Field* snap, ReversiEngine* engine) {
    auto stats = snap->getStatistics();
    cout << "Score: "
         << "(Player " << engine->getPlayerNumber(Chip::BLACK) << ") "
         << stats[Chip::BLACK]
         << " : "
         << stats[Chip::WHITE]
         << " (Player " << engine->getPlayerNumber(Chip::WHITE) << ") "
         << endl;
}

void printAvailableMoves(ReversiEngine* engine) {
    cout << "Available moves: ";
    auto moves = engine->getAvailableMoves();
    for (size_t i = 0; i < moves->size(); ++i) {
        Point* p = (*moves)[i];
        cout << *p;
        if (i >= moves->size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

Point* readFromConsole(ReversiEngine* engine) {
    int x = -1;
    int y = -1;
    char ch;
    while (true) {
        cin >> ch;
        if ('0' <= ch && ch < '8') {
            if (!(0 <= x && x < 8)) {
                x = ch - '0';
            } else if (!(0 <= y && y < 8)) {
                y = ch - '0';
            }

            if ((0 <= x && x < 8) && (0 <= y && y < 8)) {
                return new Point(x, y);
            }
        } else if (ch == 'a') {
            printAvailableMoves(engine);
        } else if (ch == 'f') {
            engine->finishGame();
            return nullptr;
        }
    }
}


void BasicObserver::onSkipped(ReversiEngine *engine, Chip* player) {
    cout << "Move "
         << engine->getMoveCounter()
         << ": "
         << *player
         << " skip" << endl;
}

void BasicObserver::onMoved(ReversiEngine *engine, Chip *player, Point move, PointsList* switchedList) {
    cout << "Move "
         << engine->getMoveCounter()
         << ": "
         << *player
         << " moved on "
         << move
         << ". Switched chips: "
         << switchedList->size()
         << endl;
    auto snap = engine->getSnapshot();
    printStat(snap, engine);
    printSnapshot(engine->getSnapshot());
    delete snap;
}

void BasicObserver::onStarted(ReversiEngine *engine) {
    cout << "GameStarted"<< endl
         << "Initial board: X - black, O - white"<< endl;
    printSnapshot(engine->getSnapshot());
}

void BasicObserver::onFinished(ReversiEngine *engine, Field *snap) {
    printStat(snap, engine);
    cout << "Game finished" << endl;
    delete snap;
}

