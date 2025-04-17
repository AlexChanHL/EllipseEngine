#pragma once

#include "Ellipse.hpp"

class EntityCollection
{
//    public:
//     EntityCollection()
//     {
//
//     }
//     ~EntityCollection()
//     {
//
//     }
//
//     void init()
//     {
//
//     }
//
//     void setModelFunc(Ellipse::ModelManagerModule& modelManager)
//     {
//     // m_setWorldFunc = modelManager.setWorldFunc();
//
//     m_addFunc = modelManager.addModelCallReturn();
//     m_removeFunc = modelManager.removeModelCallReturn();
//     m_translateFunc = modelManager.translateModelCallReturn();
//     m_rotateFunc = modelManager.rotateModelCallReturn();
//     m_scaleFunc = modelManager.scaleModelCallReturn();
//     m_startWorldFunc = modelManager.startWorldCallReturn();
//     m_endWorldFunc = modelManager.endWorldCallReturn();
//
//     }
//
//     void addModel()
//     {
//     m_modelIDs.push_back(Ellipse::ModelID{});
//     m_startWorldFunc("Main World");
//     Ellipse::UniformList uniformList;
//     m_addFunc(m_modelIDs[m_modelIDs.size() - 1],
//               "Model",
//               "CubeCustom", 
//               // "../build/debug/Debug/bin/Assets/Shader/Triangle.vert.glsl",
//               // "../build/debug/Debug/bin/Assets/Shader/Triangle.frag.glsl",
//               "Assets/Shader/Triangle.vert.glsl",
//               "Assets/Shader/Triangle.frag.glsl",
//               "../Assets/ ... ",
//               uniformList
//              );
//     m_endWorldFunc();
//     }
//
//     void removeModel(u64_t index)
//     {
//     m_startWorldFunc("Main World");
//     m_removeFunc(m_modelIDs[index]);
//     m_endWorldFunc();
//     }
//
//     void translateModel(u64_t index, Vec3 translateAmount)
//     {
//     m_startWorldFunc("Main World");
//
//     m_translateFunc(m_modelIDs[index], translateAmount);
//
//     m_endWorldFunc();
//     }
//
//     void rotateModel(u64_t index, float radiansRotate, Vec3 rotateAxis)
//     {
//     m_startWorldFunc("Main World");
//
//     m_rotateFunc(m_modelIDs[index], radiansRotate, rotateAxis);
//
//     m_endWorldFunc();
//     }
//
//     void scaleModel(u64_t index, Vec3 scaleAmount)
//     {
//     m_startWorldFunc("Main World");
//
//     m_scaleFunc(m_modelIDs[index], scaleAmount);
//
//     m_endWorldFunc();
//     }
//
//     Vector<Ellipse::ModelID> modelIDs() const
//     {
//     return m_modelIDs;
//     }
//
//    private:
//     function<void(Ellipse::ModelID& modelID,
//                   const char* modelName,
//                   const char* objectName,
//                   String vertexShader,
//                   String fragmentShader,
//                   String importPath,
//                   Ellipse::UniformList uniformList)> m_addFunc;
//     function<void(Ellipse::ModelID modelID)> m_removeFunc;
//     function<void(Ellipse::ModelID modelID, Vec3 translationAmount)> m_translateFunc;
//     function<void(Ellipse::ModelID modelID, float radians, Vec3 rotationAxis)> m_rotateFunc;
//     function<void(Ellipse::ModelID modelID, Vec3 scalarAmount)> m_scaleFunc;
//     function<void(const char*)> m_startWorldFunc;
//     function<void()> m_endWorldFunc;
//     
//     Vector<Ellipse::ModelID> m_modelIDs;
};

inline void translateModel(Mat4& model, Vec3 translateAmount)
{
    model = Ellipse::EllipseMath::translate(model, translateAmount);
}

inline void rotateModel(Mat4& model, float radians, Vec3 rotateAmount)
{
    model = Ellipse::EllipseMath::rotate(model, radians, rotateAmount);
}

inline void scaleModel(Mat4& model, Vec3 scaleAmount)
{
   model = Ellipse::EllipseMath::scale(model, scaleAmount);
}

