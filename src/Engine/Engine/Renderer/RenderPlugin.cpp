
#include "RenderPlugin.hpp"
#include "Platform/RenderPlugin/OpenGL/GLRenderPlugin.hpp"

UniquePtr<RenderPlugin> RenderPlugin::createRenderPlugin(GraphicsSpec spec)
{
    return std::make_unique<OpenGLRenderPlugin>();
}
