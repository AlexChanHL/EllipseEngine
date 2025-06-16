
#include "Renderer.hpp"

namespace Ellipse
{

class RendererImpl final : public Renderer
{
   public:
    explicit RendererImpl(UniquePtr<RenderPlugin> plugin);
    ~RendererImpl();

    void render(const RenderObj& rObj, const RenderShaderObj& sObj, const UniformList& uniforms) override;
    virtual void clearColorBuffer() override;
    virtual void clearDepthBuffer() override;
    void setClearColor(const Vec4& col) override;
    virtual void setWindowFrameSize(Pair<int, int> winSize) override;
    void setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height) override;

    virtual Pair<int, int> getWindowFrameSize() override
    {
    return Pair<int, int>{m_currentWidth, m_currentHeight};
    }

    virtual SharedPtr<RenderObj> createRenderObj(RenderObjData modelData) override;
    virtual SharedPtr<RenderShaderObj> createShaderObj(String vShader,
                                                       String fShader) override;

    virtual UniquePtr<RenderPlugin>& plugin() override
    {
    return m_plugin;
    }

    virtual String name() override;
    virtual void setName(const char* name) override;

   private:
    i32_t m_currentWidth;
    i32_t m_currentHeight;
    UniquePtr<RenderPlugin> m_plugin = nullptr;
};

RendererImpl::RendererImpl(UniquePtr<RenderPlugin> plugin)
 : m_plugin{std::move(plugin)}
{
    setName("Renderer");
}
RendererImpl::~RendererImpl()
{

}

String RendererImpl::name() 
{
    return m_name;
}
void RendererImpl::setName(const char* name)
{
    m_name = name;
}

void RendererImpl::render(const RenderObj& rObj, const RenderShaderObj& sObj, const UniformList& uniforms)
{
    sObj.use();

    m_plugin->setUniforms(uniforms);

    if(rObj.isTextured())
    {
    m_plugin->bindTextures(rObj);
    }

    m_plugin->render(rObj);
}

void RendererImpl::clearColorBuffer()
{
    m_plugin->clearColorBuffer();
}

void RendererImpl::clearDepthBuffer()
{
    m_plugin->clearDepthBuffer();
}

void RendererImpl::setClearColor(const Vec4& col)
{
    m_plugin->setClearColor(col);
}

void RendererImpl::setWindowFrameSize(Pair<int, int> winSize)
{
    m_currentWidth = winSize.first;
    m_currentHeight = winSize.second;
}

void RendererImpl::setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height)
{
    m_plugin->setViewport(posX, posY, width, height);
}

SharedPtr<RenderObj> RendererImpl::createRenderObj(RenderObjData modelData)
{
    return m_plugin->createRenderObj(modelData);
}

SharedPtr<RenderShaderObj> RendererImpl::createShaderObj(String vShader,
                                                         String fShader)
{
    return m_plugin->createShaderObj(vShader, fShader);
}

SharedPtr<Renderer> Renderer::createRenderer(UniquePtr<RenderPlugin> plugin)
{
    return createShared<RendererImpl>(std::move(plugin));  
}

}    //namespace Ellipse