class ModelVal
{
   public:
    ModelVal()
    : m_model{Mat4{1.0f}},
      m_translationAmount{Vec3{1.0f}},
      m_rotationAmount{Pair<Vec3, float>{Vec3{1.0f}, 0.0f}},
      m_scaleAmount{Vec3{1.0f}}
    {

    }
    ~ModelVal()
    {

    }

    void setTranslateAmount(Vec3 translateAmount)
    {
    m_translationAmount = translateAmount;
    }

    void setRotateAmount(float radians, Vec3 rotateAmount)
    {
    m_rotationAmount = Pair<Vec3, float>{rotateAmount, radians};
    }

    void setScaleAmount(Vec3 scaleAmount)
    {
    m_scaleAmount = scaleAmount;
    }

    void totalAmounts()
    {
    m_model = Mat4{1.0f};

    translateModel(m_model, m_translationAmount);
    rotateModel(m_model, m_rotationAmount.second, m_rotationAmount.first);
    scaleModel(m_model, m_scaleAmount);
    }

    Mat4 model() const
    {
    return m_model;
    }

   private:
    Mat4 m_model;
    Vec3 m_translationAmount;
    Pair<Vec3, float> m_rotationAmount;
    Vec3 m_scaleAmount;
};

class ModelList
{
   public:
    ModelList(Ellipse::Engine& engine)
    : m_modelModule{static_cast<Ellipse::ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))}
    {

    }
    ~ModelList()
    {

    }

    void addAmounts()
    {
    for(Pair<const Ellipse::ModelID, ModelVal>& model : m_models)
    {
    model.second.totalAmounts();
    setModelVal(model.first);
    }

    }

    void addModelDefinition(const char* name)
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           "Cube",
                           Mat4{1.0f},
                           "Assets/Shader/Triangle.vert.glsl",
                           "Assets/Shader/Triangle.frag.glsl",
                           "../Assets/ ... ",
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};
    }


    void addModel()
    {
    // String name = Ellipse::format("{}", (m_models.size() - 1));
    // std::cout << name << '\n';
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           "Cube",
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds["3"] = id;
    m_models[id] = ModelVal{};
    }

    void addModel(const char* name)
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           "Cube",
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};
    }

    void removeModel(const char* name)
    {
    m_modelModule.removeModel(m_nameIds[name]);

    // Vector<Ellipse::ModelID> modelKeys = Ellipse::Utils::keyMap(m_models);
    // m_models.erase(Ellipse::Utils::iteratorNext(m_models.begin(), Ellipse::Utils::indexAt(modelKeys.begin(), modelKeys.end(), m_nameIds[name])));
    //
    // Vector<const char*> nameIDsKeys= Ellipse::Utils::keyMap(m_nameIds);
    // m_nameIds.erase(Ellipse::Utils::iteratorNext(m_nameIds.begin(), Ellipse::Utils::indexAt(nameIDsKeys.begin(), nameIDsKeys.end(), name)));
      
    erase_if(m_models, [&](Pair<const Ellipse::ModelID, ModelVal>& model){ return model.first == m_nameIds[name]; });
    erase_if(m_nameIds, [&](Pair<const String, Ellipse::ModelID>& nameID){ return strcmp(nameID.first.c_str(), name) == 0; });
    }

    void setModelVal(const char* name)
    {
    m_modelModule.models()[m_modelModule.findModelIndex(m_nameIds[name])].model() = m_models[m_nameIds[name]].model();
    }

    void setModelVal(Ellipse::ModelID id)
    {
    m_modelModule.models()[m_modelModule.findModelIndex(id)].model() = m_models[id].model();
    }

    ModelVal& model(const char* name)
    {
    if(!m_nameIds.contains(name))
    {
    std::cout << "name does not contain id\n";
    }

    return m_models[m_nameIds[name]];
    }

    Map<Ellipse::ModelID, ModelVal>& models()
    {
    return m_models;
    }

   private:
    Ellipse::ModelManagerModule& m_modelModule;
    Map<String, Ellipse::ModelID> m_nameIds;
    Map<Ellipse::ModelID, ModelVal> m_models;
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
     Ellipse::RenderModule& m_renderModule;
     Ellipse::Timer m_timer1;
     u32_t m_modelIncrement;
     float m_rotatedDegrees;
     ModelList m_modelList;
     EntityCollection m_entities;
};
