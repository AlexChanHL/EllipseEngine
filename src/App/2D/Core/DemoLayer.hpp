#pragma once

#include "Ellipse.hpp"


class DemoLayer : public Ellipse::Layer
{
   public:
    DemoLayer(Ellipse::Engine& engine);
    virtual ~DemoLayer() = default;

    void init() override;
    virtual void onEvent(Ellipse::Event& e) override;

    void onUpdate(float dt) override;

    void setName(String name) {
     m_name = name;
    }

    bool onKeyPressed(Ellipse::KeyboardPressedEvent& e);
    bool onMouseMotion(Ellipse::MouseMotionEvent& e);
    bool onMousePressed(Ellipse::MousePressedEvent& e);
    bool onMouseWheel(Ellipse::MouseWheelEvent& e);

   private:
    Ellipse::Engine&  m_engine;
    Ellipse::TimeModule& m_timeModule;
    Ellipse::RenderModule& m_renderModule;
    Ellipse::FontModule& m_fontModule;
    Ellipse::EntitySystem& m_entitySystem;

    Ellipse::PreDefinedObjects& m_objects;

    Ellipse::Timer m_timer;
    Vector<String> m_names;
    EllipseMath::Vec2 m_cursor;
    EllipseMath::Vec3 m_colorKey;
};

