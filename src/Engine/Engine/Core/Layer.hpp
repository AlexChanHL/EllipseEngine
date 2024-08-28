#pragma once

#include "TimeModule.hpp"
#include "Event/Event.hpp"
#include "Renderer/RenderModule.hpp"
#include "Math/Matrix.hpp"
#include "Engine/Engine.hpp"
#include "Debug/Log/Log.hpp"

namespace Ellipse
{

class ILayer
{
  public:
    ILayer() = default;
    virtual ~ILayer() = default;

    virtual void init() = 0;
    virtual void onEvent(Event& event) = 0;
    virtual void onUpdate(float dt) = 0;

    virtual bool isHidden() = 0;
    virtual void hideLayer() = 0;
    virtual void showLayer() = 0;

  private:

};

class Layer : public ILayer
{
  public:
    Layer(Engine& engine)
    : m_timeModule{static_cast<TimeModule&>(engine.getModule("TimeModule"))},
      m_renderModule{static_cast<RenderModule&>(engine.getModule("RenderModule"))}
    {

    }

    virtual ~Layer() = default;

    virtual void init() override {}
    // virtual void init() override 
    // {
    //   // [ RenderModule should do this ]
    //   setClearColor(m_engine.getDefaultValue("clear color"));
    //   initUserLayer();
    // }
    virtual void onEvent(Event& event) override = 0;
    virtual void onUpdateUserLayer(float dt) = 0;
    virtual void onUpdate(float dt) override
    {
    onUpdateUserLayer(dt);

    onUpdateModelMatricies();

    renderModelsToBeRendered();
    }

    EntityRef addModel(const char* name,
                  const char* vShader,
                  const char* fShader,
                  VerticiesData verts,
                  UniformList uniforms
                  )
    {
    uLong_t size = m_modelsToBeRendered.size();
    Model model = m_renderModule.createModel(name, vShader, fShader, verts, uniforms, size);
    m_modelsToBeRendered.push_back(model);

    // Redirect pointer to the value in vector

    // m_modelsToBeRendered[size].shaderObj().getUniforms().printUniformList();
      
    // for(uLong_t i = 0; i < m_modelsToBeRendered.size(); i++)
    // {
    // Mat4* modelMat = &m_modelsToBeRendered[i].modelMat();
    // m_modelsToBeRendered[i].shaderObj().setUniformPtr(UniformVarible<Mat4>{"model", modelMat});
    // }

      
    return size;
    }

    EntityRef addQuad(Vec3 pos)
    {
    uLong_t size = m_modelsToBeRendered.size();
    Model model = m_renderModule.create2DShape("Quad", size);
    m_modelsToBeRendered.push_back(model);
       
    positionModel(size, pos);

    return size;
    }

    void scaleModel(EntityRef entity, Vec3 scalarAmount)
    {
    Model* model = findModelFromEntity(entity);
    model->setScalarAmount(scalarAmount);
    }
    void rotateModel(EntityRef entity, float radians, Vec3 axis)
    {
    Model* model = findModelFromEntity(entity);
    model->setRotationAmount(radians, axis);
    }
    void positionModel(EntityRef entity, Vec3 axis)
    {
    Model* model = findModelFromEntity(entity);
    model->setTranslationAmount(axis);
    }

    Model* findModelFromEntity(EntityRef entity)
    {
    // auto model = std::find_if(m_modelsToBeRendered.begin(),
    //                           m_modelsToBeRendered.end(),
    //  [&](Model model){ return model.entityRef() == entity; }
    //                          );

    auto itVal = m_modelsToBeRendered.begin(); 
    for(auto it = m_modelsToBeRendered.begin(); it != m_modelsToBeRendered.end(); it++)
    {
    if(it->entityRef() == entity)
    {
    itVal = it;
    }
    }

    if(itVal == m_modelsToBeRendered.end())
    {
    ELPSE_ENGINE_LOG_WARN("Couldn't find model");
    }

    // model->shaderObj().getUniforms().printUniformList();

    return &(*itVal);
    }

    // [ Use a entity manager for model creation ]

    void onUpdateModelMatricies()
    {
    for(Model& model : m_modelsToBeRendered)
    {
    model.resetModelMat();

    // std::cout << model.name() << '\n';
    ::Ellipse::translateModel(model);
    ::Ellipse::rotateModel(model);
    ::Ellipse::scaleModel(model);
    }

    // exit(1);

    }
    void positionCameraUp(float amount)
    {
    // m_renderModule.setCameraLeft(amount);
    }

    void positionCameraDown(float amount)
    {
    // m_renderModule.setCameraLeft(amount);
    }


    void positionCameraLeft(float amount)
    {
    m_renderModule.setCameraLeft(amount);
    }

    void positionCameraRight(float amount)
    {
    m_renderModule.setCameraRight(amount);
    }

    // [ Maybe the engine should render module wating for render ]
    void renderModelsToBeRendered()
    {
    for(Model& a : m_modelsToBeRendered)
    {
    // std::cout << &a.modelMat() << '\n';
    // a.shaderObj().getUniforms().printUniformList();
    m_renderModule.renderModel(a);
    }

    // [ Hackish solution, make a better way of updating the projection
    //  matrix to a new screen size ]
    // Updating Camera
    m_renderModule.updateCamera();

    }

    static SharedPtr<ILayer> createDefaultLayer();

  protected:
    void setClearColor(Vec4 col)
    {
    m_renderModule.setClearColor(col);
    }

    virtual bool isHidden() override { return m_hidden; }

    virtual void hideLayer() override { m_hidden = true; }
    virtual void showLayer() override { m_hidden = false; }

  protected:
    Vector<Model> m_modelsToBeRendered;
    // [ Don't have Rendermodule in layer so user can use layers in 
    //   seperate scenerios ]
    TimeModule& m_timeModule;
    RenderModule& m_renderModule;

    bool m_hidden = false;
    bool m_throughLayer;
    String m_name;

  private:
};

} //Ellipse namespace
