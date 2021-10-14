#include "includeAll.h"
class HumanConsoleReversi : public ConsoleReversi {
public:
    HumanConsoleReversi() {
        player1 = new HumanPlayer(Chip::BLACK(), readFromConsole);
        player2 = new HumanPlayer(Chip::WHITE(), readFromConsole);
    }
};

int main() {
    HumanConsoleReversi().start();
    return 0;
}