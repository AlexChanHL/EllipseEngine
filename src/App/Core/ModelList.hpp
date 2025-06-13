#pragma once

#include "Ellipse.hpp"

#include "Light.hpp"


class ModelList
{
   public:
    ModelList(Ellipse::Engine& engine)
    : m_modelModule{static_cast<Ellipse::ModelManagerModule&>(engine.getModule("ModelModule"))},
      m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))}
    {

    }
    ~ModelList()
    {

    }

    void onUpdate()
    {
    addAmounts();

    ELLIPSE_APP_LOG_WARN("Model list size: {}", m_modelModule.models().size());
    for(u64_t i=0;i<m_modelModule.models().size();i++)
    {
  	Ellipse::Model model = m_modelModule.models()[i];

    String name = findModelName(model.id());

    if(model.renderObject() != nullptr)
    {
    m_renderModule.render(model.renderObject(), model.shaderObject(), model.uniformList());
    }
    }

    }

    void addAmounts()
    {
    for(Pair<const Ellipse::ModelID, ModelVal>& model : m_models)
    {
    model.second.totalAmounts();
    setModelVal(model.first);
    }

    }

    void addModelDefinition(const char* name,
                            const char* objectName,
                            String vertex,
                            String frag,
                            Ellipse::RenderObjData data
                           )
    {
    Ellipse::ModelID id;
    m_modelModule.addModelDefinition(id,
                                     objectName,
                                     Mat4{1.0f},
                                     vertex,
                                     frag,
                                     Ellipse::UniformList{},
                                     data
                                    );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};

    modelModuleVal(name).uniformList().setUniformLocations(modelModuleVal(name).shaderObject()->findUniformLocationList(modelModuleVal(name).uniformList()));
    }

    void addModelDefinition(const char* name,
                            const char* objectName,
                            String vert,
                            String frag,
                            Ellipse::Camera& camera,
                            Light& light,
                            Ellipse::RenderObjData renderObjData
                           )
    {
    Ellipse::ModelID id;
    m_modelModule.addModelDefinition(id,
                                     objectName,
                                     Mat4{1.0f},
                                     vert,
                                     frag,
                                     Ellipse::UniformList{},
                                     renderObjData
                                    );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};

    addCamera(modelModuleVal(name).uniformList(), camera);

    addMaterials(modelModuleVal(name).uniformList(), model(name));

    addLight(modelModuleVal(name).uniformList(), light);

    modelModuleVal(name).uniformList().setUniformLocations(modelModuleVal(name).shaderObject()->findUniformLocationList(modelModuleVal(name).uniformList()));
    }

    void addModel(const char* name, const char* objectName, Ellipse::Camera& camera, Light& light)
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           objectName,
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};

    addCamera(modelModuleVal(name).uniformList(), camera);

    addMaterials(modelModuleVal(name).uniformList(), model(name));

    addLight(modelModuleVal(name).uniformList(), light);

    modelModuleVal(name).uniformList().setUniformLocations(modelModuleVal(name).shaderObject()->findUniformLocationList(modelModuleVal(name).uniformList()));
    }

    void addModel(const char* name, const char* objectName)
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           objectName,
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
    ELLIPSE_APP_LOG_WARN("name does not contain id model");
    }
    

    return m_modelModule.models()[m_modelModule.findModelIndex(m_nameIds[name])];
    }

    ModelVal& model(const char* name)
    {
    if(!m_nameIds.contains(name))
    {
    ELLIPSE_APP_LOG_WARN("name does not contain id, name: {}", name);
    }

    return m_models[m_nameIds[name]];
    }

    Map<Ellipse::ModelID, ModelVal>& models()
    {
    return m_models;
    }

    String findModelName(Ellipse::ModelID id)
    {
    for(auto [key, val] : m_nameIds)
    {
    if(id == val)
    {
    return key;
    }
    }

    return "No model found";
    }

   private:
    Ellipse::ModelManagerModule& m_modelModule;
    Ellipse::RenderModule& m_renderModule;
    Map<String, Ellipse::ModelID> m_nameIds;
    Map<Ellipse::ModelID, ModelVal> m_models;
};

