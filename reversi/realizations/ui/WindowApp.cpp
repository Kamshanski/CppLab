
#include "includeAll.h"

using namespace std;

//---------------------------
HWND MAIN_WINDOW_HWND;
const char g_szClassName[]              = "Reversi Game";
const string VERTICAL_FIELD_INDEXES[]   = {"1", "2", "3", "4", "5", "6", "7", "8"};
const string HORIZONTAL_FIELD_INDEXES[]     = {"A", "B", "C", "D", "E", "F", "G", "H"};


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
            return engine->setFirstBlackSecondWhite();
        } else {
            return engine->setFirstWhiteSecondBlack();
        }
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
        o << "Player 1 (" << *engine->getPlayersChip(1) << ") "
          << stats[Chip::BLACK]
          << " : "
          << stats[Chip::WHITE]
          << " (" << *engine->getPlayersChip(2) << ") Player 2";
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
          << "moved on "
          << '(' << VERTICAL_FIELD_INDEXES[move.getX()] << ", " << HORIZONTAL_FIELD_INDEXES[move.getY()] << ')' << ". "
          << "Number of captured enemy's chips: " << switchedList->size();
        lGameLog->addLine(o.str());
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
    }

    void onStarted(ReversiEngine *engine) override {
        fetchField();
        ostringstream o;
        o << "Game started.";
        lGameLog->addLine(o.str());
        btnStartStop->setText("FINISH");
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
        redrawRectangle(MAIN_WINDOW_HWND, btnStartStop->getViewRect());
        engine->analyseGame();
    }

    void onFinished(ReversiEngine *engine, Field *snap) override {
        auto stats = snap->getStatistics();
        Chip* winner = (stats[Chip::BLACK] > stats[Chip::WHITE])
                ? Chip::BLACK
                : (stats[Chip::BLACK] < stats[Chip::WHITE])
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
        btnStartStop->setText("START");
        redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
        redrawRectangle(MAIN_WINDOW_HWND, btnStartStop->getViewRect());
    }

    void onError(ReversiEngine *engine, exception &error) override {
        auto ime = dynamic_cast<IllegalMoveException*>(&error);
        if ((ime) != nullptr) {
            ostringstream  o;
            o << "Illegal move with "
               << '\"' << *ime->chip << '\"'
               << " on position "
               << '(' << VERTICAL_FIELD_INDEXES[ime->x] << ", " << HORIZONTAL_FIELD_INDEXES[ime->y] << ')';
            lGameLog->addLine(o.str());
        } else {
        }
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

struct FieldListener: ButtonsFieldListener {
    void clearButtons(ButtonsField* field) {
        for (int i = 0; i < ButtonsField::BTN_FIELD_SIZE; ++i) {
            for (int j = 0; j < ButtonsField::BTN_FIELD_SIZE; ++j) {
                field->setButtonClear(i, j);
            }
        }
    }


    void onMouseEnteredButton(ButtonsField *field, int i, int j) override {
        clearButtons(field);
        if (engine->isStarted()) {
            Chip* chip = engine->getChipOn({i, j});
            if (chip == Chip::NONE) {
                field->setButtonSelected(i, j);
                PointsList* aims = engine->getAvailableAimsForMove({i, j});
                if (aims != nullptr) {
                    if (!aims->empty()) {
                        for (Point* p: *aims) {
                            field->setButtonHighlighted(p->getX(), p->getY());
                        }
                    }
                }
            }
        } else {
            field->setButtonSelected(i, j);
        }

    }

    void onMouseEscapedButton(ButtonsField *field) override {
        clearButtons(field);
    }

    void onClickOnButton(ButtonsField *field, int i, int j) override {
        if (engine->isStarted()) {
            engine->move({i, j}, engine->getCurrentPlayer());
            clearButtons(field);
            field->setButtonSelected(i, j);
        }
    }
};

//---------------------------

void initApp(HWND parent) {
    MAIN_WINDOW_HWND = parent;

    engine = new ReversiEngine();
    engine->setObserver(new GameObserver());
    // init button field indexes
    bfField = new ButtonsField(60, 60, 50, 20, 4);
    bfField->setListener(new FieldListener());
    clickables.push_back(bfField);
    drawables.push_back(bfField);

    int afterFieldX = 530;
    lPlayerColor = new Label(afterFieldX, 60, 150, 20);
    lPlayerColor->setText("Your color:");
    drawables.push_back(lPlayerColor);

    rbgPlayerColor = new RadioButtonGroup(afterFieldX, 90, {"Black (goes first)", "White"});
    rbgPlayerColor->setListener(new PlayerColorListener());
    clickables.push_back(rbgPlayerColor);
    drawables.push_back(rbgPlayerColor);

    lSecondPlayer = new Label(afterFieldX, 170, 150, 20);
    lSecondPlayer->setText("Second player:");
    drawables.push_back(lSecondPlayer);
    rbgSecondPlayer = new RadioButtonGroup(afterFieldX, 200, {"AI", "Human"});
    rbgSecondPlayer->setListener(new SecondPlayerListener());
    drawables.push_back(rbgSecondPlayer);
    clickables.push_back(rbgSecondPlayer);

    auto r = rbgSecondPlayer->getViewRect();
    btnStartStop = new Button(afterFieldX, r.top + 200, 100, 61);
    btnStartStop->setListener(new StartStopBtnListener());
    btnStartStop->setText("START");
    drawables.push_back(btnStartStop);
    clickables.push_back(btnStartStop);

    lGameLog = new MultilineLabel(60, bfField->getViewRect().bottom + 30, 800, 40, 4);
    lGameLog->addLine("Press <<START>> to start the game!");
    drawables.push_back(lGameLog);

    lScore = new Label(60, 10, 450, 40, true, false);
    lScore->setText("Player 1 (BLACK) XX : XX (WHITE) Player 2");
    drawables.push_back(lScore);


    int lIndexWidth = 10;
    auto chipRect = bfField->getChipViewRect(0, 0);
    int lIndexHeight = abs(chipRect.top - chipRect.bottom);

    for (int i = 0; i < ButtonsField::BTN_FIELD_SIZE; ++i) {
        int rX = bfField->getViewRect().left - lIndexWidth*2;
        int rY = bfField->getChipViewRect(i, 0).top;

        int lX = bfField->getViewRect().right + lIndexWidth;
        int lY = rY;

        auto lLeft = new Label(rX, rY, lIndexWidth, lIndexHeight);
        lLeft->setText(VERTICAL_FIELD_INDEXES[i]);
        drawables.push_back(lLeft);

        auto lRight = new Label(lX, lY, lIndexWidth, lIndexHeight);
        lRight->setText(VERTICAL_FIELD_INDEXES[i]);
        drawables.push_back(lRight);
    }

    for (int i = 0; i < ButtonsField::BTN_FIELD_SIZE; ++i) {
        int centerX = (bfField->getChipViewRect(0, i).left + bfField->getChipViewRect(0, i).left) / 2;
        int tX = centerX + lIndexWidth/2;
        int tY = bfField->getViewRect().top - lIndexHeight - 4;

        int bX = tX;
        int bY = bfField->getViewRect().bottom + 4;

        auto lTop = new Label(tX, tY, lIndexWidth, lIndexHeight, true);
        lTop->setText(HORIZONTAL_FIELD_INDEXES[i]);
        drawables.push_back(lTop);

        auto lBottom = new Label(bX, bY, lIndexWidth, lIndexHeight, true);
        lBottom->setText(HORIZONTAL_FIELD_INDEXES[i]);
        drawables.push_back(lBottom);
    }
}

// TODO продебажить пропуски
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

    if (!RegisterClassEx(&wc))    {
        MessageBox(NULL, "Window Registration Failed", "Error",   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindow(g_szClassName,
                        "ReversiGame",
                        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // disable resize
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);


    if (hwnd == NULL)    {
        MessageBox(NULL, "Window Creation Failed", "Error",   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG Msg;
    while(GetMessage(&Msg, NULL, 0, 0) > 0)    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
