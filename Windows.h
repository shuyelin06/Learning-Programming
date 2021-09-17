#pragma once

// Sets the system to UNICODE
#ifndef UNICODE 
#define UNICODE
#endif

// Necessary Files
#include <windows.h> // Needed to write windows
#include <tchar.h> // Needed for converstions for window names

/*
 Code for the main window
 */
// Instantiates all of the windows
void InstantiateMainWindow(HINSTANCE hInstance);
// WindowProc defines the behavior of the window (how it interacts with the user, appearance, etc)
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);