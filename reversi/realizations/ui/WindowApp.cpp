#include "includeAll.h"

using namespace std;

//---------------------------

int WINDOW_WIDTH = 710;
int WINDOW_HEIGHT = 700;
int WINDOW_X = 50;
int WINDOW_Y = 60;

//---------------------------
const char g_szClassName[]              = "Reversi Game";

const char* VERTICAL_FIELD_INDEXES[]    = {"1", "2", "3", "4", "5", "6", "7", "8"};
const char* HORIZONTAL_FIELD_INDEXES[]  = {"A", "B", "C", "D", "E", "F", "G", "H"};

const char* LABEL_COLOR             = "Your color:";
const char* OPTION_BLACK            = "Black (goes first)";
const char* OPTION_WHITE            = "White";
const char* LABEL_SECOND_PLAYER     = "Second player:";
const char* OPTION_AI               = "AI";
const char* OPTION_HUMAN            = "Human";

const char WINDOW_TITLE[]           = "ReversiGame";

const char* BTN_START               = "START";
const char* BTN_FINISH              = "FINISH";

const char* LOG_PRESS_START         = "Press <<START>> to start the game!";
const char* LOG_GAME_STARTED        = "Game started.";

const char SCORE_TXT[]              = "Player 1 (%s) %d : %d (%s) Player 2";

const char LOG_SKIPPED[]            = "Player %s skipped move.";
const char LOG_MOVED[]              = "Player %d (%s) moved on (%s, %s). Number of captured enemy's chips: %d";
const char LOG_ILLEGAL_MOVE[]       = "Illegal move with '%s' on position (%s, %s)";
const char LOG_WINNER[]             = "Game finished. Player %d (%s) is winner. Congratulations.";
const char LOG_DRAW[]               = "Game finished. Draw.";

//---------------------------
HWND MAIN_WINDOW_HWND;

ButtonsField* bfField = nullptr;

RadioButtonGroup* rbgPlayerColor = nullptr;
Label* lPlayerColor = nullptr;

RadioButtonGroup* rbgSecondPlayer = nullptr;
Label* lSecondPlayer = nullptr;

Label* lScore = nullptr;

MultilineLabel* lGameLog = nullptr;

Button* btnStartStop = nullptr;

vector<Drawable*> drawables;
vector<Clickable*> clickables;

ReversiEngine* engine;
ReversiAi ai;

bool isAiSecondPLayer = true;

//---------------------------
// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template<typename ... Args>
string format( const string& format, Args ... args ) {
    size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size <= 0 ){ throw runtime_error( "Error during formatting." ); }
    unique_ptr<char[]> buf( new char[ size ] );
    snprintf( buf.get(), size, format.c_str(), args ... );
    return string{ buf.get(), buf.get() + size - 1 }; // We don't want the '\0' inside
}

void redrawRectangle(HWND hwnd, RECT rect) {
    InvalidateRect(hwnd, &rect, NULL);
}

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

void printToGameLog(string msg) {
    lGameLog->addLine(msg);
    redrawRectangle(MAIN_WINDOW_HWND, lGameLog->getViewRect());
}

void printScoreText(string msg) {
    lScore->setText(msg);
    redrawRectangle(MAIN_WINDOW_HWND, lScore->getViewRect());
}

void displayScore(map<Chip*, int>& stats) {
    string msg = format(SCORE_TXT,
            engine->getPlayersChip(1)->cstr(),
            stats[Chip::BLACK],
            stats[Chip::WHITE],
            engine->getPlayersChip(2)->cstr());
    printScoreText(msg);
}

void setGameButtonText(string text) {
    btnStartStop->setText(std::move(text));
    redrawRectangle(MAIN_WINDOW_HWND, btnStartStop->getViewRect());
}

void clearButtons(ButtonsField* field) {
    for (int i = 0; i < ButtonsField::BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < ButtonsField::BTN_FIELD_SIZE; ++j) {
            field->setButtonClear(i, j);
        }
    }
}
//---------------------------
struct PlayerColorListener : RadioButtonGroupListener {
    bool onSelected(int idNew, int idPrev, vector<string> &options) override {
        if (!engine->isStarted()) {
            if (idNew == 0) {
                return engine->setFirstBlackSecondWhite();
            } else {
                return engine->setFirstWhiteSecondBlack();
            }
        }
        return false;
    }
};

struct SecondPlayerListener : RadioButtonGroupListener {
    bool onSelected(int idNew, int idPrev, vector<string> &options) override {
        if (!engine->isStarted()) {
            isAiSecondPLayer = (idNew != 0);
            return true;
        }
        return false;
    }
};

class GameObserver : public GameListener {
public:

    void onSwitchPlayers(ReversiEngine *engine) override {
        fetchField();
        auto snap = engine->getSnapshot();
        auto stats = snap->getStatistics();
        displayScore(stats);
        delete snap;
    }

    void onSkipped(ReversiEngine *engine, Chip *player) override {
        string msg = format(LOG_SKIPPED, player->cstr());
        printToGameLog(msg);
    }

