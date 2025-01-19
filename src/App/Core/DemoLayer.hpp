#pragma once

#include "Ellipse.hpp"

class EntityCollection
{
   public:
    EntityCollection()
    {

    }
    ~EntityCollection()
    {

    }

    void init()
    {

    }

    void setModelFunc(Ellipse::ModelManagerModule& modelManager)
    {
    // m_addFunc = modelManager.addFunc();
    // m_translateFunc = modelManager.translateFunc();
    // m_rotateFunc = modelManager.rotateFunc();
    // m_scaleFunc = modelManager.scaleFunc();

    }

    void addModel(Ellipse::ModelID& modelID)
    {
   //  Vector<float> verticies = 
   //  {
   //   0.0f,  0.5f,  0.0f,
   //   0.5f, -0.5f,  0.0f,
   //  -0.5f, -0.5f,  0.0f,
   //  };
   //
   //  // [ Make VerticiesData copy constructor ]
   //  Ellipse::VerticiesData verticiesData{3, verticies.size(), verticies};
   //
   //  offset = 0.0f;
   // 
   //  Ellipse::UniformList uniformList;
   //  uniformList.addUniform(Ellipse::UniformVarible<float>{"offset", &m_offset});
    // m_addModel.addModel(modelID,
    //                     "Model",
    //                     "Assets/Shader/Triangle.vert.glsl",
    //                     "Assets/Shader/Triangle.frag.glsl",
    //                     verticiesData,
    //                     uniformList
    //                    );
    }

    // void re
   
   private:
    // Ellipse::function<void(ModelID&,
            //                const char*,
            //                String,
            //                String,
            //                VerticiesData,
            //                UniformList)> m_addModelFunc;
    // Ellipse::function<void(ModelID, Vec3)> m_translateFunc;
    // Ellipse::function<void(ModelID, float, Vec3)> m_rotateFunc;
    // Ellipse::function<void(ModelID, Vec3)> m_scaleFunc;
};

class DemoLayer : public Ellipse::Layer
{
   public:
     DemoLayer(Ellipse::Engine& engine);
     virtual ~DemoLayer() = default;

     void initUserLayer() override;
     virtual void onEvent(Ellipse::Event& e) override;

     void onUpdateUserLayer(float dt) override;

     void setName(String name) 
     {
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
     float m_offset;
     Ellipse::Timer m_timer1;
     u32_t m_modelIncrement;
     float m_rotatedDegrees;
     Vector<Ellipse::ModelID> m_entities;
};
