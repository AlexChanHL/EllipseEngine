
#include "Renderer.hpp"

namespace Ellipse
{

class RendererImpl final : public Renderer
{
   public:
    explicit RendererImpl(UniquePtr<RenderPlugin> plugin);
    ~RendererImpl() = default;

    void render(const RenderObj& rObj, const RenderShaderObj& sObj) override;
    virtual void clearColorBuffer() override;
    void setClearColor(const Vec4& col) override;
    virtual void setWindowFrameSize(Pair<int, int> winSize) override;
    void setViewport(int32_t width, int32_t height) override;

    virtual Pair<int, int> getWindowFrameSize() override
    {
    return Pair<int, int>{m_currentWidth, m_currentHeight};
    }

    virtual SharedPtr<RenderObj> createRenderObj(VerticiesData verts) override;
    virtual SharedPtr<RenderShaderObj> createShaderObj(String vShader,
                                                 String fShader,
                                                 UniformList uniforms) override;

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

String RendererImpl::name() 
{
    return m_name;
}
void RendererImpl::setName(const char* name)
{
    m_name = name;
}

void RendererImpl::render(const RenderObj& rObj, const RenderShaderObj& sObj)
{
    sObj.use();

    m_plugin->setUniforms(sObj.getUniforms(),
                          sObj.getUniformLocs());


    m_plugin->render(rObj);
}

void RendererImpl::clearColorBuffer()
{
    m_plugin->clearColorBuffer();
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

void RendererImpl::setViewport(int32_t width, int32_t height)
{
    m_plugin->setViewport(width, height);
}

SharedPtr<RenderObj> RendererImpl::createRenderObj(VerticiesData verts)
{
    return m_plugin->createRenderObj(verts);
}

SharedPtr<RenderShaderObj> RendererImpl::createShaderObj(String vShader,
                                    String fShader,
                                    UniformList uniforms)
{
    return m_plugin->createShaderObj(vShader, fShader, uniforms);
}

SharedPtr<Renderer> Renderer::createRenderer(UniquePtr<RenderPlugin> plugin)
{
    return createShared<RendererImpl>(std::move(plugin));  
}

}    //namespace Ellipse
