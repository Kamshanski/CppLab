
#include "includeAll.h"

using namespace std;

//---------------------------
HWND MAIN_WINDOW_HWND;
const char g_szClassName[] = "Reversi Game";

ButtonsField* bfField = nullptr;
RadioButtonGroup* rbgPlayerColor = nullptr;
RadioButtonGroup* rbgSecondPlayer = nullptr;
Label* lPlayerColor = nullptr;
Label* lSecondPlayer = nullptr;
Label* lScore = nullptr;
MultilineLabel* lGameLog = nullptr;
Button* btnStartStop = nullptr;

vector<Drawable*> drawables;
vector<Clickable*> clickables;

ReversiEngine* engine;
//---------------------------

void redrawRectangle(HWND hwnd, RECT rect) {
    InvalidateRect(hwnd, &rect, NULL);
}
//---------------------------
struct PlayerColorListener : RadioButtonGroupListener {
    bool onSelected(int idNew, int idPrev, vector<string> &options) override {
        if (idNew == 0) {
            engine->setFirstBlackSecondWhite();
        } else {
            engine->setFirstWhiteSecondBlack();
        }
        return true;
    }
};

struct SecondPlayerListener : RadioButtonGroupListener {
    bool onSelected(int idNew, int idPrev, vector<string> &options) override {
        return true;
    }
};

class GameObserver : public GameListener {
public:
    void fetchField() {
        auto snap = engine->getSnapshot();
        auto stats = snap->getStatistics();
        for (int i = 0; i < snap->getSize(); ++i) {
            for (int j = 0; j < snap->getSize(); ++j) {
                if (snap->getChip(i, j) == Chip::BLACK) bfField->setChipBlack(i, j);
                else if (snap->getChip(i, j) == Chip::WHITE) bfField->setChipWhite(i, j);
                else if (snap->getChip(i, j) == Chip::NONE) bfField->setChipInvisible(i, j);
            }
        }
        delete snap;
        redrawRectangle(MAIN_WINDOW_HWND, bfField->getViewRect());
    }

    void onSwitchPlayers(ReversiEngine *engine) override {
        fetchField();
        auto snap = engine->getSnapshot();
        auto stats = snap->getStatistics();
        ostringstream o;
        o << "Player 1 (" << engine->getPlayersChip(1) << ")"
          << stats[Chip::BLACK]
          << " : "
          << stats[Chip::WHITE]
          << "(" << engine->getPlayersChip(2) << ") Player 2";
        lScore->setText(o.str());
        delete snap;
        redrawRectangle(MAIN_WINDOW_HWND, lScore->getViewRect());
    }

    void onSkipped(ReversiEngine *engine, Chip *player) override {
        ostringstream o;
        o << "Player " << *player << " skipped move.";
        lGameLog->addLine(o.str());
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
    }

    void onMoved(ReversiEngine *engine, Chip *player, Point move, PointsList *switchedList) override {
        ostringstream o;
        o << "Player " << engine->getPlayerNumber(player)
          << " (" << *player << ") "
          << "moved on " << move << ". "
          << switchedList->size() << " enemy's chips were captured.";
        lGameLog->addLine(o.str());
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
    }

    void onStarted(ReversiEngine *engine) override {
        fetchField();
        ostringstream o;
        o << "Game started.";
        lGameLog->addLine(o.str());
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
    }

    void onFinished(ReversiEngine *engine, Field *snap) override {
        auto stats = snap->getStatistics();
        Chip* winner = (stats[Chip::BLACK] > stats[Chip::WHITE])
                ? Chip::BLACK
                : (stats[Chip::BLACK] > stats[Chip::WHITE])
                    ? Chip::WHITE
                    : Chip::NONE;

        ostringstream o;
        o << "Game finished. ";
        if (winner != Chip::NONE) {
            o << "Player " << engine->getPlayerNumber(winner)
            << " (" << *winner << ") "
            << "is winner. Congratulations.";
        } else {
            o << "Draw.";
        }
        lGameLog->addLine(o.str());
        lGameLog->addLine("Press <<START>> to start the game!");
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
    }

    void onError(ReversiEngine *engine, exception &error) override {
        lGameLog->addLine(error.what());
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
    }
};

struct StartStopBtnListener : ButtonListener {
    bool onClicked() override {
        if (engine->isStarted()) {
            engine->finishGame();
        } else {
            engine->startGame();
        }
        return true;
    }
};

//---------------------------

