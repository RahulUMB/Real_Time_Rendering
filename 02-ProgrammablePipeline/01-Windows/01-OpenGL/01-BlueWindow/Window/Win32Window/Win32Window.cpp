#include "Win32Window.hpp"

bool Win32Window::Initialize(int width, int height)
{
    if (!this->execLoop)
        return (false);

    WNDCLASSEX wndclass = {};

    this->m_hInstance = NULL;

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = this->m_hInstance;
    wndclass.lpszClassName = TEXT("Win32");
    wndclass.lpszMenuName = NULL;

    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_hIcon = (HICON)LoadImage(this->m_hInstance, TEXT("Resource\\Icon\\R.ico"), IMAGE_ICON, 204, 192, LR_LOADFROMFILE);
    wndclass.hIcon = m_hIcon;
    wndclass.hIconSm = m_hIcon;

    RegisterClassEx(&wndclass);

    this->m_winXPos = (::GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
    this->m_winYPos = (::GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

    this->m_hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        TEXT("Win32"),
        TEXT("WindowApplication...!!!"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        this->m_winXPos,
        this->m_winYPos,
        width,
        height,
        NULL, 
        NULL,
        this->m_hInstance,
        this);
    if (this->m_hWnd == INVALID_HANDLE_VALUE)
    {
        std::cout << "CreateWindowEx(...) failed with error: " << std::hex << this->m_hWnd << "." << std::endl;
        return (false);
    }
    
    return (true);
}

void Win32Window::UnInitialize()
{
    if (this->m_hIcon)
    {
        DestroyIcon(m_hIcon);
        m_hIcon = NULL;
    }

    return;
}

void Win32Window::ShowWindow()
{
    ::ShowWindow(this->m_hWnd, SW_SHOW);
}

void Win32Window::Run()
{
    while (this->bDone == false)
    {
        if (PeekMessage(&this->m_msg, NULL, 0, 0, PM_REMOVE))
        {
            if (this->m_msg.message == WM_QUIT)
            {
                this->bDone = true;
            }
            else
            {
                TranslateMessage(&this->m_msg);
                DispatchMessage(&this->m_msg);
            }
        }
        else
        {
            if (this->execLoop)
                this->execLoop(0.0f);
        }
    }

    return;
}

LRESULT CALLBACK Win32Window::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    Win32Window *pThis;

    if (iMsg == WM_NCCREATE)
    {
        pThis = static_cast<Win32Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetLastError(0);
        if(!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
        {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else
    {
        pThis = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        switch (iMsg)
        {
        case WM_ERASEBKGND:
            return (0);

        case WM_SIZE:
            if (pThis->resize)
                pThis->resize(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_KEYDOWN:
            switch(wParam)
            {
                case VK_ESCAPE:
                    DestroyWindow(hWnd);
                    break;
            }
            break;

        case WM_CHAR:
            switch (wParam)
            {
            case 'f':
            case 'F':
                pThis->FullScreen();
                break;
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hWnd);

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
    }

    return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void Win32Window::FullScreen()
{
    MONITORINFO mi;

    if (bFullScreen  == false)
    {
        dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            mi = { sizeof(MONITORINFO) };
            if (GetWindowPlacement(m_hWnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(m_hWnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(
                    m_hWnd, HWND_TOP,
                    mi.rcMonitor.left,
                    mi.rcMonitor.top,
                    mi.rcMonitor.right - mi.rcMonitor.left,
                    mi.rcMonitor.bottom - mi.rcMonitor.top,
                    SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        ShowCursor(FALSE);
        bFullScreen = true;
    }
    else
    {
        SetWindowLong(m_hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(m_hWnd, &wpPrev);
        SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
        ShowCursor(TRUE);
        bFullScreen = false;
    }
}
