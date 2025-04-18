
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_modelManagerLayerModule{static_cast<Ellipse::ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))},
   m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getLayerModule("RenderModule"))},
   m_modelIncrement{0},
   m_rotatedDegrees{0.0f},
   m_modelList{engine},
   m_weapon{m_modelList, engine}
{
   m_name = "Placeholder";
   m_throughLayer = false;
}

void DemoLayer::initUserLayer()
{
   // [ Layer should not set the clear color manually ]


   // [ Adding models will create models with the same name ]
  
   // Ellipse::RenderModule& renderModule = static_cast<Ellipse::RenderModule&>(m_engine.getLayerModule("RenderModule"));
  
   Ellipse::RenderModule& renderer = static_cast<Ellipse::RenderModule&>(m_engine.getLayerModule("RenderModule"));
   Pair<i32_t, i32_t> size = Ellipse::Application::get().getWindow().getWindowSize();
   renderer.setViewport(Ellipse::Viewspace{0,
                                           0,
                                           size.first,
                                           size.second
                                          }
                       );

   // m_modelList.addModelDefinition("1");
   m_light.init(m_modelList, "LightCube", "Assets/Shader/Light.vert.glsl", "Assets/Shader/Light.frag.glsl");
  
   m_light.setPosition(m_modelList, Vec3{1.0f, 2.0f, 1.0f});

   m_modelList.addModelDefinition("1", m_renderModule.camera(), m_light.light());


   
   m_modelList.model("1").setTranslateAmount(Vec3{0.0f, 0.0f, 0.0f});
   m_modelList.model("1").setRotateAmount(Ellipse::EllipseMath::Radian{90.0f}.radians(), Vec3{1.0f, 1.0f, 0.0f});

   // m_modelList.addModel(m_light.light(), m_renderModule.camera());
   // m_modelList.addModel(m_light, m_renderModule.camera());

   // m_modelList.model(previousModel(m_modelList)).uniformList().addUniform(UniformVarible<Vec3>{"light", &m_light.direction()});
   // m_modelList.model(previousModel(m_modelList)).uniformList().addUniform(UniformVarible<Vec3>{"light", &m_light.position()});
  


   // modelVal.setScaleAmount(Vec3{1.0f});

   // m_modelList.addModel("3");
   // m_modelList.model("3").setTranslateAmount(Vec3{0.0f});
  

   // // translateModelIndex(0, Vec3{0.0f, 0.0f, 0.0f});
   // // rotateModelIndex(0, Ellipse::EllipseMath::Radian{45.0f}.radians(), Vec3{1.0f, 1.0f, 0.0f});
   // for(u32_t i=0;i<30;i++)
   // {
   // float x0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
   // float y0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
   // float z0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
   // // translateModelIndex(i, Vec3{x0, y0, z0});
   // }

    // m_modelManagerLayerModule.cameraManager().cameraIndex(
    //  m_modelManagerLayerModule.cameraManager().findCameraIndex("Camera")
    //  ).setPosition(Vec3{0.0f, 0.0f, 8.0f});

   Ellipse::Application::get().getWindow().lockCursorToWindow();
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

void DemoLayer::onUpdateUserLayer(float dt)
{
    m_modelList.addAmounts();

    m_weapon.update();

    // for(u32_t i=0;i<30;i++)
    // {
    // float x0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
    // float y0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
    // float z0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
    // m_entities.translateModel(i, Vec3{x0, y0, z0});
    // m_entities.rotateModel(i, float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
    // }

    // m_modelManagerLayerModule.queryUserWorld("UserWorld");

    // m_modelManagerLayerModule.endWorld();
    // std::cout << "Updated: " << m_name << '\n';
  
    // m_player->onUpdate(dt);

    // RenderData data = m_renderModule.getRenderData();
}

bool DemoLayer::onKeyPressed(Ellipse::KeyboardPressedEvent& e)
{
     bool aPressed = Input::isKeyPressed(ELLIPSE_KEY_a);
     if(aPressed)
     {
     // ELLIPSE_APP_LOG_INFO("'a' key is pressed");
     }

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
     // m_modelManagerLayerModule.setCameraPosition("Camera", Vec3{0.0f, 0.0f, 0.0f});
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
   // e.logMousePosition();
  
   // std::cout << e.mousePositions().first / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().first) * 2.0f - 1.0f << '\n';
   // std::cout << -1.0f * (e.mousePositions().second / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().second) * 2.0f - 1.0f) << '\n';

   float xPos =  e.mousePositions().first / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().first) * 2.0f - 1.0f;
   float yPos = -1.0f * (e.mousePositions().second / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().second) * 2.0f - 1.0f);


   // [ Rename to cameraUpdateOffsetValues ]
   // ELLIPSE_APP_LOG_INFO("Mouse offset X: {} Mouse off Y: {}", Ellipse::Application::get().getWindow().mouseOffsetsLast().first, Ellipse::Application::get().getWindow().mouseOffsetsLast().second);
  
   // e.logMousePosition();
   m_renderModule.camera().registerMouseUpdate(Ellipse::Application::get().getWindow().mouseOffsets());
   // m_modelManagerLayerModule.cameraUpdateOffsetValues();

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(Ellipse::MousePressedEvent& e)
{
    // ELLIPSE_APP_LOG_INFO("{}   detected mouse press!\n", m_name);
    // ELLIPSE_APP_LOG_INFO("Pos: {} {}" ,  e.mousePosX(), e.mousePosY());

    // [ Adding model within a blocking event, ? if user pressed and event is event then the entity will 
    //   be before the first 30 entities and translate those ]
    // m_entities.addModel();
  
    m_weapon.fire();

    // if((m_weapon.weaponType() == WeaponType::AssaultRifle) && i)
    // {
    // 
    // }


    return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(Ellipse::MouseWheelEvent& e)
{
    // ELLIPSE_APP_LOG_INFO("{}", e.logMouseOffset());

    return m_throughLayer ? false : true;
}
