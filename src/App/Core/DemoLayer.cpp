
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
   m_cubeMadeCube{m_modelList, engine, m_light.light()}
{
   m_name = "Placeholder";
   m_throughLayer = false;

   Ellipse::RenderObjData cubeData;
   cubeData.setIndicies(Vector<u32_t>{0, 2, 3,
                                      0, 1, 3,

                                      4, 5, 7,
                                      4, 6, 7,

                                      8, 9, 11,
                                      8, 10, 11,

                                      12, 13, 15,
                                      12, 14, 15,

                                      16, 17, 19,
                                      16, 18, 19,

                                      20, 21, 23,
                                      20, 22, 23
                                      }
                                     );
   cubeData.setPositions(Vector<float>{-0.5f,  0.5f,  0.5f,  
                                       0.5f,  0.5f,  0.5f,  
                                      -0.5f, -0.5f,  0.5f,  
                                       0.5f, -0.5f,  0.5f,  

                                       0.5f,  0.5f,  0.5f,  
                                       0.5f,  0.5f, -0.5f,  
                                       0.5f, -0.5f,  0.5f,  
                                       0.5f, -0.5f, -0.5f,  

                                      -0.5f,  0.5f, -0.5f,  
                                       0.5f,  0.5f, -0.5f,  
                                      -0.5f, -0.5f, -0.5f,  
                                       0.5f, -0.5f, -0.5f,  

                                      -0.5f,  0.5f,  0.5f,  
                                      -0.5f,  0.5f, -0.5f,  
                                      -0.5f, -0.5f,  0.5f,  
                                      -0.5f, -0.5f, -0.5f,  

                                      -0.5f,  0.5f, -0.5f,  
                                       0.5f,  0.5f, -0.5f,  
                                      -0.5f,  0.5f,  0.5f,  
                                       0.5f,  0.5f,  0.5f,  

                                      -0.5f, -0.5f,  0.5f,  
                                       0.5f, -0.5f,  0.5f,  
                                      -0.5f, -0.5f, -0.5f,
                                       0.5f, -0.5f, -0.5f
                                      }
                                     );
   cubeData.setNormals(std::vector<float>{0,  0,  1,
                                          0,  0,  1,
                                          0,  0,  1,
                                          0,  0,  1,

                                          1,  0,  0,
                                          1,  0,  0,
                                          1,  0,  0,
                                          1,  0,  0,

                                          0,  0, -1,
                                          0,  0, -1,
                                          0,  0, -1,
                                          0,  0, -1,

                                         -1,  0,  0,
                                         -1,  0,  0,
                                         -1,  0,  0,
                                         -1,  0,  0,

                                          0,  1,  0,
                                          0,  1,  0,
                                          0,  1,  0,
                                          0,  1,  0,

                                          0, -1,  0,
                                          0, -1,  0,
                                          0, -1,  0,
                                          0, -1,  0
                                        }
                                       );
   cubeData.setTexCoords(Vector<float>{0.0f, 0.0f,
                                       1.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,

                                       0.0f, 0.0f,
                                       1.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,

                                       0.0f, 0.0f,
                                       1.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,

                                       0.0f, 0.0f,
                                       1.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,

                                       0.0f, 0.0f,
                                       1.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,

                                       0.0f, 0.0f,
                                       1.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,
                                      }
                                     );


   Ellipse::RenderObjData quadData;

   quadData.setIndicies(Vector<u32_t>{0, 1, 2,
                                      1, 2, 3 
                                      }
                        );
   quadData.setPositions(Vector<float>{-0.5f, 0.5f, 0.0f,
                                        0.5f, 0.5f, 0.0f,
                                       -0.5f, -0.5f, 0.0f,
                                        0.5f, -0.5f, 0.0f
                                      }
                        );
   quadData.setNormals(Vector<float>{0.0f, 0.0f, 1.0f,
                                     0.0f, 0.0f, 1.0f,
                                     0.0f, 0.0f, 1.0f,
                                     0.0f, 0.0f, 1.0f
                                    }
                      );
   quadData.setTexCoords(Vector<float>{0.0f, 1.0f,
                                       1.0f, 1.0f,
                                       0.0f, 0.0f,
                                       1.0f, 0.0f
                                      }
                        );

   m_objectsData["Cube"] = cubeData;
   m_objectsData["Quad"] = quadData;
}

