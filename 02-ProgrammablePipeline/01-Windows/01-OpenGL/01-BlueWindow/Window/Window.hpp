#pragma once

typedef void (*FPTR_Resize)(int width, int height);
typedef void (*FPTR_ExecutionLoop)(float delta);

class Window
{
private:

protected:
    FPTR_Resize resize = nullptr;
    FPTR_ExecutionLoop execLoop = nullptr;

public:
    virtual bool Initialize(int width, int height) = 0;
    virtual void UnInitialize() = 0;

    virtual void ShowWindow() = 0;
    virtual void Run() = 0;

    virtual void FullScreen() = 0;

    inline void SetResizeFunc(FPTR_Resize resizecallback)
    {
        resize = resizecallback;
    }

    inline void SetExecutionFunction(FPTR_ExecutionLoop execFunc)
    {
        execLoop = execFunc;
    }
};