void initApp(HWND parent) {
    MAIN_WINDOW_HWND = parent;
    engine = new ReversiEngine();
    engine->setObserver(new GameObserver());
    // init button field indexes
    bfField = new ButtonsField(60, 60, 50, 20, 4);
    // todo engine
    bfField->setListener(new ButtonFieldListenerImpl(nullptr));

    lPlayerColor = new Label(500, 60, 150, 20);
    lPlayerColor->setText("Your color:");
    rbgPlayerColor = new RadioButtonGroup(500, 90, {"Black (goes first)", "White"});
    rbgPlayerColor->setListener(new PlayerColorListener());

    lSecondPlayer = new Label(500, 170, 150, 20);
    lSecondPlayer->setText("Second player:");
    rbgSecondPlayer = new RadioButtonGroup(500, 200, {"AI", "Human"});
    rbgSecondPlayer->setListener(new SecondPlayerListener());

    lGameLog = new MultilineLabel(60, bfField->getViewRect().bottom + 10, 450, 40, 4);
    lGameLog->addLine("Press <<START>> to start the game!");

    lScore = new Label(60, 20, 450, 40, true, false);
    lScore->setText("Player 1 (BLACK) 20 : 25 (WHITE) Player 2");

    auto r = rbgSecondPlayer->getViewRect();
    btnStartStop = new Button(r.left, r.top + 200, 100, 61);
    btnStartStop->setListener(new StartStopBtnListener());
    btnStartStop->setText("START");

    drawables.push_back(lPlayerColor);
    drawables.push_back(rbgPlayerColor);
    drawables.push_back(lSecondPlayer);
    drawables.push_back(rbgSecondPlayer);
    drawables.push_back(lGameLog);
    drawables.push_back(lScore);
    drawables.push_back(btnStartStop);
    // hard object must be the last
    drawables.push_back(bfField);

    clickables.push_back(rbgPlayerColor);
    clickables.push_back(rbgSecondPlayer);
    clickables.push_back(btnStartStop);
    clickables.push_back(bfField);
}


LRESULT lpfnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  {

    bool useDefaultProc = true;

    switch(msg) {
        case WM_PAINT: {
            RECT windowRect;
            GetClientRect(hwnd, &windowRect);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // paint buttons
            for (Drawable* v: drawables) {
                v->onPaint(hdc);
            }
            EndPaint(hwnd, &ps);
            useDefaultProc = false;
            break;
        }
        case WM_MOUSEMOVE: {
            int pX = GET_X_LPARAM(lParam);
            int pY = GET_Y_LPARAM(lParam);
            bool hasChanges = false;
            hasChanges |= bfField->onMouseMove(pX, pY);
            if (hasChanges) {
                RECT changedRect = bfField->getViewRect();
                InvalidateRect(hwnd, &changedRect, NULL);
            }

            useDefaultProc = false;
            break;
        }
        case WM_LBUTTONDOWN: {
            int pX = GET_X_LPARAM(lParam);
            int pY = GET_Y_LPARAM(lParam);

            bool clickedAny = false;
            RECT changedRect;
            GetClientRect(hwnd, &changedRect);
            InvalidateRect(hwnd, &changedRect, NULL);

            for(Clickable* view: clickables) {
                if (view->onClick(pX, pY)) {
                    clickedAny = true;
                    changedRect = view->getViewRect();
                    break;
                }
            }
            if (clickedAny) {
                InvalidateRect(hwnd, &changedRect, NULL);
            }

            useDefaultProc = false;
            break;
        }
        case WM_CREATE:
            initApp(hwnd);
            useDefaultProc = false;
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            useDefaultProc = false;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            useDefaultProc = false;
            break;
        case WM_ERASEBKGND: { // draws background http://deadbeef.narod.ru/work/articles/flicker.htm
            // DefWindowProc will clear the window using the WNDCLASSEX.hbrBackground member
            LRESULT result = DefWindowProc (hwnd, msg, wParam, lParam);
            useDefaultProc = false;
            break;
        }
    }

    if (useDefaultProc) {
        return DefWindowProc (hwnd, msg, wParam, lParam);
    }
    return 0;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow){
    MSG Msg;
    HWND hwnd;
    WNDCLASSEX wc;

    wc.lpszMenuName  = NULL;
    wc.hInstance     = hInstance;
    wc.lpszClassName = g_szClassName;
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.cbClsExtra    = wc.cbWndExtra = 0;
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpfnWndProc   = lpfnWndProc;

    if(!RegisterClassEx(&wc))    {
        MessageBox(NULL, "Window Registration Failed", "Error",   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindow(g_szClassName,
                        "ReversiGame",
                        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // disable resize
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);



    if(hwnd == NULL)    {
        MessageBox(NULL, "Window Creation Failed", "Error",   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
