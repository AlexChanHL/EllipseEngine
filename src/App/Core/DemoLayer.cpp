
#include "Ellipse.hpp"

#include "DemoLayer.hpp"

DemoLayer::DemoLayer(Engine& engine)
: Layer{engine}
{
   m_name = "Placeholder";
   m_throughLayer = false;
}

void DemoLayer::init()
{
   // Layer should not set the clear color manually
   setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});

   Vector<float> verticies = 
   {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f,
   };

   Ellipse::VerticiesData verticiesData{3, verticies.size(), verticies};


   m_offset = 0.0f;
  
   Ellipse::UniformList uniformList;
   uniformList.addUniform(Ellipse::UniformVarible<float>{"offset", &m_offset});
   
   EntityRef entityRef = addModel("Model",
                                 "Assets/Shader/Triangle.vert.glsl",
                                 "Assets/Shader/Triangle.frag.glsl",
                                 verticiesData,
                                 uniformList
                                 );
   
   rotateModel(entityRef, Radians{45.0f}, Vec3{0.0f, 0.0f, 1.0f});
   positionModel(entityRef, Vec3{1.0f, 0.25f, 0.0f});
   scaleModel(entityRef, Vec3{0.5f, 0.5f, 0.5f});

   // [ Have a model manager do all this work ]

   addQuad(Vec3{-0.25f, 0.4f, 0.0f});

   // positionCamera(Vec3{0.0f, 0.0f, 3.0f});

   // EntityRef entity1 = addModel("Model2",
   //                            "Assets/Shader/Triangle.vert.glsl",
   //                            "Assets/Shader/Triangle.frag.glsl",
   //                             verticiesData,
   //                             uniformList
   //                           );
   //
   // positionModel(entity1, Vec3{0.5f, 0.5f, 0.0f});
   // scaleModel(entity1, Vec3{0.5f, 0.5f, 0.5f});

   // EntityRef entity2 = addModel("Model",
   //                            "Assets/Shader/Triangle.vert.glsl",
   //                            "Assets/Shader/Triangle.frag.glsl",
   //                             verticies,
   //                             uniformList
   //                           );
   //
   // positionModel(entity2, Vec3{-0.2f, 0.45f, 0.0f});
   // scaleModel(entity2, Vec3{0.5f, 0.5f, 0.5f});
   //
   // // EntityRef entity3 = addModel("Model",
   // //                            "Assets/Shader/Triangle.vert.glsl",
   // //                            "Assets/Shader/Triangle.frag.glsl",
   // //                             verticies,
   // //                             uniformList
   // //                           );
   // //
   // // positionModel(entity3, Vec3{0.1f, 0.35f, 0.0f});
   // // scaleModel(entity3, Vec3{0.5f, 0.5f, 0.5f});
   //
   // m_entity3 = addModel("Model",
   //                            "Assets/Shader/Triangle.vert.glsl",
   //                            "Assets/Shader/Triangle.frag.glsl",
   //                             verticies,
   //                             uniformList
   //                           );
   //
   // positionModel(m_entity3, Vec3{0.1f, 0.5f, 0.0f});
   // scaleModel(m_entity3, Vec3{0.5f, 0.5f, 0.5f});
   //
   // m_entity4 = addModel("Model",
   //                            "Assets/Shader/Triangle.vert.glsl",
   //                            "Assets/Shader/Triangle.frag.glsl",
   //                             verticies,
   //                             uniformList
   //                           );
   //
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
    // std::cout << "Updated: " << m_name << "\n";
  
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
        case ELLIPSE_KEY_a:
        positionCameraLeft(0.5f);
        m_offset -= 0.05f;
         break;
        case ELLIPSE_KEY_d:
        positionCameraRight(0.5f);
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
   std::cout << m_name <<  " detected mouse press!\n";
   std::cout << m_name <<  " Pos: : " << e.mousePosY() << "\n";

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(MouseWheelEvent& e)
{
  std::cout << e.logMouseOffset() << "\n";

   return m_throughLayer ? false : true;
}
