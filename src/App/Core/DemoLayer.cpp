
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_modelManagerLayerModule{static_cast<Ellipse::ModelManagerModule&>(engine.getLayerModule("ModelManagerLayerModule"))}
{
   m_name = "Placeholder";
   m_throughLayer = false;
}

void DemoLayer::initUserLayer()
{
   // [ Layer should not set the clear color manually ]

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


   m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{0,
    0,
    Ellipse::Application::get().getWindow().getWindowSize().first / 2,
    Ellipse::Application::get().getWindow().getWindowSize().second});


   // m_modelManagerLayerModule.setWorld("Main World");
   // [ The camera is added before setting the viewspace ] 
   // m_modelManagerLayerModule.setViewspace("Camera1");
   // m_modelManagerLayerModule.setViewspace(0.25, 1.0, 0, 0);
  
   // m_modelManagerLayerModule.setWorld("Main World");
   // m_modelManagerLayerModule.setWorld("Camera1 World");
   // m_modelManagerLayerModule.setViewspace("Camera1");

   // m_modelManagerLayerModule.addModel(m_entities[0],
   //                                    "Model", 
   //                                    "Assets/Shader/Triangle.vert.glsl",
   //                                    "Assets/Shader/Triangle.frag.glsl",
   //                                    verticiesData,
   //                                    uniformList
   //                                    );

   for(unsigned long i=0;i<100;i++)
   {
   m_entities.push_back(Ellipse::ModelID{});
   }

   m_modelManagerLayerModule.addModel(m_entities[0],
                                      "Model", 
                                      "Assets/Shader/Triangle.vert.glsl",
                                      "Assets/Shader/Triangle.frag.glsl",
                                      verticiesData,
                                      uniformList
                                      );

   // m_modelManagerLayerModule.translateModel(m_entities[0], Vec3{0.5f, 0.0f, 0.0f});
   // m_modelManagerLayerModule.rotateModel(m_entities[0], float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});
   // m_modelManagerLayerModule.removeModel(m_entities[0]);
  

   m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{
    Ellipse::Application::get().getWindow().getWindowSize().first / 2,
    0,
    Ellipse::Application::get().getWindow().getWindowSize().first / 2,
    Ellipse::Application::get().getWindow().getWindowSize().second});

   m_modelManagerLayerModule.addModel(m_entities[1],
                                      "Model1", 
                                      "Assets/Shader/Triangle.vert.glsl",
                                      "Assets/Shader/Triangle.frag.glsl",
                                      verticiesData,
                                      uniformList
                                      );
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
   // // m_modelManagerLayerModule.setViewspace(Ellipse::Viewspace{125,3262,314,153});
   //
   // m_modelManagerLayerModule.addModel(m_entities[3],
   //                                    "Model3", 
   //                                    "Assets/Shader/Triangle.vert.glsl",
   //                                    "Assets/Shader/Triangle.frag.glsl",
   //                                    verticiesData,
   //                                    uniformList
   //                                    );
   // m_modelManagerLayerModule.removeModel(m_entities[3]);
   //
   // m_modelManagerLayerModule.addModel(m_entities[4],
   //                                    "Model4", 
   //                                    "Assets/Shader/Triangle.vert.glsl",
   //                                    "Assets/Shader/Triangle.frag.glsl",
   //                                    verticiesData,
   //                                    uniformList
   //                                    );
   // m_modelManagerLayerModule.removeModel(m_entities[4]);
   //
   // m_modelManagerLayerModule.addModel(m_entities[5],
   //                                    "Model5", 
   //                                    "Assets/Shader/Triangle.vert.glsl",
   //                                    "Assets/Shader/Triangle.frag.glsl",
   //                                    verticiesData,
   //                                    uniformList
   //                                    );
   // m_modelManagerLayerModule.removeModel(m_entities[5]);

   // m_modelManagerLayerModule.removeModel(m_entities[1]);
  
   // m_modelManagerLayerModule.removeModel(m_entities[1]);
   
   // EntityRef entityRef = addModel("Model",
   //                               "Assets/Shader/Triangle.vert.glsl",
   //                               "Assets/Shader/Triangle.frag.glsl",
   //                               verticiesData,
   //                               uniformList
   //                               );
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
   // m_entities.push_back(addModel("Model",
   //                               "Assets/Shader/Triangle.vert.glsl",
   //                               "Assets/Shader/Triangle.frag.glsl",
   //                               verticiesData,
   //                               uniformList
   //                               )
   //                     );
   //
   // for(auto entity : m_entities)
   // {
   // scaleModel(entity, Vec3{0.5f, 0.5f, 0.5f});
   // }

   // float pos = 0;
   // for(float i=0; i<10;i++)
   // {
   // EntityRef ref = addQuad(Vec3{pos, 0.0f, 0.0f});
   // rotateModel(ref, Radians{45.0f}, Vec3{0.0f, 0.0f, 1.0f});
   // pos += 0.1f;
   // }

   // positionCamera(Vec3{0.0f, 0.0f, 3.0f});

   // m_entity3 = addModel("Model2",
   //                            "Assets/Shader/Triangle.vert.glsl",
   //                            "Assets/Shader/Triangle.frag.glsl",
   //                             verticiesData,
   //                             uniformList
   //                           );

   // positionModel(m_entity4, Vec3{-0.2f, -0.35f, 0.0f});
   // scaleModel(m_entity4, Vec3{0.5f, 0.5f, 0.5f});

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
    // [ Have an specific engine timer so that we can account
    //   for moments when pausing ]
    //
    
    // std::cout << "Window size: " << Ellipse::Application::get().getWindow().getWindowSize().first << '\n';
  
    // m_modelManagerLayerModule.rotateModel(m_entities[0], float(m_timeModule.secAndNSec()), Vec3{0.0f, 0.0f, 1.0f});

    // std::cout << float(m_timeModule.secAndNSec()) << '\n';

    // exit(1);

    // if(m_timeModule.setTimer(m_timer1, 1))
    // {
    // // Logger cannot use info
    // ELPSE_APP_LOG_WARN("One second has passed");
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
     std::cout << "'a' key is pressed" << "\n";
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
     // positionCameraLeft(0.025f);
      break;
     case ELLIPSE_KEY_d:
     // positionCameraRight(0.025f);
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
