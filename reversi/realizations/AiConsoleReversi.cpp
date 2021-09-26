#include "includeAll.h"
class AiConsoleReversi : public ConsoleReversi {
public:
    AiConsoleReversi() {
        player1 = new HumanPlayer(Chip::BLACK());
        player2 = new AiPlayer(Chip::WHITE());
    }
};

int main() {
    char ch = 'a';
    AiConsoleReversi game;
    while (ch != 'e') {
        cout << "Control: "
             << "'s' to start"
             << "'a' to show available moves"
             << "'f' to finish game"
             << "'e' to shutdown" << endl;
        cin >> ch;
        if (ch == 'e') {
            return 0;
        } else if (ch == 's') {
            game.start();
        }
    }
    return 0;
}