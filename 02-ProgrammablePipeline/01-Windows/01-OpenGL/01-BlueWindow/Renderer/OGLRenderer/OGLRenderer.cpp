#include "OGLRenderer.hpp"

bool OGLRenderer::Initialize()
{
    if (!m_hwnd)
        return (false);

    PIXELFORMATDESCRIPTOR pfd;

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;
    
    m_hdc = GetDC(m_hwnd);

    int iPixelFormatIndex = ChoosePixelFormat(m_hdc, &pfd);
    if (iPixelFormatIndex == 0)
    {
        std::cout << "ChoosePixelFormat(...) failed." << std::endl;
        return (false);
    }

    if (SetPixelFormat(m_hdc, iPixelFormatIndex, &pfd) == false)
    {
        std::cout << "SetPixelFormat(...) failed." << std::endl;
        return (false);
    }
    
    m_glrc = wglCreateContext(m_hdc);
    if (m_glrc == NULL)
    {
        std::cout << "wglCreateContext(...) failed." << std::endl;
        return (false);
    }

    if (wglMakeCurrent(m_hdc, m_glrc) == false)
    {
        std::cout << "wglMakeCurrent(...) failed." << std::endl;
        return (false);
    }

    GLenum result = glewInit();
    if (result != GLEW_OK)
    {
        std::cout << "glewInit(...) failed." << std::endl;
        return (false);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    return (true);
}

void OGLRenderer::UnInitialize()
{
    if (wglGetCurrentContext() == m_glrc)
    {
        wglMakeCurrent(NULL, NULL);
    }
    
    if (m_hdc)
    {
        ReleaseDC(m_hwnd, m_hdc);
        m_hdc = NULL;
    }

    return;
}

void OGLRenderer::SetHWND(HWND hWnd)
{
    m_hwnd = hWnd;
}

void OGLRenderer::Resize(const int width, const int height)
{
    return;
}

void OGLRenderer::PreRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return;
}

void OGLRenderer::Render()
{    
    return;
}

void OGLRenderer::PostRender()
{
    SwapBuffers(m_hdc);

    return;
}

void OGLRenderer::Update(float delta)
{
    return;
}