    void onMoved(ReversiEngine *engine, Chip *player, Point move, PointsList *switchedList) override {
        string msg = format(LOG_MOVED,
               engine->getPlayerNumber(player),
               player->cstr(),
               VERTICAL_FIELD_INDEXES[move.getX()],
               HORIZONTAL_FIELD_INDEXES[move.getY()],
               switchedList->size());
        printToGameLog(msg);
    }

    void onWaitingForMove(ReversiEngine *engine) override {
        if (engine->isStarted() && isAiSecondPLayer) {
            int humanPlayer = rbgPlayerColor->getSelection();
            Chip* humanChip = (humanPlayer == 0) ? Chip::BLACK : Chip::WHITE;
            Chip* aiChip = humanChip->getEnemy();
            if (aiChip == engine->getCurrentPlayer()) {
                Point aiMove = ai.chooseMove(engine, aiChip);
                engine->move(aiMove, aiChip);
            }
        }
    }

    void onStarted(ReversiEngine *engine) override {
        fetchField();
        auto snap = engine->getSnapshot();
        auto stat = snap->getStatistics();
        displayScore(stat);
        printToGameLog(LOG_GAME_STARTED);
        setGameButtonText(BTN_FINISH);
        delete snap;
    }

    void onFinished(ReversiEngine *engine, Field *snap) override {
        auto stats = snap->getStatistics();
        Chip* winner = (stats[Chip::BLACK] > stats[Chip::WHITE])
                ? Chip::BLACK
                : (stats[Chip::BLACK] < stats[Chip::WHITE])
                    ? Chip::WHITE
                    : Chip::NONE;
        string msg = (winner == Chip::NONE)
                ? LOG_DRAW
                : format(LOG_WINNER,
                         engine->getPlayerNumber(winner),
                         winner->cstr());
        displayScore(stats);
        setGameButtonText(BTN_START);
        printToGameLog(msg);
        printToGameLog(LOG_PRESS_START);
    }

    void onError(ReversiEngine *engine, exception &error) override {
        auto ime = dynamic_cast<IllegalMoveException*>(&error);
        if ((ime) != nullptr) {
            string msg = format(LOG_ILLEGAL_MOVE,
                                ime->chip->cstr(),
                                VERTICAL_FIELD_INDEXES[ime->x],
                                HORIZONTAL_FIELD_INDEXES[ime->y]);
            printToGameLog(msg);
        } else {
            printToGameLog(error.what());
        }
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
    lPlayerColor->setText(LABEL_COLOR);
    drawables.push_back(lPlayerColor);

    rbgPlayerColor = new RadioButtonGroup(afterFieldX, 90, {OPTION_BLACK, OPTION_WHITE});
    rbgPlayerColor->setListener(new PlayerColorListener());
    clickables.push_back(rbgPlayerColor);
    drawables.push_back(rbgPlayerColor);

    lSecondPlayer = new Label(afterFieldX, 170, 150, 20);
    lSecondPlayer->setText(LABEL_SECOND_PLAYER);
    drawables.push_back(lSecondPlayer);
    rbgSecondPlayer = new RadioButtonGroup(afterFieldX, 200, {OPTION_AI, OPTION_HUMAN});
    rbgSecondPlayer->setListener(new SecondPlayerListener());
    drawables.push_back(rbgSecondPlayer);
    clickables.push_back(rbgSecondPlayer);

    auto r = rbgSecondPlayer->getViewRect();
    btnStartStop = new Button(afterFieldX, r.top + 200, 100, 61);
    btnStartStop->setListener(new StartStopBtnListener());
    btnStartStop->setText(BTN_START);
    drawables.push_back(btnStartStop);
    clickables.push_back(btnStartStop);

    lGameLog = new MultilineLabel(60, bfField->getViewRect().bottom + 30, 800, 40, 4);
    lGameLog->addLine(LOG_PRESS_START);
    drawables.push_back(lGameLog);

    lScore = new Label(60, 10, 450, 40, true, false);
    lScore->setText(LOG_PRESS_START);
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

//----------------------------
LRESULT lpfnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  {

    bool useDefaultProc = true;

    switch(msg) {
        case WM_PAINT: {    // double buffering applied
            RECT windowRect;
            GetClientRect(hwnd, &windowRect);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Create off-screen DC for double buffering
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmMem = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
            HANDLE hOld   = SelectObject(hdcMem, hbmMem);

            // Fill screen with white
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, Color::WHITE);
            SelectObject(hdc, GetStockObject(DC_PEN));
            SetDCPenColor(hdc, Color::WHITE);
            Rectangle(hdcMem, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

            // Paint views with hdcMem
            for (Drawable* v: drawables) {
                v->onPaint(hdcMem);
            }

            // Show built image on the screen
            BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdcMem, 0, 0, SRCCOPY);

            // Clear memory
            SelectObject(hdcMem, hOld);
            DeleteObject(hbmMem);
            DeleteDC    (hdcMem);

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
    }

    if (useDefaultProc) {
        return DefWindowProc (hwnd, msg, wParam, lParam);
    }
    return 0;
}

//-------------------------
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

    HWND hwnd = CreateWindow(
            g_szClassName,
            WINDOW_TITLE,
            WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // disable resize
            WINDOW_X, WINDOW_Y,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            NULL, NULL,
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
