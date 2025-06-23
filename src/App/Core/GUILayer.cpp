
#include "GUILayer.hpp"


GUILayer::GUILayer(Ellipse::Engine& engine)
: Layer{engine},
  m_modelList2D{engine},
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

    m_modelList2D.addModel("FrontQuad", "Quad");
}
    

void GUILayer::onEvent(Ellipse::Event& event)
{
    
}

void GUILayer::onUpdate(float dt)
{
    m_modelList2D.onUpdate();
}

