#pragma once

#include "Engine/System.hpp"
#include "Math/Random/Random.hpp"
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
     Entity() : m_id{-1} {
     }
     virtual ~Entity() {
     }

     Entity(const Entity& e) 
     : m_components{e.components()}, 
       m_id{e.id()} {
     }

     virtual Entity& operator=(const Entity& e) {
      m_components = e.components();
      m_id = e.id();
      return *this;
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
      if(m_components.find(T::name()) == m_components.end()) {
       std::cout << "Not found in components\n" << "Name: " << T::name() << '\n';
       auto e = new T();
       return *e;
      }
      
      return static_cast<T&>(*m_components[T::name()]);
     }

     template<typename T>
     void removeComponent() {
      m_components.erase(T::name());
     }

     uint64_t componentAmount() {
      return m_components.size();
     }
     i32_t& id() { return m_id; }
     i32_t id() const { return m_id; }

     std::map<String, std::shared_ptr<Component>> components() const { return m_components; }

    protected:
     virtual void initOverride() = 0;

    protected:
     std::map<String, std::shared_ptr<Component>> m_components;
     i32_t m_id;
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
     i32_t addEntity(Entity& entity) {
      // [ 10000 Max ]
      i32_t id = EllipseMath::randIntDist(0, 10000);
      while(m_entities.find(id) != m_entities.end()) {
       id = EllipseMath::randIntDist(0, 10000);
      }
      entity.id() = id;
      m_entities[id] = createShared<T>(static_cast<T&>(entity));
      return id;
     }

     template<typename T>
     void addEntity(Entity& entity, i32_t* id) {
      // [ 10000 Max ]
      *id = EllipseMath::randIntDist(0, 10000);
      while(m_entities.find(*id) != m_entities.end()) {
       *id = EllipseMath::randIntDist(0, 10000);
      }
      entity.id() = *id;
      m_entities[*id] = createShared<T>(static_cast<T&>(entity));
     }

     // [ Will leak memory but not crash ]
     template<typename T>
     T& findEntity(i32_t id) {
      if(m_entities.find(id) == m_entities.end()) {
       std::cout << "Not found in entities\n" << "ID: " << id << '\n';
       auto e = new T();
       return *e;
      }

      // std::cout << "Found in entities\n" << "ID: " << id << '\n';
      return static_cast<T&>(*m_entities[id]);
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

