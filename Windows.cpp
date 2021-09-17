#include "Windows.h"

void InstantiateMainWindow(HINSTANCE hInstance){
    const wchar_t Main_Window[]  = L"Main Window";

    // Creates a window class (a set of behaviors a group of windows might all have in common)
    WNDCLASS wc = {};

    // Settings for the WNDCLASS can be found here: https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
    wc.lpfnWndProc = MainWindowProc; // Points to the window procedure; the window's behavior
    wc.hInstance = hInstance; // Will always be hInstance, so the window stays open
    wc.lpszClassName = Main_Window; // Identifies the window class (MUST BE UNIQUE)


    // This method registers the class from its memory address (& operator)
    RegisterClass(&wc); // Registers the class 
};

/*
POST: Places a message on the message queue, to be dispatched through the message loop
SEND: The message skips the queue, and the operating system calls the window procedure immediately.
*/
// LResult is our program's response to a message (uMsg)
// Defines the behavior of the window - receives a message from the user/operating system, and performs some action based on it.
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    // Oftentimes, a typical window procedure is a long switch statement with cases for everything we want.
    switch(uMsg){ // Message handling to tell the window what to do
        case WM_DESTROY: // On destroy comand, delete the window
            PostQuitMessage(0); // Puts a WM_QUIT at the end of the message queue, which causes GetMessage to return 0 and signals the end of the application loop
            return 0;
        
        case WM_PAINT: // ALWAYS called by the system. Use WM_PRINT or WM_PRINTCLIENT message to force a window to print (from our application side)
        // The WM_PAINT message tells the operating system to REPAINT / REDRAW the portion of the window that needs to be updated
            {
                PAINTSTRUCT ps; // Contains information on the paint request
                HDC hdc = BeginPaint(hwnd, &ps); // Must be called to signal to windows the window is painting itself

                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1)); // &ps.rcPaint gives us the coordinates for the rectangle to fill in
                EndPaint(hwnd, &ps); // Signals to windows the window is done painting itself
            }
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};