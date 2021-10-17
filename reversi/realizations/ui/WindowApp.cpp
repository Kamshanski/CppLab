
#include "includeAll.h"

using namespace std;

//---------------------------
const char g_szClassName[] = "Reversi Game";

ButtonsField* bfField = nullptr;
RadioButtonGroup* rbgPlayerColor = nullptr;
RadioButtonGroup* rbgSecondPlayer = nullptr;
Label* lPlayerColor = nullptr;
Label* lSecondPlayer = nullptr;
Label* lGameMessages = nullptr;

vector<Drawable*> drawables;
vector<Clickable*> clickables;


//---------------------------

struct PlayerColorListener : RadioButtonGroupListener {
    bool onSelected(int idNew, int idPrev, vector<string> &options) override {
        return true;
    }
};

struct SecondPlayerListener : RadioButtonGroupListener {
    bool onSelected(int idNew, int idPrev, vector<string> &options) override {
        return true;
    }
};

//---------------------------

void initApp(HWND parent) {
    // init button field indexes
    bfField = new ButtonsField(new ButtonFieldListenerImpl(nullptr));

    lPlayerColor = new Label(500, 60, 150, 20);
    lPlayerColor->setText("Your color:");
    rbgPlayerColor = new RadioButtonGroup(500, 90, {"Black (goes first)", "White"});
    rbgPlayerColor->setListener(new PlayerColorListener());

    lSecondPlayer = new Label(500, 170, 150, 20);
    lSecondPlayer->setText("Second player:");
    rbgSecondPlayer = new RadioButtonGroup(500, 200, {"AI", "Human"});
    rbgSecondPlayer->setListener(new SecondPlayerListener());

    lGameMessages = new Label(60, 500, 450, 40);
    lGameMessages->setText("Hi! Start the game!");

    drawables.push_back(bfField);
    drawables.push_back(lPlayerColor);
    drawables.push_back(rbgPlayerColor);
    drawables.push_back(lSecondPlayer);
    drawables.push_back(rbgSecondPlayer);
    drawables.push_back(lGameMessages);

    clickables.push_back(rbgPlayerColor);
    clickables.push_back(rbgSecondPlayer);
    clickables.push_back(bfField);
}

bool processClick(int pX, int pY) {
    bool needToRedraw = false;
    needToRedraw |= bfField->onClick(pX, pY);
    needToRedraw |= rbgPlayerColor->onClick(pX, pY);
    needToRedraw |= rbgSecondPlayer->onClick(pX, pY);

//    string text = ("You pressed button " + to_string(LOWORD(btnId)));
//    MessageBox(parent, text.c_str(), "MessageBox", MB_OK | MB_ICONWARNING);
    return needToRedraw;
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

            for(Clickable* view: clickables) {
                if (view->onClick(pX, pY))
                    break;
            }

            RECT windowRect;
            GetClientRect(hwnd, &windowRect);
            InvalidateRect(hwnd, &windowRect, NULL);

            useDefaultProc = false;
            break;
        }
        case WM_LBUTTONDOWN: {
            int pX = GET_X_LPARAM(lParam);
            int pY = GET_Y_LPARAM(lParam);
            bool hasChanges = processClick(pX, pY);
            if (hasChanges) {
                RECT windowRect;
                GetClientRect(hwnd, &windowRect);
                InvalidateRect(hwnd, &windowRect, NULL);
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
