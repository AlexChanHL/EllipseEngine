
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_modelManagerLayerModule{static_cast<Ellipse::ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))},
   m_modelIncrement{0},
   m_rotatedDegrees{0.0f}
{
   m_name = "Placeholder";
   m_throughLayer = false;
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
   m_modelManagerLayerModule.addUserSubWorld("SubWorld", "UserWorld");

   m_modelManagerLayerModule.addUserWorld("Main World", "UserWorld1");
   m_modelManagerLayerModule.addUserSubWorld("SubWorld1", "UserWorld1");


   Vector<float> verticies = 
   {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f,
   };

   // [ Make VerticiesData copy constructor ]
   Ellipse::VerticiesData verticiesData{3, verticies.size(), verticies};


   m_offset = 0.0f;
  
   Ellipse::UniformList uniformList;
   uniformList.addUniform(Ellipse::UniformVarible<float>{"offset", &m_offset});

   ELLIPSE_APP_LOG_INFO("uniform item");
   ELLIPSE_APP_LOG_INFO("uniform item");

   // m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{0,
   //  0,
   //  Ellipse::Application::get().getWindow().getWindowSize().first / 2,
   //  Ellipse::Application::get().getWindow().getWindowSize().second}); 


   // [ Adding models will create models with the same name ]
   auto addModelIndex  = [&](u32_t index)
   {
   m_modelManagerLayerModule.addModel(m_entities[index],
                                      "Model", 
                                      "Assets/Shader/Triangle.vert.glsl",
                                      "Assets/Shader/Triangle.frag.glsl",
                                      verticiesData,
                                      uniformList
                                      );

   };

   auto removeModelIndex = [&](u32_t modelIndex)
   {
   m_modelManagerLayerModule.removeModel(m_entities[modelIndex]);
   };

   auto translateModelIndex = [&](u32_t index, Vec3 translateAmount)
   {
   m_modelManagerLayerModule.translateModel(m_entities[index], translateAmount);
   };

   auto  rotateModelIndex = [&](u32_t index, float radians, Vec3 rotationAxis)
   {
   m_modelManagerLayerModule.rotateModel(m_entities[index], radians, rotationAxis);
   };

   auto scaleModelIndex = [&](u32_t index, Vec3 scalarAmount)
   {
   m_modelManagerLayerModule.scaleModel(m_entities[index], scalarAmount);
   };

   for(unsigned long i=0;i<100;i++)
   {
   m_entities.push_back(Ellipse::ModelID{});
   }

   m_modelManagerLayerModule.startWorld("Main World");

   addModelIndex(0);

   // addModelFunc();
   // m_modelManagerLayerModule.translateModel(m_entities[0], Vec3{0.5f, 0.0f, 0.0f});
   // removeModelLast();
   // addModelFunc();
   // translateModelLast(Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
   // removeModelLast();

   // m_modelManagerLayerModule.removeModel(m_entities[0]);
  
   // m_modelManagerLayerModule.hideAllModels("UserWorld1");
   // m_modelManagerLayerModule.startSubWorld("SubWorld");

   // m_modelManagerLayerModule.setWireFrameModel(m_entities[0], "UserWorld1");

   // addModelFunc();
   // removeModelLast();
   
   // m_modelManagerLayerModule.endSubWorld();
   m_modelManagerLayerModule.startSubWorld("SubWorld1");


   // addModelFunc();
   // addModelFunc();
   // translateModelLast(Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
   // translateModelLast(Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
   // removeModelLast();
   // removeModelLast();
   // 
   m_modelManagerLayerModule.endSubWorld();
   //
   m_modelManagerLayerModule.startSubWorld("SubWorld");
  
   // m_modelManagerLayerModule.setWireFrameModel(m_entities[0], "UserWorld1");





   // addModelFunc();
   // removeModelLast();
   
   m_modelManagerLayerModule.endSubWorld();

   // addModelFunc();
   // rotateModelLast(float(55.0f), Vec3{0.0f, 0.0f, 1.0f});
   // scaleModelLast(Vec3{1.0f, 0.25f, 0.0f});
   // addModelFunc();
   // addModelFunc();
   // addModelFunc();
   // addModelFunc();
   // addModelFunc();

   // removeModelIndex(0);
   // removeModelLast();
   // removeModelLast();

   // m_modelManagerLayerModule.queryUserWorld("UserWorld");
   // m_modelManagerLayerModule.queryUserWorld("UserWorld1");
   // exit(1);

   m_modelManagerLayerModule.startSubWorld("SubWorld1");

   // addModelFunc();
   // addModelFunc();

   m_modelManagerLayerModule.endSubWorld();

   m_modelManagerLayerModule.endWorld();
  
   // This camera will have a different position in the world
   // m_modelManagerLayerModule.setSubWorld("Camera 2");

   // m_modelManagerLayerModule.removeModel(m_entities[1]);

   // m_modelManagerLayerModule.translateModel(m_entities[0], Vec3{0.5f, 0.0f, 0.0f});
   // m_modelManagerLayerModule.rotateModel(m_entities[0], float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
   // m_modelManagerLayerModule.removeModel(m_entities[0]);
  

   // m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{
   //  Ellipse::Application::get().getWindow().getWindowSize().first / 2,
   //  0,
   //  Ellipse::Application::get().getWindow().getWindowSize().first / 2,
   //  Ellipse::Application::get().getWindow().getWindowSize().second});
   //
   // m_modelManagerLayerModule.addModel(m_entities[1],
   //                                    "Model1", 
   //                                    "Assets/Shader/Triangle.vert.glsl",
   //                                    "Assets/Shader/Triangle.frag.glsl",
   //                                    verticiesData,
   //                                    uniformList
   //                                    );
   // m_modelManagerLayerModule.removeModel(m_entities[1]);

   //
   // m_modelManagerLayerModule.addModel(m_entities[2],
   //                                    "Model2", 
   //                                    "Assets/Shader/Triangle.vert.glsl",
   //                                    "Assets/Shader/Triangle.frag.glsl",
   //                                    verticiesData,
   //                                    uniformList
   //                                    );
   // m_modelManagerLayerModule.removeModel(m_entities[2]);
   //
   // rotateModel(entityRef, Radians{45.0f}, Vec3{0.0f, 0.0f, 1.0f});
   // positionModel(entityRef, Vec3{1.0f, 0.25f, 0.0f});
   // scaleModel(entityRef, Vec3{0.5f, 0.5f, 0.5f});
   
   // [ Have a model manager do all this work ]

   // for(u32_t i = 0; i < 10; i++)
   // {
   // m_entities.push_back(addQuad(Vec3{-0.25f, 0.4f, 0.0f}));
   // }
   // for(u32_t i = 0; i < 10; i++)
   // {
   // positionModel(m_entities[i], Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
   // }
   //
   // float pos = 0;
   // for(float i=0; i<10;i++)
   // {
   // EntityRef ref = addQuad(Vec3{pos, 0.0f, 0.0f});
   // rotateModel(ref, Radians{45.0f}, Vec3{0.0f, 0.0f, 1.0f});
   // pos += 0.1f;
   // }

   // positionCamera(Vec3{0.0f, 0.0f, 3.0f});

   // removeModel(Model);
   // removeModel("Model", 0);
   // 
   // addModel("DetailedModel");
   //
   // getModel("Model", 0);
}

