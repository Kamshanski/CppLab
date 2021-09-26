#include "includeAll.h"
class HumanConsoleReversi : public ConsoleReversi {
public:
    HumanConsoleReversi() {
        player1 = new HumanPlayer(Chip::BLACK());
        player2 = new HumanPlayer(Chip::WHITE());
    }
};

int main() {
    HumanConsoleReversi().start();
    return 0;
}