
#include "Renderer.hpp"

class RendererImpl final : public Renderer
{
   public:
    explicit RendererImpl(UniquePtr<RenderPlugin> plugin);
    ~RendererImpl() = default;

    void render(RenderObj& rObj, RenderShaderObj& sObj) override;
    void setClearColor(const Vec4& col) override;
    void setViewport(int32_t width, int32_t height) override;
    UniquePtr<RenderObj> createRenderObj() override;
    UniquePtr<RenderShaderObj> createShaderObj() override;
   private:
    UniquePtr<RenderPlugin> m_plugin = nullptr;
};

RendererImpl::RendererImpl(UniquePtr<RenderPlugin> plugin)
 : m_plugin{std::move(plugin)}
{

}

void RendererImpl::render(RenderObj& rObj, RenderShaderObj& sObj)
{
    m_plugin->render(rObj, sObj);
}

void RendererImpl::setClearColor(const Vec4& col)
{
    m_plugin->setClearColor(col);
}

void RendererImpl::setViewport(int32_t width, int32_t height)
{
    m_plugin->setViewport(width, height);
}

UniquePtr<RenderObj> RendererImpl::createRenderObj()
{
    return m_plugin->createRenderObj();
}

UniquePtr<RenderShaderObj> RendererImpl::createShaderObj()
{
    return m_plugin->createShaderObj();
}

UniquePtr<Renderer> Renderer::createRenderer(UniquePtr<RenderPlugin> plugin)
{
    return std::make_unique<RendererImpl>(std::move(plugin));  
}

