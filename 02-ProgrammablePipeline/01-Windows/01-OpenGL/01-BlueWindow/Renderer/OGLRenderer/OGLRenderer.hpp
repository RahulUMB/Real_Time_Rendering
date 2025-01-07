#pragma once

#include "..\Renderer.hpp"

#include <Windows.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/GL.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")

class OGLRenderer : public Renderer
{
public:
    HDC m_hdc;
    HWND m_hwnd;
    HGLRC m_glrc;

    bool Initialize() override;
    void UnInitialize() override;

    void SetHWND(HWND hWnd);

    void Resize(const int width, const int height);

    void PreRender() override;
    void Render() override;
    void PostRender() override;

    void Update(float delta) override;
};
