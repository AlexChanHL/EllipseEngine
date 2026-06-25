#pragma once


#include "Ellipse.hpp"
#include "RenderModule.hpp"
#include "RenderComponent2D.hpp"

namespace Ellipse {
 class RenderEntity3D : public RenderEntity {
  public:
   RenderEntity3D() {}; 
   RenderEntity3D(Engine& engine) 
   : RenderEntity{engine} {
    m_renderModule3D = static_cast<RenderModule3D*>(m_renderModule);
   }
   virtual ~RenderEntity3D() = default;

   RenderEntity3D(const RenderEntity3D& e) 
   : RenderEntity(e),
     m_renderModule3D{static_cast<RenderModule3D*>(e.renderModule())} {
   }

   void operator=(const RenderEntity3D& e) {
    m_renderModule = e.renderModule();
    m_renderModule3D = e.renderModule3D();
   }

   virtual void initOverride() override {
    auto rComp = Ellipse::RenderComponent{*m_renderModule, m_renderModule->preDefinedObjects()[m_objectName]};
    addComponent<Ellipse::RenderComponent>(rComp);
   }

   virtual void render() override {
    auto rComp = findComponent<RenderComponent>();
    if(rComp.renderObj().get() == nullptr) {
     return;
    }
    if(rComp.shaderObj().get() == nullptr) {
     return;
    }

    m_renderModule3D->render3D(rComp.renderObj().get(),
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

