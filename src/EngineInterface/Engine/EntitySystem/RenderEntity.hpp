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

   RenderEntity& operator=(const RenderEntity& e) {
    this->m_renderModule = e.renderModule();
    this->m_id = e.id();
    this->m_components = e.components();

    return *this;
   }

   virtual void initOverride() override {
    auto rComp = Ellipse::RenderComponent{*m_renderModule, m_renderModule->preDefinedObjects()[m_objectName]};
    addComponent<Ellipse::RenderComponent>(rComp);
   }

   void onUpdate() override {
    auto rComp = findComponent<Ellipse::RenderComponent>();
   }
 
   virtual void render() {
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
   
  protected:
   RenderModule* m_renderModule;
   String m_objectName;
 };

}

