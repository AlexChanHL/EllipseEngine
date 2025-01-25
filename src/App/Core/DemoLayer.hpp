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
    // m_setWorldFunc = modelManager.setWorldFunc();

    m_addFunc = modelManager.addModelCallReturn();
    m_removeFunc = modelManager.removeModelCallReturn();
    m_translateFunc = modelManager.translateModelCallReturn();
    m_rotateFunc = modelManager.rotateModelCallReturn();
    m_scaleFunc = modelManager.scaleModelCallReturn();
    m_startWorldFunc = modelManager.startWorldCallReturn();
    m_endWorldFunc = modelManager.endWorldCallReturn();

    }

    void addModel()
    {
    m_modelIDs.push_back(Ellipse::ModelID{});
    m_startWorldFunc("Main World");
    Ellipse::UniformList uniformList;
    m_addFunc(m_modelIDs[m_modelIDs.size() - 1],
              "Model",
              "CubeCustom", 
              // "../build/debug/Debug/bin/Assets/Shader/Triangle.vert.glsl",
              // "../build/debug/Debug/bin/Assets/Shader/Triangle.frag.glsl",
              "Assets/Shader/Triangle.vert.glsl",
              "Assets/Shader/Triangle.frag.glsl",
              "../Assets/ ... ",
              uniformList
             );
    m_endWorldFunc();
    }

    void removeModel(u64_t index)
    {
    m_startWorldFunc("Main World");
    m_removeFunc(m_modelIDs[index]);
    m_endWorldFunc();
    }

    void translateModel(u64_t index, Vec3 translateAmount)
    {
    m_startWorldFunc("Main World");

    m_translateFunc(m_modelIDs[index], translateAmount);

    m_endWorldFunc();
    }

    void rotateModel(u64_t index, float radiansRotate, Vec3 rotateAxis)
    {
    m_startWorldFunc("Main World");

    m_rotateFunc(m_modelIDs[index], radiansRotate, rotateAxis);

    m_endWorldFunc();
    }

    void scaleModel(u64_t index, Vec3 scaleAmount)
    {
    m_startWorldFunc("Main World");

    m_scaleFunc(m_modelIDs[index], scaleAmount);

    m_endWorldFunc();
    }

    Vector<Ellipse::ModelID> modelIDs() const
    {
    return m_modelIDs;
    }

   private:
    function<void(Ellipse::ModelID& modelID,
                  const char* modelName,
                  const char* objectName,
                  String vertexShader,
                  String fragmentShader,
                  String importPath,
                  Ellipse::UniformList uniformList)> m_addFunc;
    function<void(Ellipse::ModelID modelID)> m_removeFunc;
    function<void(Ellipse::ModelID modelID, Vec3 translationAmount)> m_translateFunc;
    function<void(Ellipse::ModelID modelID, float radians, Vec3 rotationAxis)> m_rotateFunc;
    function<void(Ellipse::ModelID modelID, Vec3 scalarAmount)> m_scaleFunc;
    function<void(const char*)> m_startWorldFunc;
    function<void()> m_endWorldFunc;
    
    Vector<Ellipse::ModelID> m_modelIDs;
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
     Ellipse::Timer m_timer1;
     u32_t m_modelIncrement;
     float m_rotatedDegrees;
     EntityCollection m_entities;
};
