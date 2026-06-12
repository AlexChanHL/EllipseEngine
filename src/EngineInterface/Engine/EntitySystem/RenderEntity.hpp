#pragma once


#include "EntitySystem.hpp"
#include "RenderComponent.hpp"

namespace Ellipse {
 class RenderEntity : public Entity {
  public:
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
    auto rComp = Ellipse::RenderComponent{*m_renderModule, m_renderModule->preDefinedObjects()["Quad"]};
    addComponent<Ellipse::RenderComponent>(rComp);
   }

   void onUpdate() override {
    auto rComp = findComponent<Ellipse::RenderComponent>();
    rComp.shaderObj()->uniformList().printUniformList();
   }
 
   void render() {
    auto rComp = findComponent<RenderComponent>();
    if(m_renderModule == nullptr) {
     std::cout << m_renderModule << " null\n";
    }
    // if(rComp.renderObj().get() != nullptr) {
    //  std::cout << "null\n";
    // }
    
    // std::cout << "Mesh: " << rComp.renderObj()->meshes()[0]->positions().size() << '\n';
    m_renderModule->render(rComp.renderObj().get(), rComp.shaderObj().get(), rComp.shaderObj()->uniformList());
   }
 
   RenderModule* renderModule() const { return m_renderModule; }
   
  private:
   RenderModule* m_renderModule;
 };

}

