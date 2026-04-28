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
     virtual void update() = 0;
     
    private:
};

// class AComponent : public Component {
//     public:
//      AComponent() {
//
//      }
//      ~AComponent() {
//
//      }
//      virtual void update() override {
//       std::cout << "A component\n";
//      }
//
//      static String name() {
//       return "AComponent";
//      }
//      
//     private:
// };

class Entity {
    public:
     Entity() {

     }
     ~Entity() {

     }

     void update() {
      for(auto [key, value] : m_components) {
       value->update();
      }
     }

     template<typename T>
     void addComponent(Component& component) {
      m_components[T::name()] = std::make_shared<T>(static_cast<T&>(component));
     }

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

     void update() {
      for(auto [key, value] : m_entities) {
       value->update();
      }
     }
     
     void addEntity(Entity& entity) {
      i32_t id = 1;
      m_entities[id] = std::make_shared<Entity>(entity);
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

