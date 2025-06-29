#pragma once

#include "ModelVal.hpp"
#include "Light.hpp"

#include "Ellipse.hpp"


class ModelList
{
   public:
    ModelList(Ellipse::Engine& engine)
    : m_modelModule{static_cast<Ellipse::ModelManagerModule&>(engine.getModule("ModelModule"))},
      m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))}
    {

    }
    virtual ~ModelList()
    {

    }

    virtual void onUpdate()
    {
    addAmounts();

    for(Pair<String, u64_t> index : m_modelIndicies)
    {
    Ellipse::Model model = m_modelModule.models()[index.second];

    String name = findModelName(model.id());
    m_renderModule.render(model.renderObject().get(), model.shaderObject().get(), model.uniformList());
    }

    }

    virtual void addAmounts()
    {
        for(Pair<const Ellipse::ModelID, ModelVal>& model : m_models)
        {
            model.second.model() = Mat4{1.0f};

            model.second.model() = Ellipse::EllipseMath::translate(model.second.model(), model.second.translationAmount());
            model.second.model() = Ellipse::EllipseMath::rotate(model.second.model(), model.second.rotationAmount().second, model.second.rotationAmount().first);
            model.second.model() = Ellipse::EllipseMath::scale(model.second.model(), model.second.scaleAmount());

            *model.second.normalMatrix() = Ellipse::EllipseMath::inverse(Ellipse::EllipseMath::transpose(Mat3{model.second.model()}));

            setModelVal(model.first);
        }
    
    }
    virtual void addModelDefinition(const char* objectName,
                            String vert,
                            String frag,
                            Ellipse::RenderObjData data
                           )
    {
    if(m_modelModule.findObjectIndex(objectName) == -1)
    {
    m_modelModule.addModelDefinition(objectName,
                                     vert,
                                     frag,
                                     data
                                    );
    return;
    }

    ELLIPSE_APP_LOG_INFO("Object already in list. Object name: {}", objectName);
    return;
    }

    virtual void addModel(const char* name, const char* objectName, Ellipse::Camera& camera, Light& light)
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           objectName,
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};
    m_modelIndicies[name] = m_modelModule.models().size() - 1;

    addCamera(modelModuleVal(name).uniformList(), camera);

    addMaterials(modelModuleVal(name).uniformList(), model(name));

    addLight(modelModuleVal(name).uniformList(), light);

    modelModuleVal(name).uniformList().setUniformLocations(modelModuleVal(name).shaderObject()->findUniformLocationList(modelModuleVal(name).uniformList()));
    }

    virtual void addModel(const char* name, const char* objectName)
    {
    Ellipse::ModelID id;
    m_modelModule.addModel(id,
                           objectName,
                           Mat4{1.0f},
                           Ellipse::UniformList{}
                          );

    m_nameIds[name] = id;
    m_models[id] = ModelVal{};
    m_modelIndicies[name] = m_modelModule.models().size() - 1;
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
    erase_if(m_modelIndicies, [&](Pair<const String, u64_t>& modelIndex){ return strcmp(modelIndex.first.c_str(), name) == 0; });
    for(Pair<String, u64_t> index : m_modelIndicies)
    {
    m_modelIndicies[index.first] = m_modelModule.findModelIndex(m_nameIds[index.first]);
    }

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

   protected:
    Ellipse::ModelManagerModule& m_modelModule;
    Ellipse::RenderModule& m_renderModule;

    Map<String, Ellipse::ModelID> m_nameIds;
    Map<Ellipse::ModelID, ModelVal> m_models;
    Map<String, u64_t> m_modelIndicies;
};

