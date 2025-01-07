#include <Windows.h>
#include <iostream>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#include "Window/Win32Window/Win32Window.hpp"
#include "Renderer/OGLRenderer/OGLRenderer.hpp"

const int iWidth = 800;
const int iHeight = 600;

Win32Window *win32 = nullptr;
OGLRenderer *ogl = nullptr;

void Resize(int width, int height)
{
    ogl->Resize(width, height);
}

void Run(float delta)
{
    ogl->Update(delta);
    ogl->PreRender();
    ogl->Render();
    ogl->PostRender();
}

int main(void)
{
    win32 = new Win32Window();
    win32->SetExecutionFunction(Run);
    if (!win32->Initialize(iWidth, iHeight))
    {
        std::cout << "Create Window failed. Exitting now." << std::endl;
        exit (-1);
    }
    
    ogl = new OGLRenderer();
    if (!ogl)
    {
        std::cout << "OpenGL Renderer constructor failed. Exitting now." << std::endl;
        exit (-2);
    }
    ogl->SetHWND(win32->GetHWND());
    if (!ogl->Initialize())
    {
        std::cout << "OpenGL Renderer Initialization failed. Exitting now." << std::endl;
        exit (-3);
    }

    // Show Window
    win32->ShowWindow();

    // Execuation Loop
    win32->Run();

    // Uninitialization OpenGL component 
    ogl->UnInitialize();

    // Unitialization components before exiting
    win32->UnInitialize();

    return (0);
}

