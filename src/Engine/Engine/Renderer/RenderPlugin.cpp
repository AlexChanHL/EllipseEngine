
#include "RenderPlugin.hpp"
#include "Platform/RenderPlugin/OpenGL/GLRenderPlugin.hpp"

namespace Ellipse
{

UniquePtr<RenderPlugin> RenderPlugin::createRenderPlugin(GraphicsSpec spec)
{
    return std::make_unique<OpenGLRenderPlugin>();
}

} //   namespace Ellipse
