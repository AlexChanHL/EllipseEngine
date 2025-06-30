
#include "Ellipse.hpp"

#include "DemoLayer.hpp"


DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_modelManagerLayerModule{static_cast<Ellipse::ModelManagerModule&>(engine.getModule("ModelModule"))},
   m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))},
   m_modelIncrement{0},
   m_rotatedDegrees{0.0f},
   m_modelList{engine},
   m_weapon{m_modelList, engine, m_light.light()},
   m_cubeMadeCube{m_modelList, engine, m_light.light()},
   m_objects{m_renderModule.preDefinedObjects()}
{
   m_name = "Placeholder";
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


   Ellipse::RenderObjData cube = m_objects["Cube"];
   Ellipse::RenderObjData quad = m_objects["Quad"];

   m_modelList.addModelDefinition("LightCube",
                                  "Assets/Shader/Light.vert.glsl",
                                  "Assets/Shader/Light.frag.glsl",
                                  cube
                                 );
   m_modelList.addModelDefinition("Cube",
                                  "Assets/Shader/Cube.vert.glsl",
                                  "Assets/Shader/Cube.frag.glsl",
                                  cube
                                 );
   m_modelList.addModelDefinition("Quad",
                                  "Assets/Shader/Quad.vert.glsl",
                                  "Assets/Shader/Quad.frag.glsl",
                                  quad
                                 );

   m_light.init(m_modelList, "LightCube");
   m_light.setPosition(m_modelList, Vec3{1.0f, 2.0f, 1.0f});

   m_modelList.addModel("Cube1",
                        "Cube",
                        m_renderModule.camera(),
                        m_light.light()
                       );

   m_cubeMadeCube.init();


   m_modelList.addModel("Quad1",
                        "Quad",
                        m_renderModule.camera(),
                        m_light.light()
                       );
   m_modelList.model("Cube1").setTranslateAmount(Vec3{0.0f, 0.5f, -0.5f});
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
    // ELLIPSE_APP_LOG_INFO("{}", m_timeModule.secAndNSec())
    // m_modelList.model("Cube1").setRotateAmount(Ellipse::EllipseMath::radians(static_cast<float>(m_timeModule.secAndNSec() * 16)),
    //                                        Vec3{0.0f, 1.0f, 0.0f}
    //                                       );

    // Ellipse::EllipseMath::rotate(Ellipse::EllipseMath::radians(static_cast<float>(m_timeModule.secAndNSec() * 16)), m_renderModule.camera().front(), Vec3(0);
    m_modelList.model("Cube1").setRotateAmount(Ellipse::EllipseMath::radians(30.0f),
                                               Vec3{0.0f, 1.0f, 0.0f}
                                              );

    m_modelList.onUpdate();

    if((m_weapon.weaponType() == WeaponType::AssaultRifle) && Ellipse::Input::isMousePressed(ELLIPSE_MOUSE_BUTTON_LEFT))
    {
    m_weapon.fire();
    }

    m_weapon.update();


    m_cubeMadeCube.linearFunc([&](Pixel& pixel)
    {
    Vec3 position = pixel.worldPosition();

    double time = m_timeModule.secAndNSec() * 16;
    float radiansRotated = Ellipse::EllipseMath::radians(static_cast<float>(time));

    position = Ellipse::EllipseMath::rotateXAxis(position, radiansRotated);

    Mat3 yAxisMatrix{1.0f};

    position = Ellipse::EllipseMath::rotateYAxis(position, radiansRotated);

    Mat3 zAxisMatrix{1.0f};

    // position = Ellipse::EllipseMath::rotateZAxis(position, radiansRotated);

    pixel.setPosition(position); 
    }
                             );

    // m_player->onUpdate(dt);

    // RenderData data = m_renderModule.getRenderData();
}

bool DemoLayer::onKeyPressed(Ellipse::KeyboardPressedEvent& e)
{
     // bool aPressed = Ellipse::Input::isKeyPressed(ELLIPSE_KEY_a);
     // if(aPressed)
     // {
     // ELLIPSE_APP_LOG_INFO("'a' key is pressed");
     // }

     switch(e.keyCode())
     {
     case ELLIPSE_KEY_w:
     m_renderModule.setCameraFront(1.0f);
     break;
     case ELLIPSE_KEY_s:
     m_renderModule.setCameraBackward(1.0f);
     break;
     case ELLIPSE_KEY_a:
     m_renderModule.setCameraLeft(1.0f);
     break;
     case ELLIPSE_KEY_d:
     m_renderModule.setCameraRight(1.0f);
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
     m_weapon.changeWeaponType(WeaponType::Pistol);
     break;
     case ELLIPSE_KEY_2:
     m_weapon.changeWeaponType(WeaponType::Shotgun);
     break;
     case ELLIPSE_KEY_3:
     m_weapon.changeWeaponType(WeaponType::AssaultRifle);
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
     {
     String modelName = Ellipse::format("{}", (m_modelList.models().size() - 1));
     m_modelList.removeModel(modelName.c_str());
     }
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


   m_renderModule.updateCamera(Ellipse::Application::get().getWindow().mouseOffsets());

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(Ellipse::MousePressedEvent& e)
{
    m_weapon.fire();
    return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(Ellipse::MouseWheelEvent& e)
{
    return m_throughLayer ? false : true;
}
