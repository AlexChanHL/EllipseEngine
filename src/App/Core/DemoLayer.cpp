
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

DemoLayer::DemoLayer()
: m_renderer{Ellipse::Application::get().getRenderer()},
  m_name{"Placeholder"},
  m_throughLayer{false}
{

}

void DemoLayer::init()
{
   m_renderer.setClearColor(glm::vec4{1.0f, 1.0f, 0.0f, 1.0f});

   m_renderObj = m_renderer.createRenderObj();
   m_shaderObj = m_renderer.createShaderObj();

   m_shaderObj->addShader("Assets/Shader/Triangle.vert.glsl");
   m_shaderObj->addShader("Assets/Shader/Triangle.frag.glsl");
   m_shaderObj->linkShaders();
  
     std::vector<float> verticies = 
     {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
       -0.5f, -0.5f,  0.0f,
     };
  
   m_renderObj = m_renderer.createRenderObj();
   m_renderObj->initRenderObj(verticies);
}

void DemoLayer::onEvent(Event& e)
{

       EventDispatcher dispatcher(e);
       dispatcher.dispatchEvent<KeyboardPressedEvent>(
       KEYBOARD_PRESSED_EVENT,  
       BIND_EVENT_FN(onKeyPressed)
      );
       dispatcher.dispatchEvent<MousePressedEvent>(
       MOUSE_PRESSED_EVENT,
       BIND_EVENT_FN(onMousePressed)
      );
      dispatcher.dispatchEvent<MouseWheelEvent>(
       MOUSE_WHEEL_EVENT,
       BIND_EVENT_FN(onMouseWheel)
      );
}

void DemoLayer::onUpdate()
{
    // std::cout << "Updated: " << m_name << "\n";
  
    m_shaderObj->use();
    m_shaderObj->setUniform("offset", m_offset);

    m_renderer.render(*m_renderObj, *m_shaderObj);
  
    // RenderData data = m_renderer.getRenderData();
}

bool DemoLayer::onKeyPressed(KeyboardPressedEvent& e)
{
     bool aPressed = Input::isKeyPressed(ELLIPSE_KEY_a);
      if(aPressed)
       {
   std::cout << "'a' key is pressed" << "\n";
       }

    switch(e.keyCode())
     {
        case ELLIPSE_KEY_a:
        m_offset -= 0.05f;
         break;
        case ELLIPSE_KEY_d:
        m_offset += 0.05f;
         break;
       default:
        break;
     }

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(MousePressedEvent& e)
{
  // std::cout << e.logMousePosition() << "\n";
    std::cout << m_name << " detected mouse press!\n";

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(MouseWheelEvent& e)
{
  std::cout << e.logMouseOffset() << "\n";

   return m_throughLayer ? false : true;
}
