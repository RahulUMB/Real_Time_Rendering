#pragma once

#include <iostream>
#include <Windows.h>

#include "../Window.hpp"

class Win32Window : public Window
{
private:
    int m_winXPos, m_winYPos;
    bool bDone = false;
    bool bFullScreen = false;

    MSG m_msg = {};
    HWND m_hWnd;
    HINSTANCE m_hInstance;
    HICON m_hIcon;
    DWORD dwStyle;
    WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

public:
    bool Initialize(int width, int height) override;
    void UnInitialize() override;

    void ShowWindow() override;
    void Run() override;

    void FullScreen() override;

    HWND GetHWND() { return m_hWnd; }

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};
