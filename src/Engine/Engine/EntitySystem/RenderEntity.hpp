#pragma once


#include "EntitySystem.hpp"
#include "RenderComponent.hpp"

namespace Ellipse {
 class RenderEntity : public Entity {
  public:
   RenderEntity() {}; 
   RenderEntity(Engine& engine, String objectName) 
   : m_renderModule{&static_cast<RenderModule&>(engine.getModule("RenderModule"))},
     m_objectName{objectName} {
    onInit();
   }
   virtual ~RenderEntity() = default;

   RenderEntity(const RenderEntity& e) 
   : Entity(e), 
     m_renderModule{e.renderModule()} {
   }

   RenderEntity& operator=(const RenderEntity& e) {
    this->m_renderModule = e.renderModule();
    this->m_id = e.id();
    this->m_objectName = e.objectName();
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

    rComp.model()->prepare();
    m_renderModule->render(rComp.renderObj().get(),
                           rComp.shaderObj().get(),
                           rComp.shaderObj()->uniformList()
                          );
   }
 
   RenderModule* renderModule() const { return m_renderModule; }
   String objectName() const { return m_objectName; }
   
  protected:
   RenderModule* m_renderModule;
   String m_objectName;
 };

}

