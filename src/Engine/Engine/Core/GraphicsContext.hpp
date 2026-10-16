#pragma once

#include "Base.hpp"


enum class GraphicsLibrary : u8_t
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

    virtual void deleteContext() = 0;

    virtual GraphicsLibrary getGraphicsLibrary() = 0;
    virtual void* getContext() = 0;

   private:
};


