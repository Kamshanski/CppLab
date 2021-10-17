
#include "includeAll.h"

using namespace std;

//---------------------------
const char g_szClassName[] = "Reversi Game";

ButtonsField* btnField = nullptr;

LONG rLeft = 10, rTop = 10, rRight = 20, rBottom = 160;

//---------------------------

void initApp(HWND parent) {
    // init button field indexes
    btnField = new ButtonsField(new ButtonFieldListenerImpl(nullptr));
}

void processBtnClick(int btnId, HWND parent) {
//    btnField->onClick(btnId);

//    string text = ("You pressed button " + to_string(LOWORD(btnId)));
//    MessageBox(parent, text.c_str(), "MessageBox", MB_OK | MB_ICONWARNING);
}

LRESULT lpfnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  {
    HDC hdc;
    TEXTMETRIC tm;
    PAINTSTRUCT ps;

    bool useDefaultProc = true;

    switch(msg)    {
        case WM_CREATE:
            initApp(hwnd);
            useDefaultProc = false;
            break;
        case WM_CLOSE:
//            if (MessageBox(NULL, "Are you sure you want to quit?",
//                           "Confirmation", MB_ICONQUESTION | MB_YESNO) == IDYES)
                DestroyWindow(hwnd);
            break;
        case WM_COMMAND: {
            bool isButton = (HIWORD(wParam)) == 0;
            if (isButton) {
                int btnId = (int) LOWORD(wParam);
                rLeft += 10;
                rRight += 10;
                RECT rq;
                GetClientRect(hwnd, &rq);
                RedrawWindow(hwnd, NULL, NULL, NULL);
                processBtnClick(btnId, hwnd);
                InvalidateRect(hwnd, &rq, NULL);
                SendMessage(hwnd, WM_PAINT, wParam, lParam);
            }
            return TRUE;
            useDefaultProc = false;
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
//        case WM_DRAWITEM: {
//            bool isButton = (HIWORD(wParam)) == 0;
//            if (isButton) {
//                int btnId = (int) LOWORD(wParam);
//                LPDRAWITEMSTRUCT item = (LPDRAWITEMSTRUCT)lParam;
//                return btnField->onPaint();
//            }
//
//            useDefaultProc = false;
//            break;
//        }
        case WM_PAINT: {
            RECT windowRect;
            hdc = BeginPaint(hwnd, &ps);

            // clear window with white
            GetClientRect(hwnd, &windowRect);
//            FillRect(hdc, &windowRect, reinterpret_cast <HBRUSH> (GetStockObject(WHITE_BRUSH)));

            // paint buttons
            btnField->onPaint(hdc);
//            DrawText(hdc, TEXT ("Native Windows Development with CygWin and CLion."),
//                     -1, &windowRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

//            // draw the black bar
//            RECT barRect = {rLeft, rTop, rRight, rBottom};
//
//            FillRect(hdc, &barRect, reinterpret_cast <HBRUSH> (GetStockObject(BLACK_BRUSH)));

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
                cout<<"Changed\n";
            }
            useDefaultProc = false;
            break;
        }
        case WM_ERASEBKGND: {
            // here we draw the black line between the two buttons using a solid colour filled rectangle.
            // this can just as easily be done in the WM_PAINT handler
            // DefWindowProc will clear the window using the WNDCLASSEX.hbrBackground member
            LRESULT result = DefWindowProc (hwnd, msg, wParam, lParam);
            useDefaultProc = false;
//
//            // get the DC to draw with
//            HDC dc = reinterpret_cast <HDC> (wParam);
//
//            // draw the black bar
//            RECT rect = {rLeft, rTop, rRight, rBottom};
//
//            FillRect (dc, &rect, reinterpret_cast <HBRUSH> (GetStockObject (BLACK_BRUSH)));
            break;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    if (useDefaultProc) {
        DefWindowProc (hwnd, msg, wParam, lParam);
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
    wc.style         = CS_HREDRAW | CS_VREDRAW ;
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
