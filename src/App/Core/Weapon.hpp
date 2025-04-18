#pragma once

#include "Ellipse.hpp"

#include "ModelList.hpp"


class Bullet
{
   public:
    Bullet(u64_t index,
           Vec3 position,
           Vec3 direction,
           float timeStart,
           float expireTime
          )
    : m_name{Ellipse::format("Bullet{}", index)},
      m_position{position},
      m_direction{direction},
      m_timeStart{timeStart},
      m_expireTime{expireTime}
    {
    // std::cout << m_name << '\n';

    }
    ~Bullet()
    {

    }

    bool isExpired(float dt)
    {
    return (dt - m_timeStart) >= m_expireTime;
    }

    void setPosition(Vec3 position)
    {
    m_position = position;
    }

    String name()
    {
    return m_name;
    }

    Vec3 position() const
    {
    return m_position;
    }

    Vec3 direction() const
    {
    return m_direction;
    }

    float timeStart() const
    {
    return m_timeStart;
    }
    
   private:
    String m_name;
    Vec3 m_position;
    Vec3 m_direction;
    float m_timeStart;
    float m_expireTime;
};

inline Vec3 findBulletPosition(Bullet bullet, float dt)
{
    float distanceBullet = dt - bullet.timeStart();

    float kq = 0.1f;
    float kl = 0.252f;
    float kc = 2.0f;

    float rate = static_cast<float>(pow((kq * static_cast<float>(pow(distanceBullet, 2)) + kl * distanceBullet + kc), -1));


    return bullet.position() + (bullet.direction() * rate);
}

enum class WeaponType
{
    None, Pistol, AssaultRifle, Shotgun
};

class Weapon
{
   public:
    Weapon(ModelList& modelList, Ellipse::Engine& engine)
    : m_modelList{modelList},
      m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
      m_camera{static_cast<Ellipse::RenderModule&>(engine.getLayerModule("RenderModule")).camera()},
      m_addCount{0},
      m_weaponType{WeaponType::Pistol},
      m_shotgunBulletCount{16}
    {
  
    }
    ~Weapon()
    {

    }

    void update()
    {
    float dt = static_cast<float>(m_timeModule.secAndNSec());

    for(u64_t i=0;i<m_bullets.size();i++)
    {
    Vec3 position = findBulletPosition(m_bullets[i], dt);
    m_modelList.model(m_bullets[i].name().c_str()).setTranslateAmount(position);
    m_bullets[i].setPosition(position);

    if(m_bullets[i].isExpired(dt))
    {
    m_modelList.removeModel(m_bullets[i].name().c_str());
    m_bullets.erase(m_bullets.begin() + static_cast<i64_t>(i));
    }

    }

    }

    void fire()
    {
    switch(m_weaponType)
    {
    case WeaponType::Pistol:
    m_bullets.push_back(Bullet{m_addCount, m_camera.position(), Ellipse::EllipseMath::normalize(m_camera.front()), static_cast<float>(m_timeModule.secAndNSec()), 3.0f});
    m_addCount++;

    m_modelList.addModel(m_bullets[m_bullets.size() - 1].name().c_str());
    m_modelList.model(m_bullets[m_bullets.size() - 1].name().c_str()).setTranslateAmount(m_bullets[m_bullets.size() - 1].position());
    break;
    case WeaponType::Shotgun:
    {
    for(u64_t i=0;i<m_shotgunBulletCount;i++)
    {
    Vec3 shotgunBulletDirection = Ellipse::EllipseMath::normalize(Vec3{Ellipse::EllipseMath::randRealDist(-1.0f, 1.0f),
                                                                       Ellipse::EllipseMath::randRealDist(-1.0f, 1.0f),
                                                                       Ellipse::EllipseMath::randRealDist(-1.0f, 1.0f)
                                                                      }
                                                                 );

    if(shotgunBulletDirection == -Ellipse::EllipseMath::normalize(m_camera.front()))
    {
    shotgunBulletDirection = -shotgunBulletDirection;
    }
    
    shotgunBulletDirection = Ellipse::EllipseMath::normalize((shotgunBulletDirection / 4.0f) + Ellipse::EllipseMath::normalize(m_camera.front())); 
    m_bullets.push_back(Bullet{m_addCount, m_camera.position(), shotgunBulletDirection, static_cast<float>(m_timeModule.secAndNSec()), 3.0f});
    m_addCount++;

    m_modelList.addModel(m_bullets[m_bullets.size() - 1].name().c_str());
    m_modelList.model(m_bullets[m_bullets.size() - 1].name().c_str()).setTranslateAmount(m_bullets[m_bullets.size() - 1].position());
    }

    }
    break;
    case WeaponType::AssaultRifle:
    m_bullets.push_back(Bullet{m_addCount, m_camera.position(), Ellipse::EllipseMath::normalize(m_camera.front()), static_cast<float>(m_timeModule.secAndNSec()), 3.0f});
    m_addCount++;

    m_modelList.addModel(m_bullets[m_bullets.size() - 1].name().c_str());
    m_modelList.model(m_bullets[m_bullets.size() - 1].name().c_str()).setTranslateAmount(m_bullets[m_bullets.size() - 1].position());
    default:
    break;
    }

    }

    void changeWeaponType(WeaponType weaponType)
    {
    m_weaponType = weaponType;
    }

   private:
    ModelList& m_modelList;
    Ellipse::TimeModule& m_timeModule;
    Vector<Bullet> m_bullets;
    Ellipse::Camera& m_camera;
    u64_t m_addCount;
    WeaponType m_weaponType;
    u64_t m_shotgunBulletCount;
};

