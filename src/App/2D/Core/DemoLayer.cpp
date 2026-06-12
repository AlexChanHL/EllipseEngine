
#include "Ellipse.hpp"

#include "DemoLayer.hpp"


DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))},
   m_fontModule{static_cast<Ellipse::FontModule&>(engine.getModule("FontModule"))},
   m_entitySystem{static_cast<Ellipse::EntitySystem&>(engine.getSystem("Entity"))},
   m_objects{m_renderModule.preDefinedObjects()},
   m_cursor{-0.9f, 0.9f},
   m_colorKey{0.0f, 0.0f, 0.0f}
{
   m_throughLayer = false;
}

void DemoLayer::init() {
    Ellipse::RenderModule& renderer = static_cast<Ellipse::RenderModule&>(m_engine.getModule("RenderModule"));
    Pair<i32_t, i32_t> size = Ellipse::Application::get().getWindow().getWindowSize();
    renderer.setViewport(0, 0, size.first, size.second);


    auto quad = Ellipse::RenderEntity(m_engine);
    quad.onInit();
    // std::cout << quad.renderModule() << '\n';
    m_entitySystem.addEntity<Ellipse::RenderEntity>(quad);

    auto r = static_cast<Ellipse::RenderEntity&>(m_entitySystem.findEntity(1));
    // std::cout << r.componentAmount() << "\n";

    // auto rComp = quad.findComponent<Ellipse::RenderComponent>();
    // Ellipse::EllipseMath::translate(rComp.model(), Ellipse::EllipseMath::Vec2(0, 0));
  
    // m_renderModule.render(m_entitySystem.getFromID(id, "Render"));
  

    // void PlayerEntity::move() {
    //   m_components['render'].setMat(m_components['player'].pos());
    // }
    //
  //
  //
    // m_modelList.defineObject("FontSheet", "Assets/Fonts/Font.png", m_objects["Quad"]);
    // m_modelList.defineObject("Message", "Assets/Images/Message.png", m_objects["Quad"]);
    // m_modelList.defineObject("Solar", "Assets/Images/Solar.jpeg", m_objects["Quad"]);
    // m_modelList.defineObject("Space", "Assets/Images/Space.jpeg", m_objects["Quad"]);
    // Ellipse::FontCollection times = m_fontModule.getFont("TimesNewRoman");
    // Ellipse::TextureData tex = Ellipse::loadTexture(times.sheetPath(), false);
    // Ellipse::addGlyphs(times.glyphs(),
    //                    m_objects["Quad"],
    //                    tex,
    //                    m_modelList.addModelDefinitionCallBack(),
    //                    "Assets/Shader/Quad.vert.glsl",
    //                    "Assets/Shader/Quad.frag.glsl"
    // );
    // Ellipse::freeTexture(tex);

    // Ellipse::Entity quad = Ellipse::RenderEntity("Cube1");
    // quad->setObject("Object");
    // m_renderModule->defineObject();

    // Ellipse::RenderComponent rComp = Ellipse::RenderComponent{};
    // quad.addComponent<Ellipse::RenderComponent>(rComp);
    // m_modelManagerLayerModule.defineObject("FontSheet", "Assets/Fonts/Font.png", m_objects["Quad"]);
    // m_modelManagerLayerModule.createRenderModel(quad.findComponent("Model"), "FontSheet");
  

    // auto rand = [](){ return Ellipse::EllipseMath::randRealDist(-1.0f,1.0f); };
    // m_modelList.addModel("Font1", "FontSheet", Vec2{rand(), rand()});
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

void DemoLayer::onUpdate(float dt) {
    auto r = static_cast<Ellipse::RenderEntity&>(m_entitySystem.findEntity(1));
    static_cast<Ellipse::RenderEntity&>(m_entitySystem.findEntity(1)).render();
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
     case ELLIPSE_KEY_a: {
      bool isNameFound = false;
      String randomName;
      while(!isNameFound) {
       randomName = Ellipse::Utils::generateRandomString(6);
       for(u64_t j=0;j<m_names.size();j++) {
        if(randomName == m_names[j]) {
         break;
        }
       }
       isNameFound = true;
      }
      m_names.push_back(randomName);

      if(m_cursor.x >= 0.9f) {
       m_cursor = EllipseMath::Vec2(-1.0f, m_cursor.y - 0.1f);
      }

      m_cursor += EllipseMath::Vec2(0.1f, 0.0f);
     }
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
