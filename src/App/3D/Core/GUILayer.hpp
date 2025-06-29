#pragma once

#include "ModelList2D.hpp"

#include "Ellipse.hpp"

 
class GUILayer : public Ellipse::Layer
{
    public:
     GUILayer(Ellipse::Engine& engine);
     ~GUILayer();

     virtual void init() override;
     virtual void onUpdate(float dt) override;
     virtual void onEvent(Ellipse::Event& event) override;

    private:
     ModelList2D m_modelList2D;
     Ellipse::TimeModule& m_timeModule;
     Ellipse::RenderModule& m_renderModule;
     Ellipse::PreDefinedObjects m_objects;
};

