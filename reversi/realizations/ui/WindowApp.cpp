#include "includeAll.h"

using namespace std;

const char g_szClassName[] = "bonafideideasWindowClass";
int p = 0;
HWND btn;

LRESULT lpfnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  {
    HDC hdc;
    RECT rect;
    TEXTMETRIC tm;
    PAINTSTRUCT ps;

    switch(msg)    {
        case WM_CREATE:
            /* при создании окна внедряем в него кнопочку */
            CreateWindow("button","My button",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
                         5,5,100,20,hwnd,(HMENU)1,NULL,NULL);
            btn = CreateWindow("button","My button2",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
                               50,50,100,20,hwnd,(HMENU)2,NULL,NULL);
            /* стиль WS_CHILD означает, что это дочернее окно и для него
             вместо дескриптора меню будет передан целочисленный идентификатор,
             который будет использоваться дочерним окном для оповещения
             родительского окна через WM_COMMAND */
            return 0;
        case WM_CLOSE:
//            if (MessageBox(NULL, "Are you sure you want to quit?",
//                           "Confirmation", MB_ICONQUESTION | MB_YESNO) == IDYES)
                DestroyWindow(hwnd);
            break;
        case WM_COMMAND:
            /* нажата наша кнопочка? */
            if ((HIWORD(wParam)==0) && (LOWORD(wParam)==1)) {
                MessageBox(hwnd, "You pressed my button", "MessageBox", MB_OK | MB_ICONWARNING);
            } else if ((HIWORD(wParam)==0) && (LOWORD(wParam)==2)) {
                string s = "TEXT";
                s += to_string(p++);
                SetWindowText(btn, s.c_str());
                UpdateWindow(hwnd);
            }

            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;
            GetClientRect (hwnd, &rect) ;
            DrawText (hdc, TEXT ("Native Windows Development with CygWin and CLion."),
                      -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
            EndPaint (hwnd, &ps) ;
            return 0 ;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
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
    wc.cbClsExtra      = wc.cbWndExtra  = 0;
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
                        "EX 4",
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
