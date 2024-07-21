
#include "Renderer.hpp"

Renderer::Renderer(std::unique_ptr<RenderPlugin> plugin)
 : m_plugin{std::move(plugin)}
{

}
Renderer::~Renderer()
{

}

void Renderer::render(RenderObj& rObj, RenderShaderObj& sObj)
{
    m_plugin->render(rObj, sObj);
}

void Renderer::setClearColor(const glm::vec4& col)
{
    m_plugin->setClearColor(col);
}

void Renderer::setViewport(int32_t width, int32_t height)
{
    m_plugin->setViewport(width, height);
}

std::unique_ptr<RenderObj> Renderer::createRenderObj()
{
    return m_plugin->createRenderObj();
}

std::unique_ptr<RenderShaderObj> Renderer::createShaderObj()
{
    return m_plugin->createShaderObj();
}

std::unique_ptr<Renderer> Renderer::createRenderer(std::unique_ptr<RenderPlugin> plugin)
{
    return std::make_unique<Renderer>(std::move(plugin));  
}

