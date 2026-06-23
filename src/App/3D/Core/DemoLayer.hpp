#pragma once

#include "Ellipse.hpp"

#include "Weapon.hpp"
#include "CubeMadeCube.hpp"


// class LightModel
// {
//    public:
//     LightModel()
//     : m_name{nullptr}
//     {
//
//     }
//     ~LightModel()
//     {
//
//     }
//
//     void init(ModelList& modelList, const char* name)
//     {
//     m_name = name;
//
//     m_light.setLightPosition(Vec3{0.0f, 0.0f, 0.0f});
//
//     
//     modelList.addModel(name,
//                        "LightCube"
//                       );
//
//     }
//
//     void setPosition(ModelList& modelList, Vec3 position)
//     {
//     m_light.setLightPosition(position);
//
//     modelList.model(m_name).setTranslateAmount(Vec3{1.0f, 2.0f, 1.0f});
//     }
//
//     Light& light()
//     {
//     return m_light;
//     }
//
//    private:
//     const char* m_name;
//     Light m_light;
// };


class DemoLayer : public Ellipse::Layer
{
   public:
    DemoLayer(Ellipse::Engine& engine);
    virtual ~DemoLayer() = default;

    void init() override;
    virtual void onEvent(Ellipse::Event& e) override;

    void onUpdate(float dt) override;

    void setName(String name) { m_name = name; }

    bool onKeyPressed(Ellipse::KeyboardPressedEvent& e);
    bool onMouseMotion(Ellipse::MouseMotionEvent& e);
    bool onMousePressed(Ellipse::MousePressedEvent& e);
    bool onMouseWheel(Ellipse::MouseWheelEvent& e);

   private:
    Ellipse::Engine&  m_engine;
    Ellipse::TimeModule& m_timeModule;
    Ellipse::RenderModule& m_renderModule;
    Ellipse::Timer m_timer1;
    Ellipse::EntitySystem& m_entitySystem;
    u32_t m_modelIncrement;
    float m_rotatedDegrees;
    Vector<i32_t> m_entities;
    Weapon m_weapon;

    // LightModel m_light;
    // CubeMadeCube m_cubeMadeCube;
    // Ellipse::PreDefinedObjects m_objects;
};

