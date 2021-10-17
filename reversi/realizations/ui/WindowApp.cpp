
#include "includeAll.h"

using namespace std;

//---------------------------
const char g_szClassName[] = "Reversi Game";

ButtonsField* btnField = nullptr;
RadioButtonGroup* radioBtnGroup = nullptr;


//---------------------------

void initApp(HWND parent) {
    // init button field indexes
    btnField = new ButtonsField(new ButtonFieldListenerImpl(nullptr));
    radioBtnGroup = new RadioButtonGroup(500, 20, {"Option 1", "Very long option two"});
}

bool processClick(int pX, int pY) {
    bool needToRedraw = false;
    needToRedraw |= radioBtnGroup->onClick(pX, pY);
    needToRedraw |= btnField->onClick(pX, pY);

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
            btnField->onPaint(hdc);
            radioBtnGroup->onPaint(hdc);

            EndPaint(hwnd, &ps);
            useDefaultProc = false;
            break;
        }
        case WM_MOUSEMOVE: {
            int pX = GET_X_LPARAM(lParam);
            int pY = GET_Y_LPARAM(lParam);
            bool hasChanges = btnField->onMouseMove(pX, pY);
            if (hasChanges) {
                RECT windowRect;
                GetClientRect(hwnd, &windowRect);
                InvalidateRect(hwnd, &windowRect, NULL);
            }
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
