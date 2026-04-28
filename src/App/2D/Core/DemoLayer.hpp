#pragma once

#include "ModelList.hpp"

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
    Ellipse::ModelManagerModule& m_modelManagerLayerModule;
    Ellipse::RenderModule& m_renderModule;
    Ellipse::FontModule& m_fontModule;
    Ellipse::EntitySystem& m_entitySystem;

    ModelList m_modelList;
    Ellipse::PreDefinedObjects& m_objects;

    Ellipse::Timer m_timer;
    Vector<String> m_names;
    Vec2 m_cursor;
    Vec3 m_colorKey;
};