void DemoLayer::initUserLayer()
{
   // [ Layer should not set the clear color manually ]

   Ellipse::RenderModule& renderer = static_cast<Ellipse::RenderModule&>(m_engine.getModule("RenderModule"));
   Pair<i32_t, i32_t> size = Ellipse::Application::get().getWindow().getWindowSize();
   renderer.setViewport(Ellipse::Viewspace{0,
                                           0,
                                           size.first,
                                           size.second
                                          }
                       );


   Ellipse::RenderObjData cube = m_objectsData["Cube"];

   m_light.init(m_modelList, "LightCube", "Assets/Shader/Light.vert.glsl", "Assets/Shader/Light.frag.glsl", cube);

   m_light.setPosition(m_modelList, Vec3{1.0f, 2.0f, 1.0f});

   m_modelList.addModelDefinition("Cube1",
                                  "Cube",
                                  "Assets/Shader/Triangle.vert.glsl",
                                  "Assets/Shader/Triangle.frag.glsl",
                                  m_renderModule.camera(),
                                  m_light.light(),
                                  cube
                                 );

   // m_modelList.addModelDefinition("1", "Cube", "Assets/Shader/Triangle.vert.glsl", "Assets/Shader/Triangle.frag.glsl", m_renderModule.camera(), m_light.light());

   // m_modelList.model("1").setRotateAmount(Ellipse::EllipseMath::Radian{90.0f}.radians(), Vec3{1.0f, 1.0f, 0.0f});

   m_cubeMadeCube.init();


   Ellipse::RenderObjData quad = m_objectsData["Quad"];
   m_modelList.addModelDefinition("Quad1",
                                  "Quad",
                                  "Assets/Shader/Quad.vert.glsl",
                                  "Assets/Shader/Quad.frag.glsl",
                                  quad
                                  );
    m_modelList.model("Cube1").setTranslateAmount(Vec3{-1.0f, 0.0f, 0.0f});

   // m_modelList.addModel("Quad");
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
    // ELLIPSE_APP_LOG_INFO("{}", m_timeModule.secAndNSec())
    m_modelList.model("Cube1").setRotateAmount(Ellipse::EllipseMath::Radian{static_cast<float>(m_timeModule.secAndNSec() * 16)}.radians(),
                                           Vec3{1.0f, 0.0f, 0.0f}
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
    // float radiansRotated = Ellipse::EllipseMath::Radian{static_cast<float>(m_timeModule.secAndNSec())}.radians();
    float radiansRotated = Ellipse::EllipseMath::Radian{static_cast<float>(time)}.radians();

    // ELLIPSE_APP_LOG_INFO("time value {}", time);

    Mat3 xAxisMatrix{1.0f};

    xAxisMatrix[1][1] = cos(radiansRotated);
    xAxisMatrix[1][2] = sin(radiansRotated);
    xAxisMatrix[2][1] = -sin(radiansRotated);
    xAxisMatrix[2][2] = cos(radiansRotated);

    position = position * xAxisMatrix;

    Mat3 yAxisMatrix{1.0f};

    yAxisMatrix[0][0] = cos(radiansRotated);
    yAxisMatrix[0][2] = sin(radiansRotated);
    yAxisMatrix[2][0] = -sin(radiansRotated);
    yAxisMatrix[2][2] = cos(radiansRotated);

    position = position * yAxisMatrix;

    Mat3 zAxisMatrix{1.0f};

    // zAxisMatrix[0][0] = cos(radiansRotated);
    // zAxisMatrix[0][1] = sin(radiansRotated);
    // zAxisMatrix[1][0] = -sin(radiansRotated);
    // zAxisMatrix[1][1] = cos(radiansRotated);

    position = position * zAxisMatrix;

    pixel.setPosition(position); 
    }
                             );

    // m_player->onUpdate(dt);

    // RenderData data = m_renderModule.getRenderData();
}

bool DemoLayer::onKeyPressed(Ellipse::KeyboardPressedEvent& e)
{
     bool aPressed = Ellipse::Input::isKeyPressed(ELLIPSE_KEY_a);
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
  
    // m_modelList.addModel();
    // m_modelList.model(Ellipse::format("{}", m_modelList.models().size() - 1).c_str()).setTranslateAmount(m_renderModule.camera().position() + (Ellipse::EllipseMath::normalize(m_renderModule.camera().front())) * 2.0f);
    
    m_weapon.fire();
  

    return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(Ellipse::MouseWheelEvent& e)
{
    // ELLIPSE_APP_LOG_INFO("{}", e.logMouseOffset());

    return m_throughLayer ? false : true;
}
