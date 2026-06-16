#pragma once


#include "EntitySystem.hpp"
#include "RenderComponent.hpp"

namespace Ellipse {
 class RenderEntity : public Entity {
  public:
   RenderEntity() {}; 
   RenderEntity(Engine& engine) 
   : m_renderModule{&static_cast<RenderModule&>(engine.getModule("RenderModule"))} {
   }
   virtual ~RenderEntity() = default;

   RenderEntity(const RenderEntity& e) 
   : Entity(e), 
     m_renderModule{e.renderModule()} {
   }

   void operator=(const RenderEntity& e) {
    m_renderModule = e.renderModule();
   }

   virtual void initOverride() override {
    auto rComp = Ellipse::RenderComponent{*m_renderModule, m_renderModule->preDefinedObjects()[m_objectName]};
    addComponent<Ellipse::RenderComponent>(rComp);
   }

   void onUpdate() override {
    auto rComp = findComponent<Ellipse::RenderComponent>();
    rComp.shaderObj()->uniformList().printUniformList();
   }
 
   void render() {
    auto rComp = findComponent<RenderComponent>();
    if(rComp.renderObj().get() == nullptr) {
     return;
    }
    if(rComp.shaderObj().get() == nullptr) {
     return;
    }
    
    m_renderModule->render(rComp.renderObj().get(), rComp.shaderObj().get(), rComp.shaderObj()->uniformList());
   }
 
   RenderModule* renderModule() const { return m_renderModule; }
   String& objectName() { return m_objectName; }
   
  private:
   RenderModule* m_renderModule;
   String m_objectName;
 };

}

