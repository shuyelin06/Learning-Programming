#ifndef UNICODE 
#define UNICODE
#endif

/*
The Win32 library is the native builder for Windows Applications. 
Because of this, it is the fastest, though it can be hard to learn.
*/

// The window and tchar inclusions are necessary (windows for the application, tchar for the wchar_t datatype)
#include <windows.h> 
#include <tchar.h>

// WindowProc defines the behavior of the window (how it interacts with the user, appearance, etc)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*
WinMain is the entry-point function (where the script will begin running from). The parameters will be explained below:
    hInstance: Used to identify the .exe file where the window is being run from
    hPrevInstance: Discontinued; has no meaning.
    
*/
// https://stackoverflow.com/questions/61570603/can-not-compile-win32-c-using-mingw
// For some reason, PWSTR --> PSTR for the application to actually open.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow){
    const wchar_t Test_Window[] = L"Application Window"; // Regitering a window class

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = Test_Window; // Is the wchar_t variable we previously defined

    // This method registers the class, and we register it from its memory address (& operator)
    RegisterClass(&wc);

    // Creating a window
    HWND hwnd = CreateWindowEx(
        0, // Window styles
        Test_Window, // Window class
        L"Test Window Class", // Window text
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        // CW_USEDEFAULT probably stands for some defined default value for windows.

        NULL, // Parent window
        NULL, // Menu
        hInstance, // Instance handle (???)
        NULL // Extra application data
    );

    if(hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow); // Somehow displays the window?


    // Run the message loop ?

    MSG msg = {}; // Probably what the window displays
    while(GetMessage(&msg, NULL, 0, 0)) // Get the message from the window (using its memory address so we can change it in other parts of the program)
    {
        TranslateMessage(&msg); // Translates keystrokes into characters
        DispatchMessage(&msg); // 
    }

    return 0;
}

// Defines the behavior of the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){ // Message handling to tell the window what to do
        case WM_DESTROY: // On destroy comand, delete the window
            PostQuitMessage(0);
            return 0;
        
        case WM_PAINT: // On paint command, draw ? the window
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
                EndPaint(hwnd, &ps);
            }
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}