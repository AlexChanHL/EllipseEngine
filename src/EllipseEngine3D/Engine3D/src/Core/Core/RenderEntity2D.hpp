#pragma once


#include "Ellipse.hpp"
#include "RenderModule.hpp"
#include "RenderComponent2D.hpp"

namespace Ellipse {
 class RenderEntity2D : public RenderEntity {
  public:
   RenderEntity2D() {}; 
   RenderEntity2D(Engine& engine) 
   : RenderEntity{engine} {
    m_renderModule3D = static_cast<RenderModule3D*>(m_renderModule);
   }
   virtual ~RenderEntity2D() = default;

   RenderEntity2D(const RenderEntity2D& e) 
   : RenderEntity(e),
     m_renderModule3D{static_cast<RenderModule3D*>(e.renderModule())} {
   }

   void operator=(const RenderEntity2D& e) {
    m_renderModule = e.renderModule();
    m_renderModule3D = e.renderModule3D();
   }

   virtual void initOverride() override {
    auto rComp = Ellipse::RenderComponent2D{*m_renderModule, m_renderModule->preDefinedObjects()[m_objectName]};
    addComponent<Ellipse::RenderComponent2D>(rComp);
   }

   virtual void render() override {
    auto rComp = findComponent<RenderComponent>();
    if(rComp.renderObj().get() == nullptr) {
     return;
    }
    if(rComp.shaderObj().get() == nullptr) {
     return;
    }

    m_renderModule3D->render2D(rComp.renderObj().get(),
                               rComp.shaderObj().get(),
                               rComp.shaderObj()->uniformList(),
                               rComp.model()->translate(),
                               rComp.model()->rotateAxis(),
                               rComp.model()->rotateAngle(),
                               rComp.model()->scale()
                               );
   }

   RenderModule3D* renderModule3D() const { return m_renderModule3D; }
 
  protected:
   RenderModule3D* m_renderModule3D;
 };

}

