#pragma once
#include "Renderer.h"

class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    static Singleton& Get()
    {
        static Singleton instance;
        return instance;
    }
    static Renderer* GetRenderer() { return Get().GetRendererInternal(); }
    static void SetRenderer(Renderer* newRenderer) { Get().SetRendererInternal(newRenderer); }
private:
    Renderer* GetRendererInternal() { return renderer; }
    void SetRendererInternal(Renderer* newRenderer) { renderer = newRenderer; }
    Singleton() {}
    Renderer* renderer;
};