
#include "Ellipse.hpp"

#include "DemoLayer.hpp"


DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_modelManagerLayerModule{static_cast<Ellipse::ModelManagerModule&>(engine.getModule("ModelModule"))},
   m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))},
   m_modelList{engine},
   m_objects{m_renderModule.preDefinedObjects()}
{
   m_throughLayer = false;
}

void DemoLayer::init()
{
    Ellipse::RenderModule& renderer = static_cast<Ellipse::RenderModule&>(m_engine.getModule("RenderModule"));
    Pair<i32_t, i32_t> size = Ellipse::Application::get().getWindow().getWindowSize();
    renderer.setViewport(Ellipse::Viewspace{0,
                                            0,
                                            size.first,
                                            size.second
                                           }
                        );


    Ellipse::RenderObjData quad = m_objects["Quad"];

    m_modelList.addModelDefinition("Quad",
                                   "Assets/Shader/Quad.vert.glsl",
                                   "Assets/Shader/Quad.frag.glsl",
                                   quad
                                  );
    // for(u64_t i=0;i<10;i++)
    // {
    // String modelName = fmt::format("FrontQuad{}", i);
    // m_modelList.addModel(modelName.c_str(), "Quad");
    // m_modelList.scale(modelName.c_str(), Vec2{0.5f, 0.75f});
    // }

    m_modelList.addModel("FrontQuad", "Quad");
    m_modelList.translate("FrontQuad", Vec2{-0.5f, 0.1f});
    m_modelList.scale("FrontQuad", Vec2{0.5f, 0.75f});
}

void DemoLayer::onEvent(Ellipse::Event& e)
{
    Ellipse::EventDispatcher dispatcher(e);
    dispatcher.dispatchEvent<Ellipse::KeyboardPressedEvent>(
    KEYBOARD_PRESSED_EVENT,  
    BIND_EVENT_FN(onKeyPressed)
    );
    dispatcher.dispatchEvent<Ellipse::MouseMotionEvent>(
    MOUSE_MOTION_EVENT,
    BIND_EVENT_FN(onMouseMotion)
    );
    dispatcher.dispatchEvent<Ellipse::MousePressedEvent>(
    MOUSE_PRESSED_EVENT,
    BIND_EVENT_FN(onMousePressed)
    );
    dispatcher.dispatchEvent<Ellipse::MouseWheelEvent>(
    MOUSE_WHEEL_EVENT,
    BIND_EVENT_FN(onMouseWheel)
    );
}

void DemoLayer::onUpdate(float dt)
{
    // for(u64_t i=0;i<10;i++)
    // {
    // String modelName = fmt::format("FrontQuad{}", i);
    //
    // float theta = Ellipse::EllipseMath::radians(static_cast<float>(m_timeModule.secAndNSec()) * 100 + i * 10);
    // double x = sin(theta) / 2;
    // double y = cos(theta) / 2;
    // // ELLIPSE_APP_LOG_INFO("{} {}", x, y);
    // ELLIPSE_APP_LOG_INFO("theta {}", theta);
    // m_modelList.translate(modelName.c_str(), Vec2{x, y});
    // m_modelList.rotate(modelName.c_str(), theta);
    // }

    m_modelList.onUpdate();
}

bool DemoLayer::onKeyPressed(Ellipse::KeyboardPressedEvent& e)
{
     switch(e.keyCode())
     {
     case ELLIPSE_KEY_w:
     // m_renderModule.setCameraUp(1.0f);
     break;
     case ELLIPSE_KEY_s:
     // m_renderModule.setCameraDown(1.0f);
     break;
     case ELLIPSE_KEY_a:
     // m_renderModule.setCameraLeft(1.0f);
     break;
     case ELLIPSE_KEY_d:
     // m_renderModule.setCameraRight(1.0f);
     break;
     case ELLIPSE_KEY_p:
     break;
     case ELLIPSE_KEY_b:
     {
     // Ellipse::Camera& camera = m_modelManagerLayerModule.cameraIndex(m_modelManagerLayerModule.findCameraIndex("Camera"));

     // camera.setCameraSpeed(camera.cameraSpeed() + 1.0f);
     }
     break;
     case ELLIPSE_KEY_n:
     {
     // Ellipse::Camera& camera = m_modelManagerLayerModule.cameraIndex(m_modelManagerLayerModule.findCameraIndex("Camera"));
     // camera.setCameraSpeed(camera.cameraSpeed() - 1.0f);
     }
     break;
     case ELLIPSE_KEY_ESCAPE:
     Ellipse::Application::get().quitApplication();
     break;
     case ELLIPSE_KEY_1:
     break;
     case ELLIPSE_KEY_2:
     break;
     case ELLIPSE_KEY_3:
     break;
     case ELLIPSE_KEY_9:
     Ellipse::Application::get().getWindow().lockCursorToWindow();
     break;
     case ELLIPSE_KEY_0:
     Ellipse::Application::get().getWindow().unlockCursorToWindow();
     break;
     case ELLIPSE_KEY_o:
     // m_timeModule.unPause();
     break;
     case ELLIPSE_KEY_i:
     break;
     default:
     break;
     }

     return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseMotion(Ellipse::MouseMotionEvent& e)
{
   float xPos =  e.mousePositions().first / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().first) * 2.0f - 1.0f;
   float yPos = -1.0f * (e.mousePositions().second / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().second) * 2.0f - 1.0f);


   // m_renderModule.updateCamera(Ellipse::Application::get().getWindow().mouseOffsets());

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(Ellipse::MousePressedEvent& e)
{
    return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(Ellipse::MouseWheelEvent& e)
{
    return m_throughLayer ? false : true;
}