void DemoLayer::onEvent(Event& e)
{

    EventDispatcher dispatcher(e);
    dispatcher.dispatchEvent<KeyboardPressedEvent>(
    KEYBOARD_PRESSED_EVENT,  
    BIND_EVENT_FN(onKeyPressed)
    );
    dispatcher.dispatchEvent<MouseMotionEvent>(
    MOUSE_MOTION_EVENT,
    BIND_EVENT_FN(onMouseMotion)
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

void DemoLayer::onUpdateUserLayer(float dt)
{
    Vector<float> verticies = 
    {
     0.0f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
    };

    // [ Make VerticiesData copy constructor ]
    Ellipse::VerticiesData verticiesData{3, verticies.size(), verticies};
    m_offset = 0.0f;
    
    Ellipse::UniformList uniformList;
    uniformList.addUniform(Ellipse::UniformVarible<float>{"offset", &m_offset});
    u32_t modelDecrementAmount = 1;


    // [ Adding models will create models with the same name ]
    auto addModelIndex = [&](u32_t index)
    {
    if(m_modelIncrement >= 100)
    {
    return;
    }

    m_modelManagerLayerModule.addModel(m_entities[index],
                                       "Model", 
                                       "Assets/Shader/Triangle.vert.glsl",
                                       "Assets/Shader/Triangle.frag.glsl",
                                       verticiesData,
                                       uniformList
                                       );

    
    };

    auto removeModelIndex = [&](u32_t modelIndex)
    {
    m_modelManagerLayerModule.removeModel(m_entities[modelIndex]);
    };

    auto translateModelIndex = [&](u32_t index, Vec3 translateAmount)
    {
    m_modelManagerLayerModule.translateModel(m_entities[index], translateAmount);
    };

    auto rotateModelIndex = [&](u32_t index, float radians, Vec3 rotationAxis)
    {
    m_modelManagerLayerModule.rotateModel(m_entities[index], radians, rotationAxis);
    };

    auto scaleModelIndex = [&](u32_t index, Vec3 scalarAmount)
    {
    m_modelManagerLayerModule.scaleModel(m_entities[index], scalarAmount);
    };
    // [ Have an specific engine timer so that we can account
    //   for moments when pausing ]
    //
    
    // std::cout << "Window size: " << Ellipse::Application::get().getWindow().getWindowSize().first << '\n';
  
    // m_modelManagerLayerModule.rotateModel(m_entities[0], float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});

    // std::cout << float(m_timeModule.secAndNSec()) << '\n';
  
    m_modelManagerLayerModule.startWorld("Main World");

    // ELLIPSE_APP_LOG_INFO("world manager");
    m_modelManagerLayerModule.queryUserWorld("UserWorld");

    m_modelManagerLayerModule.rotateModel(m_entities[0], Ellipse::EllipseMath::Radian(m_rotatedDegrees).radians(), Vec3{0.0f, 0.0f, 1.0f});

    m_modelManagerLayerModule.endWorld();


    m_modelManagerLayerModule.startWorld("Main World");

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
    // m_modelManagerLayerModule.rotateModel(m_entities[0], float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
    // addModelFunc();
    // addModelFunc();
    // addModelFunc();
    // m_modelManagerLayerModule.queryUserWorld("UserWorld");
    // exit(1);
    // m_modelManagerLayerModule.translateModel(m_entities[0], Vec3{0.5f, 0.0f, 0.0f});
    // removeModelLast();

    m_modelManagerLayerModule.startSubWorld("SubWorld1");


    // addModelFunc();
    // translateModelLast(Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
    // translateModelLast(Vec3{EllipseMath::randRealDist(-1.0, 1.0), EllipseMath::randRealDist(-1.0, 1.0), 0.0f});
    // removeModelLast();

    m_modelManagerLayerModule.endSubWorld();

    m_modelManagerLayerModule.startSubWorld("SubWorld");
   
    // m_modelManagerLayerModule.setWireFrameModel(m_entities[0], "UserWorld1");
    // translateModelIndex(2, Vec3{-0.5f, 0.5f, 0.0f});
    // rotateModelIndex(2, Ellipse::EllipseMath::Radian(45.0f).radians(), Vec3{0.0f, 0.0f, 1.0f});

    m_modelManagerLayerModule.endSubWorld();

    // addModelFunc();
    // rotateModelLast(float(55.0f), Vec3{0.0f, 0.0f, 1.0f});
    // scaleModelLast(Vec3{1.0f, 0.25f, 0.0f});
    // addModelFunc();

    // removeModelLast();

    // m_modelManagerLayerModule.queryUserWorld("UserWorld");
    // m_modelManagerLayerModule.queryUserWorld("UserWorld1");
    // exit(1);

    m_modelManagerLayerModule.startSubWorld("SubWorld1");

    // addModelFunc();
    // addModelFunc();

    m_modelManagerLayerModule.endSubWorld();

    m_modelManagerLayerModule.endWorld();
    // exit(1);

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

bool DemoLayer::onKeyPressed(KeyboardPressedEvent& e)
{
     bool aPressed = Input::isKeyPressed(ELLIPSE_KEY_a);
     if(aPressed)
     {
     ELLIPSE_APP_LOG_INFO("'a' key is pressed");
     }

     switch(e.keyCode())
     {
     case ELLIPSE_KEY_w:
     // positionCameraUp(0.025f);
      break;
     case ELLIPSE_KEY_s:
     // positionCameraDown(0.025f);
      break;
     case ELLIPSE_KEY_a:
     m_rotatedDegrees += 0.75f;
      break;
     case ELLIPSE_KEY_d:
     m_rotatedDegrees -= 0.75f;
      break;
     case ELLIPSE_KEY_p:
     // m_timeModule.pause();
      break;
     case ELLIPSE_KEY_o:
     // m_timeModule.unPause();
      break;
     default:
      break;
     }

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseMotion(MouseMotionEvent& e)
{
   e.logMousePosition();

   // std::cout << e.mousePositions().first / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().first) * 2.0f - 1.0f << '\n';
   // std::cout << -1.0f * (e.mousePositions().second / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().second) * 2.0f - 1.0f) << '\n';

   float xPos =  e.mousePositions().first / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().first) * 2.0f - 1.0f;
   float yPos = -1.0f * (e.mousePositions().second / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().second) * 2.0f - 1.0f);

   m_modelManagerLayerModule.startWorld("Main World");

   m_modelManagerLayerModule.translateModel(m_entities[0], Vec3{xPos, yPos, 0.0f});

   m_modelManagerLayerModule.endWorld();

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(MousePressedEvent& e)
{
   // std::cout << e.logMousePosition() << "\n";
   std::cout << m_name <<  " detected mouse press!\n";
   std::cout << m_name <<  " Pos: : " << e.mousePosY() << "\n";

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(MouseWheelEvent& e)
{
  std::cout << e.logMouseOffset() << "\n";

   return m_throughLayer ? false : true;
}
