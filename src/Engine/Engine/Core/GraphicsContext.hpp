#pragma once

#include "Base.hpp"

enum class GraphicsLib : u8_t
{
   None   = 0u,
   OpenGL = 1u,
   Vulkan = 2u,
};

class GraphicsContext
{
   public:
    GraphicsContext() = default;
    virtual ~GraphicsContext() = default;

    virtual GraphicsLib getGraphicsLib() = 0;
    virtual void* getContext() = 0;

   private:
};


