#pragma once

class Renderer
{
public:
    virtual bool Initialize() = 0;
    virtual void UnInitialize() = 0;

    virtual void Resize(int width, int height) = 0;

    virtual void PreRender() = 0;
    virtual void Render() = 0;
    virtual void PostRender() = 0;
    
    virtual void Update(float delta) = 0;
};
