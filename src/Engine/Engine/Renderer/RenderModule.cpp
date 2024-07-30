
#include "Renderer.hpp"
#include "RenderModule.hpp"

class RenderModuleImpl final : public RenderModule
{
    public:
     RenderModuleImpl();
     virtual Model createModel() override;
     virtual void renderModel(const Model& model) override;

     String name() override;
     void setName(const char* name) override;

    private:
     // Renderer& m_renderer;
};

RenderModuleImpl::RenderModuleImpl()
 // : 
{

}

String RenderModuleImpl::name()
{
   return m_name;
}
void RenderModuleImpl::setName(const char* name)
{
   m_name = name;
}

Model RenderModuleImpl::createModel()
{
    return Model{};
}

void RenderModuleImpl::renderModel(const Model& model) 
{

}
