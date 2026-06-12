#pragma once

#include "Engine/System.hpp"
#include "Base.hpp"


namespace Ellipse {

class Component {
    public:
     Component() {

     }
     virtual ~Component() {

     }
     virtual void onInit() = 0;
     virtual void onUpdate() = 0;
     
    private:
};

// [ Derive entities form this class ]
class Entity {
    public:
     Entity() {

     }
     virtual ~Entity() {

     }

     Entity(const Entity& e) 
     : m_components{e.components()} {
     }

     void onInit() {
      initOverride();

      for(auto [key, value] : m_components) {
       value->onInit();
      }
     }

     virtual void onUpdate() {
      
     }

     void updateComponents() {
      for(auto [key, value] : m_components) {
       value->onUpdate();
      }
     }

     template<typename T>
     void addComponent(Component& component) {
      if(m_components.contains(T::name())) {
       // Log component is in list 
       return;
      }
      m_components[T::name()] = std::make_shared<T>(static_cast<T&>(component));
     }

     template<typename T>
     void addComponent() {
      if(m_components.contains(T::name())) {
       // Log component is in list 
       return;
      }
      m_components[T::name()] = std::make_shared<T>();
     }

     // template<typename T>
     // void addComponent(const T& t) {
     //  if(m_components.contains(T::name())) {
     //   // Log component is in list 
     //   return;
     //  }
     //  m_components[T::name()] = std::make_shared<T>(t);
     // }

     template<typename T>
     T& findComponent() {
      return static_cast<T&>(*m_components[T::name()]);
     }

     template<typename T>
     void removeComponent() {
      m_components.erase(T::name());
     }

     uint64_t componentAmount() {
      return m_components.size();
     }

     std::map<String, std::shared_ptr<Component>> components() const { return m_components; }

    protected:
     virtual void initOverride() = 0;

    private:
     std::map<String, std::shared_ptr<Component>> m_components;
};

class EntitySystem : public ISystem {
    public:
     EntitySystem() {

     }
     ~EntitySystem() {

     }

     virtual String name() override {
      return "Entity";
     }
     virtual void setName(const char* name) override {
     }

     virtual void onInit() override {

     }

     virtual void onUpdate() override {
      for(auto [key, value] : m_entities) {
       value->onUpdate();
       value->updateComponents();
    }
      }
     
     template<typename T>
     void addEntity(Entity& entity) {
      i32_t id = 1;
      m_entities[id] = createShared<T>(static_cast<T&>(entity));
     }

     Entity& findEntity(i32_t id) {
      return *m_entities[id];
     }

     void removeEntity(i32_t id) {
      m_entities.erase(id);
     }

     uint64_t entityAmount() {
      return m_entities.size();
     }

	   std::unordered_map<i32_t, SharedPtr<Entity>> entities() {
      return m_entities;
     }

     static SharedPtr<EntitySystem> createEntitySystem() {
      return createShared<EntitySystem>(); 
     }

    private:
     std::unordered_map<i32_t, std::shared_ptr<Entity>> m_entities;
};  

}     // namespace Ellipse

