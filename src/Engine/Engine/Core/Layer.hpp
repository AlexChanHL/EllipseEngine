#pragma once

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
    // virtual void onUpdate(float dt) = 0;

    virtual bool isHidden() = 0;
    virtual void hideLayer() = 0;
    virtual void showLayer() = 0;

  private:

};

class Layer : public ILayer
{
  public:
    Layer(Engine& engine)
    : m_renderModule{static_cast<RenderModule&>(engine.getModule("RenderModule"))}
    {

    }

    virtual ~Layer() = default;

    virtual void init() override {}
    // virtual void init() override 
    // {
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
                  Vector<float> verticies,
                  UniformList uniforms
                  )
    {
    uLong_t size = m_modelsToBeRendered.size();
    Model model = m_renderModule.createModel(name, vShader, fShader, verticies, uniforms, size);
    m_modelsToBeRendered.push_back(model);

    // Redirect pointer to the value in vector
    // Mat4* modelMat = &m_modelsToBeRendered[size].modelMat();
    // std::cout << "Create " << model.name() << '\n';
    // m_modelsToBeRendered[size].shaderObj().setUniformPtr(UniformVarible<Mat4>{"model", modelMat});

    for(uLong_t i = 0; i < m_modelsToBeRendered.size(); i++)
    {
    Mat4* modelMat = &m_modelsToBeRendered[i].modelMat();
    m_modelsToBeRendered[i].shaderObj().setUniformPtr(UniformVarible<Mat4>{"model", modelMat});
    }

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
    auto model = std::find_if(m_modelsToBeRendered.begin(),
                              m_modelsToBeRendered.end(),
     [&](Model model){ return model.entityRef() == entity; }
                             );

    if(model == m_modelsToBeRendered.end())
    {
    ELPSE_ENGINE_LOG_WARN("Couldn't find model");
    }

    return &(*model);
    }

    void onUpdateModelMatricies()
    {
    for(Model& model : m_modelsToBeRendered)
    {
    model.resetModelMat();

    // std::cout << model.name() << '\n';
    ::Ellipse::scaleModel(model);
    ::Ellipse::rotateModel(model);
    ::Ellipse::translateModel(model);
    }

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
    RenderModule& m_renderModule;

    bool m_hidden = false;
    bool m_throughLayer;
    String m_name;

  private:
};

} //Ellipse namespace
