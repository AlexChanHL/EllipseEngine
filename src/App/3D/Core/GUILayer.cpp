
#include "GUILayer.hpp"


GUILayer::GUILayer(Ellipse::Engine& engine)
: Layer{engine},
  m_modelList2D{engine},
  m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
  m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))},
  m_objects{m_renderModule.preDefinedObjects()}
{

}

GUILayer::~GUILayer()
{

}

void GUILayer::init()
{
    m_modelList2D.addModelDefinition("Quad", "Assets/Shader/Quad.vert.glsl", "Assets/Shader/Quad.frag.glsl", m_objects["Quad"]);
    m_modelList2D.addModelDefinition("CubeNoLight", "Assets/Shader/CubeNoLight.vert.glsl", "Assets/Shader/CubeNoLight.frag.glsl", m_objects["Cube"]);

    for(u64_t i=0;i<10;i++)
    {
    String modelName = fmt::format("FrontQuad{}", i);
    m_modelList2D.addModel(modelName.c_str(), "Quad");
    m_modelList2D.scale(modelName.c_str(), Vec2{0.5f, 0.75f});
    }
    // m_modelList2D.addModel("FrontQuad", "CubeNoLight");
    // m_modelList2D.translate("FrontQuad", Vec2{0.5f, 0.5f});
    // m_modelList2D.rotate("FrontQuad", Ellipse::EllipseMath::radians(45.0f));
}
    

void GUILayer::onEvent(Ellipse::Event& event)
{
    
}

void GUILayer::onUpdate(float dt)
{
    m_modelList2D.onUpdate();

    for(u64_t i=0;i<10;i++)
    {
    String modelName = fmt::format("FrontQuad{}", i);

    float theta = Ellipse::EllipseMath::radians(static_cast<float>(m_timeModule.secAndNSec()) * 100 + i * 10);
    double x = sin(theta) / 2;
    double y = cos(theta) / 2;
    // ELLIPSE_APP_LOG_INFO("{} {}", x, y);
    ELLIPSE_APP_LOG_INFO("theta {}", theta);
    m_modelList2D.translate(modelName.c_str(), Vec2{x, y});
    // m_modelList2D.rotate(modelName.c_str(), theta);
    }
}

