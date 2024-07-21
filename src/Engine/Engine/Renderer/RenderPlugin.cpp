
#include "RenderPlugin.hpp"
#include "Platform/RenderPlugin/OpenGL/GLRenderPlugin.hpp"

std::unique_ptr<RenderPlugin> RenderPlugin::createRenderPlugin(GraphicsSpec spec)
{
    return std::make_unique<OpenGLRenderPlugin>();
}
