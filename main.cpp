#include "Windows.h" // Defines our windows

// https://dev.to/giovannicodes/setup-sdl2-with-visual-studio-code-and-mingw64-on-windows-14c5#:~:text=%20Setup%20SDL2%20with%20Visual%20Studio%20Code%20and,and%20cross%20your%20fingers.%20You%20should...%20More%20
/* 
Notes to Run the Program
https://stackoverflow.com/questions/61570603/can-not-compile-win32-c-using-mingw
For some reason, PWSTR --> PSTR for the application to actually open. 
  
"cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
"cpp": "cd $dir && g++ *.cpp -o $fileNameWithoutExt && $dir$fileNameWithoutExt",  
*/

/*
The Win32 library is the native builder for Windows Applications. 
Because of this, it is the fastest, though it can be hard to learn.

WinMain is the entry-point function (where the script will begin running from). The parameters will be explained below:
    hInstance: Used to identify the .exe file where the window is being run from
    hPrevInstance: Discontinued; has no meaning.
    
*/

// Main function where the program will be run from
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow){
    InstantiateMainWindow(hInstance);

    // Creates an instance of a window (more information can be found here: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa)
    HWND hwnd = CreateWindowEx(
        0, // Window styles
        L"Main Window", // Window class
        L"Main Application Window", // Window title text
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        // CW_USEDEFAULT probably stands for some defined default value for windows.

        NULL, // Parent window
        NULL, // Menu
        hInstance, // Instance handle (???)
        NULL // Extra application data (can be used to pass a data structure to the window)
    );
    if(hwnd == NULL) return 0; // If the function fails, it will return 0. If it doesn't it will return a handle for the window to be called

    
    // Displays the window; hwnd is the window, and nCmdShow is a minimize/maximization of a window (passed by the operating system)
    ShowWindow(hwnd, nCmdShow); 


    // Run a message loop, so the window can interact with the user and operating system.
    MSG msg = {}; 
    // As long as the message is not 0, the while loop runs true.
    while(GetMessage(&msg, NULL, 0, 0)) // Get a message from the window queue (which holds the messages for every window created in this program). If there are no messages, WAIT until one is sent.
    {
        // Almost alawys, pass the message structure to these two messages.
        TranslateMessage(&msg); // Translates keystrokes into characters (don't really need to know how this works)
        DispatchMessage(&msg); // Tells the operating system to call the window procedure of the window that is the target of the message
    }

    // End of program
    return 0;
}