cls

del *.obj *.exe

cl.exe /c /EHsc /Fe:Main.exe Main.cpp Window\Win32Window\Win32Window.cpp Renderer\OGLRenderer\OGLRenderer.cpp /I "C:\OpenGL\glew-2.1.0\include"

link.exe Main.obj Win32Window.obj OGLRenderer.obj /LIBPATH "C:\OpenGL\glew-2.1.0\lib\Release\x64\glew32.lib" user32.lib gdi32.lib /SUBSYSTEM:CONSOLE

Main.exe
