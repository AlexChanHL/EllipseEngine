#pragma once

#include "Ellipse.hpp"
#include "Ellipse3D.hpp"


class Bullet {
   public:
    Bullet(i32_t id,
           u64_t index,
           EllipseMath::Vec3 position,
           EllipseMath::Vec3 direction,
           float timeStart,
           float expireTime
          )
    : m_id{id},
      m_position{position},
      m_direction{direction},
      m_timeStart{timeStart},
      m_expireTime{expireTime} {
    }
    ~Bullet() {
    }

    bool isExpired(float dt) { return (dt - m_timeStart) >= m_expireTime; }
    void setPosition(EllipseMath::Vec3 position) { m_position = position; }
    i32_t id() { return m_id; }
    EllipseMath::Vec3 position() const { return m_position; }
    EllipseMath::Vec3 direction() const { return m_direction; }
    float timeStart() const { return m_timeStart; }
    
   private:
    i32_t m_id;
    EllipseMath::Vec3 m_position;
    EllipseMath::Vec3 m_direction;
    float m_timeStart;
    float m_expireTime;
};

inline EllipseMath::Vec3 findBulletPosition(Bullet bullet, float dt) {
    float distanceBullet = dt - bullet.timeStart();
    float kq = 0.1f;
    float kl = 0.252f;
    float kc = 2.0f;
    float rate = static_cast<float>(pow((kq * static_cast<float>(pow(distanceBullet, 2)) + kl * distanceBullet + kc), -1));
    // std::cout << bullet.position().x << ' ' << bullet.position().y << ' ' << bullet.position().z << '\n';

    return bullet.position() + (bullet.direction() * rate);
}

enum class WeaponType {
    None, Pistol, AssaultRifle, Shotgun
};

class Weapon {
   public:
    Weapon(Ellipse::Engine& engine) 
    : m_engine{engine},
      m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
      m_entitySystem{static_cast<Ellipse::EntitySystem&>(engine.getSystem("Entity"))},
      m_camera{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule")).camera()},
      m_addCount{0},
      m_weaponType{WeaponType::Pistol},
      m_shotgunBulletCount{16} {
    }
    // Weapon(ModelList& modelList, Ellipse::Engine& engine, Light& light)
//     : m_modelList{modelList},
//       m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
//       m_light{light},
//       m_weaponType{WeaponType::Pistol},
//     {
//   
//     }
    ~Weapon() {

    }

    void update() {
     float dt = static_cast<float>(m_timeModule.secAndNSec());
 
     for(u64_t i=0;i<m_bullets.size();i++) {
      EllipseMath::Vec3 position = findBulletPosition(m_bullets[i], dt);
      auto e = m_entitySystem.findEntity<Ellipse::RenderEntity3D>(m_bullets[i].id());
      if(e.id() != -1) {
       auto rComp = e.findComponent<Ellipse::RenderComponent>();
       rComp.model()->translate(position);
       m_bullets[i].setPosition(position);
       e.render();
       std::cout << e.id() << '\n';
       if(m_bullets[i].isExpired(dt)) {
        m_entitySystem.removeEntity(e.id());
        m_bullets.erase(m_bullets.begin() + static_cast<i64_t>(i));
       }
      }
     }
    }

    void fire() {
    switch(m_weaponType) {
     case WeaponType::Pistol: {
      auto cube = Ellipse::RenderEntity(m_engine);
      cube.objectName() = "Cube";
      cube.onInit();
      i32_t id = 0;
      m_entitySystem.addEntity<Ellipse::RenderEntity3D>(cube, &id);
      m_bullets.push_back(Bullet{id, m_addCount, m_camera.position(), Ellipse::EllipseMath::normalize(m_camera.front()), static_cast<float>(m_timeModule.secAndNSec()), 3.0f});
      m_addCount++;
      auto rComp = cube.findComponent<Ellipse::RenderComponent>();
      rComp.model()->translate(m_camera.position());
      std::cout << "Fire\n";
     }
     break;
     case WeaponType::Shotgun: {
      // for(u64_t i=0;i<m_shotgunBulletCount;i++) {
      //  EllipseMath::Vec3 shotgunBulletDirection = Ellipse::EllipseMath::normalize(EllipseMath::Vec3{Ellipse::EllipseMath::randRealDist(-1.0f, 1.0f),
      //                                                                     Ellipse::EllipseMath::randRealDist(-1.0f, 1.0f),
      //                                                                     Ellipse::EllipseMath::randRealDist(-1.0f, 1.0f)
      //                                                                    }
      //                                                               );
      //  if(shotgunBulletDirection == -Ellipse::EllipseMath::normalize(m_camera.front())) {
      //   shotgunBulletDirection = -shotgunBulletDirection;
      //  }
      //  shotgunBulletDirection = Ellipse::EllipseMath::normalize((shotgunBulletDirection / 4.0f) + Ellipse::EllipseMath::normalize(m_camera.front())); 
      //  m_bullets.push_back(Bullet{m_addCount, m_camera.position(), shotgunBulletDirection, static_cast<float>(m_timeModule.secAndNSec()), 3.0f});
      //  m_addCount++;
      //  // m_modelList.addModel(m_bullets[m_bullets.size() - 1].name().c_str(), "Cube", m_camera, m_light);
      //  // m_modelList.model(m_bullets[m_bullets.size() - 1].name().c_str()).setTranslateAmount(m_bullets[m_bullets.size() - 1].position());
      // }
     }
     break;
     case WeaponType::AssaultRifle:
      // m_bullets.push_back(Bullet{m_addCount, m_camera.position(), Ellipse::EllipseMath::normalize(m_camera.front()), static_cast<float>(m_timeModule.secAndNSec()), 3.0f});
      // m_addCount++;
      // m_modelList.addModel(m_bullets[m_bullets.size() - 1].name().c_str(), "Cube", m_camera, m_light);
      // m_modelList.model(m_bullets[m_bullets.size() - 1].name().c_str()).setTranslateAmount(m_bullets[m_bullets.size() - 1].position());
     break;
     default:
     break;
    }

    }
//     void changeWeaponType(WeaponType weaponType) { m_weaponType = weaponType; }
//     WeaponType weaponType() const { return m_weaponType; }
//
   private:
    Ellipse::Engine& m_engine;
    Ellipse::TimeModule& m_timeModule;
    Ellipse::EntitySystem& m_entitySystem;
    Vector<Bullet> m_bullets;
    Ellipse::Camera& m_camera;
//     Light& m_light;
    u64_t m_addCount;
    WeaponType m_weaponType;
    u64_t m_shotgunBulletCount;
};

