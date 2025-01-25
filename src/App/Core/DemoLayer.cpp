
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_modelManagerLayerModule{static_cast<Ellipse::ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))},
   // m_renderLayerModule{static_cast<Ellipse::RenderLayerModule&>(engine.getLayerModule("RenderLayerModule"))},
   m_modelIncrement{0},
   m_rotatedDegrees{0.0f}
{
   m_name = "Placeholder";
   m_throughLayer = false;

   m_entities.setModelFunc(m_modelManagerLayerModule);
}

void DemoLayer::initUserLayer()
{
   // [ Layer should not set the clear color manually ]

   m_modelManagerLayerModule.addWorld("Main World");
   m_modelManagerLayerModule.addSubWorld("SubWorld", "Main World");
   m_modelManagerLayerModule.addSubWorld("SubWorld1", "Main World");
   // m_modelManagerLayerModule.addSubWorld("SubWorld2", "Main World");
   // m_modelManagerLayerModule.addWorld("Main World", Ellipse::Viewspace{
   //  Ellipse::Application::get().getWindow().getWindowSize().first,
   //  Ellipse::Application::get().getWindow().getWindowSize().second,
   //  0,
   //  0
   //                                                                    }
   //                                   );
  
   m_modelManagerLayerModule.addUserWorld("Main World", "UserWorld");
   m_modelManagerLayerModule.addUserCamera("UserWorld", "Camera");
   m_modelManagerLayerModule.addUserSubWorld("SubWorld", "UserWorld");

   // [ Add a default camera if user does not specify ]
   // m_modelManagerLayerModule.addUserWorld("Main World", "UserWorld1");
   // m_modelManagerLayerModule.addUserSubWorld("SubWorld1", "UserWorld1");

   // m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{0,
   //  0,
   //  Ellipse::Application::get().getWindow().getWindowSize().first / 2,
   //  Ellipse::Application::get().getWindow().getWindowSize().second}); 


   // [ Adding models will create models with the same name ]

   // m_modelManagerLayerModule.startWorld("Main World");

   // for(u32_t i=0;i<30;i++)
   // {
   // m_entities.addModel();
   // }
   // // translateModelIndex(0, Vec3{0.0f, 0.0f, 0.0f});
   // // rotateModelIndex(0, Ellipse::EllipseMath::Radian{45.0f}.radians(), Vec3{1.0f, 1.0f, 0.0f});
   // for(u32_t i=0;i<30;i++)
   // {
   // float x0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
   // float y0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
   // float z0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
   // // translateModelIndex(i, Vec3{x0, y0, z0});
   // }

    m_modelManagerLayerModule.cameraManager().cameraIndex(
     m_modelManagerLayerModule.cameraManager().findCameraIndex("Camera")
     ).setPosition(Vec3{0.0f, 0.0f, 8.0f});

   Ellipse::Application::get().getWindow().lockCursorToWindow();

   // m_modelManagerLayerModule.hideAllModels("UserWorld1");
   // m_modelManagerLayerModule.startSubWorld("SubWorld");

   // m_modelManagerLayerModule.setWireFrameModel(m_entities[0], "UserWorld1");

   // m_modelManagerLayerModule.startSubWorld("SubWorld1");
   //
   // m_modelManagerLayerModule.endSubWorld();
   // //
   // m_modelManagerLayerModule.startSubWorld("SubWorld");
  
   // m_modelManagerLayerModule.setWireFrameModel(m_entities[0], "UserWorld1");

   // m_modelManagerLayerModule.endSubWorld();

   // m_modelManagerLayerModule.queryUserWorld("UserWorld");
   // m_modelManagerLayerModule.queryUserWorld("UserWorld1");

   // m_modelManagerLayerModule.startSubWorld("SubWorld1");
   //
   // m_modelManagerLayerModule.endSubWorld();
   //
   // m_modelManagerLayerModule.endWorld();
  
   // This camera will have a different position in the world
   // m_modelManagerLayerModule.setSubWorld("Camera 2");


   // m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{
   //  Ellipse::Application::get().getWindow().getWindowSize().first / 2,
   //  0,
   //  Ellipse::Application::get().getWindow().getWindowSize().first / 2,
   //  Ellipse::Application::get().getWindow().getWindowSize().second});
   //
   // [ Have a model manager do all this work ]
   // for(u32_t i = 0; i < 10; i++)
   // {
   // m_entities.push_back(addQuad(Vec3{-0.25f, 0.4f, 0.0f}));
   // }
   // for(u32_t i = 0; i < 10; i++)
   // {
   // positionModel(m_entities[i], Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
   // }
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
    // if(m_timeModule.setTimer(m_timer1, 1))
    // {
    // for(u32_t i=0;i<30;i++)
    // {
    // float x0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
    // float y0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
    // float z0 = Ellipse::EllipseMath::randRealDist<float>(0, 10);
    // m_entities.translateModel(i, Vec3{x0, y0, z0});
    // m_entities.rotateModel(i, float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
    // }
    //
    // }

    // m_modelManagerLayerModule.queryUserWorld("UserWorld");

    // m_modelManagerLayerModule.endWorld();


    // m_modelManagerLayerModule.startWorld("Main World");

    // m_modelManagerLayerModule.queryUserWorld("UserWorld");
    // translateModelIndex(0, Vec3{0.5f, 0.0f, 0.0f});
    // rotateModelIndex(0, 45.0f, Vec3{0.0f, 0.0f, 1.0f});
    // rotateModelIndex(0, float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
    // scaleModelIndex(0, Vec3{1.0f, 1.0f, 1.0f});
    // removeModelIndex(0);
    // if(m_timeModule.setTimer(m_timer1, 1))
    // {
    // rotateModelIndex(0, float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
    // }
  
    // m_modelManagerLayerModule.startSubWorld("SubWorld1");

    // m_modelManagerLayerModule.endSubWorld();
    //
    // m_modelManagerLayerModule.startSubWorld("SubWorld");
   
    // m_modelManagerLayerModule.setWireFrameModel(m_entities[0], "UserWorld1");
    // rotateModelIndex(2, Ellipse::EllipseMath::Radian(45.0f).radians(), Vec3{0.0f, 0.0f, 1.0f});

    // m_modelManagerLayerModule.endSubWorld();

    // m_modelManagerLayerModule.queryUserWorld("UserWorld");
    // m_modelManagerLayerModule.queryUserWorld("UserWorld1");

    // m_modelManagerLayerModule.startSubWorld("SubWorld1");
    //
    // m_modelManagerLayerModule.endSubWorld();
    //
    // m_modelManagerLayerModule.endWorld();

    // if(m_timeModule.setTimer(m_timer1, 1))
    // {
    // // Logger cannot use info
    // ELLIPSE_APP_LOG_WARN("One second has passed");
    // for(u32_t i = 0; i < m_entities.size(); i++)
    // {
    // positionModel(m_entities[i], Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
    // }
    // }
    // for(auto entity : m_entities)
    // {
    // rotateModel(entity, float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
    // }

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
     m_modelManagerLayerModule.translateCameraForward("Camera");
      break;
     case ELLIPSE_KEY_s:
     m_modelManagerLayerModule.translateCameraBackward("Camera");
      break;
     case ELLIPSE_KEY_a:
     m_modelManagerLayerModule.translateCameraLeft("Camera");
      break;
     case ELLIPSE_KEY_d:
     m_modelManagerLayerModule.translateCameraRight("Camera");
      break;
     case ELLIPSE_KEY_p:
     m_modelManagerLayerModule.setCameraPosition("Camera", Vec3{0.0f, 0.0f, 0.0f});
     break;
     case ELLIPSE_KEY_b:
     {
     Ellipse::Camera& camera = m_modelManagerLayerModule.cameraIndex(m_modelManagerLayerModule.findCameraIndex("Camera"));

     camera.setCameraSpeed(camera.cameraSpeed() + 1.0f);
     }
     break;
     case ELLIPSE_KEY_n:
     {
     Ellipse::Camera& camera = m_modelManagerLayerModule.cameraIndex(m_modelManagerLayerModule.findCameraIndex("Camera"));
     camera.setCameraSpeed(camera.cameraSpeed() - 1.0f);
     }
     break;
     case ELLIPSE_KEY_ESCAPE:
     Ellipse::Application::get().quitApplication();
     break;
     case ELLIPSE_KEY_9:
     // m_modelManagerLayerModule.addModel(lastestModel());
     // updateLastestModel();
      break;
     case ELLIPSE_KEY_0:
     m_entities.removeModel(m_entities.modelIDs().size() - 1);
     break;
     case ELLIPSE_KEY_1:
     Ellipse::Application::get().getWindow().lockCursorToWindow();
     break;
     case ELLIPSE_KEY_2:
     Ellipse::Application::get().getWindow().unlockCursorToWindow();
     break;
     case ELLIPSE_KEY_o:
     // m_timeModule.unPause();
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
  
   // Ellipse::EllipseMath::printVec(m_modelManagerLayerModule.retrieveCamera("Camera").front());
  
   // e.logMousePosition();
   // m_modelManagerLayerModule.registerMouseUpdate(e.offsets());
   m_modelManagerLayerModule.registerMouseUpdate(Ellipse::Application::get().getWindow().mouseOffsets());
   // m_modelManagerLayerModule.cameraUpdateOffsetValues();

   m_modelManagerLayerModule.startWorld("Main World");

   // m_modelManagerLayerModule.translateModel(m_entities[0], Vec3{xPos, yPos, 0.0f});

   m_modelManagerLayerModule.endWorld();

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(Ellipse::MousePressedEvent& e)
{
    ELLIPSE_APP_LOG_INFO("{}   detected mouse press!\n", m_name);
    ELLIPSE_APP_LOG_INFO("Pos: : {} {}" ,  e.mousePosX(), e.mousePosY());

    // [ Adding model within a blocking event, ? if user pressed and event is event then the entity will 
    //   be before the first 30 entities and translate those ]
    m_entities.addModel();
    Ellipse::Camera& camera = m_modelManagerLayerModule.cameraManager().cameraIndex(m_modelManagerLayerModule.cameraManager().findCameraIndex("Camera"));
    m_entities.translateModel(m_entities.modelIDs().size() - 1, camera.position() + (4.0f * camera.front()));

    return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(Ellipse::MouseWheelEvent& e)
{
    ELLIPSE_APP_LOG_INFO("{}", e.logMouseOffset());

    return m_throughLayer ? false : true;
}
