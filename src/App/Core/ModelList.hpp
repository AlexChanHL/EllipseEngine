#pragma once

#include "Ellipse.hpp"

#include "Light.hpp"


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

    void addModelDefinition(const char* name,
                            String vertex,
                            String frag
                           )
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           "LightCube",
                           Mat4{1.0f},
                           vertex,
                           frag,
                           "../Assets/ ... ",
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};
    }

    void addModelDefinition(const char* name, Ellipse::Camera& camera, Light& light)
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

    addCamera(modelModuleVal(name).uniformList(), camera);

    addMaterials(modelModuleVal(name).uniformList(), model(name));

    addLight(modelModuleVal(name).uniformList(), light);

    }

    void addModel()
    {
    String name = Ellipse::format("{}", m_models.size());
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           "Cube",
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};
    }

    void addModel(Ellipse::Camera& camera, Light& light)
    {
    String name = Ellipse::format("{}", m_models.size());
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           "Cube",
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};

    addCamera(modelModuleVal(name.c_str()).uniformList(), camera);

    addMaterials(modelModuleVal(name.c_str()).uniformList(), model(name.c_str()));

    addLight(modelModuleVal(name.c_str()).uniformList(), light);
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

    Ellipse::Model& modelModuleVal(const char* name)
    {
    if(!m_nameIds.contains(name))
    {
    std::cout << "name does not contain id model\n";
    }

    return m_modelModule.models()[m_modelModule.findModelIndex(m_nameIds[name])];
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

