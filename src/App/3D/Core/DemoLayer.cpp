
#include "Ellipse.hpp"

#include "DemoLayer.hpp"


DemoLayer::DemoLayer(Ellipse::Engine& engine)
 : Layer{engine},
   m_engine{engine},
   m_timeModule{static_cast<Ellipse::TimeModule&>(engine.getModule("TimeModule"))},
   m_renderModule{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule"))},
   m_entitySystem{static_cast<Ellipse::EntitySystem&>(engine.getSystem("Entity"))},
   m_modelIncrement{0},
   m_rotatedDegrees{0.0f}
   // m_weapon{m_modelList, engine, m_light.light()},
   // m_cubeMadeCube{m_modelList, engine, m_light.light()},
   // m_objects{m_renderModule.preDefinedObjects()}
{
   m_name = "Placeholder";
   m_throughLayer = false;
}

void DemoLayer::init() {
   Ellipse::RenderModule& renderer = static_cast<Ellipse::RenderModule&>(m_engine.getModule("RenderModule"));
   Pair<i32_t, i32_t> size = Ellipse::Application::get().getWindow().getWindowSize();

   auto quad = Ellipse::RenderEntity(m_engine);
   quad.objectName() = "Quad";
   quad.onInit();
   m_entitySystem.addEntity<Ellipse::RenderEntity>(quad);

   auto cube = Ellipse::RenderEntity(m_engine);
   cube.objectName() = "Cube";
   cube.onInit();
   m_entitySystem.addEntity<Ellipse::RenderEntity>(cube);


   // Ellipse::RenderObjData cube = m_objects["Cube"];
   // m_modelList.defineCubeObject("Cube", "Assets/Fonts/Font.png", m_objects["Cube"]);
   // m_modelList.defineLightCubeObject("LightCube", "Assets/Fonts/Font.png", m_objects["Cube"]);
   //
   // m_modelList.addModel("L1 cube", "LightCube", Vec3{0.0f, 0.0f, -1.0f});
   // m_cubeMadeCube.init();
}

void DemoLayer::onEvent(Ellipse::Event& e) {
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
    auto time = double(m_timeModule.secAndNSec());
    EllipseMath::Vec3 pos = EllipseMath::Vec3(cos(time), sin(time), 0.0f);

    auto e = SharedPtr<Ellipse::Entity>();
    e = m_entitySystem.findEntityWithIdx(0);
    if(e->id() != -1) {
     m_entitySystem.findEntity<Ellipse::RenderEntity>(e->id()).render();
    }

    e = m_entitySystem.findEntityWithIdx(1); 
    if(e->id() != -1) {
     Ellipse::RenderComponent& rComp = e->findComponent<Ellipse::RenderComponent>();
     *rComp.model() = Ellipse::EllipseMath::translate(EllipseMath::Mat4(1.0f), pos);

     m_entitySystem.findEntity<Ellipse::RenderEntity>(e->id()).render();
    }

  
    // m_modelList.onUpdate();
    //
    // if((m_weapon.weaponType() == WeaponType::AssaultRifle) && Ellipse::Input::isMousePressed(ELLIPSE_MOUSE_BUTTON_LEFT)) {
    //  m_weapon.fire();
    // }
    //
    // m_weapon.update();
    //
    //
    // m_cubeMadeCube.linearFunc([&](Pixel& pixel) {
    //  Vec3 position = pixel.worldPosition();
    //
    //  double time = m_timeModule.secAndNSec() * 16;
    //  float radiansRotated = Ellipse::EllipseMath::radians(static_cast<float>(time));
    //
    //  position = Ellipse::EllipseMath::rotateXAxis(position, radiansRotated);
    //
    //  Mat3 yAxisMatrix{1.0f};
    //
    //  position = Ellipse::EllipseMath::rotateYAxis(position, radiansRotated);
    //
    //  Mat3 zAxisMatrix{1.0f};
    //  pixel.setPosition(position); 
    // }
    // );
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
     // case ELLIPSE_KEY_1:
     // m_weapon.changeWeaponType(WeaponType::Pistol);
     // break;
     // case ELLIPSE_KEY_2:
     // m_weapon.changeWeaponType(WeaponType::Shotgun);
     // break;
     // case ELLIPSE_KEY_3:
     // m_weapon.changeWeaponType(WeaponType::AssaultRifle);
     // break;
     case ELLIPSE_KEY_9:
     Ellipse::Application::get().getWindow().lockCursorToWindow();
     break;
     case ELLIPSE_KEY_0:
     Ellipse::Application::get().getWindow().unlockCursorToWindow();
     break;
     // case ELLIPSE_KEY_o:
     // // m_timeModule.unPause();
     // break;
     // case ELLIPSE_KEY_i:
     // {
     // String modelName = Ellipse::format("{}", (m_modelList.models().size() - 1));
     // m_modelList.removeModel(modelName.c_str());
     // }
     // break;
     default:
     break;
     }

     return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseMotion(Ellipse::MouseMotionEvent& e) {
   float xPos =  e.mousePositions().first / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().first) * 2.0f - 1.0f;
   float yPos = -1.0f * (e.mousePositions().second / static_cast<float>(Ellipse::Application::get().getWindow().getWindowSize().second) * 2.0f - 1.0f);

   m_renderModule.mouseUpdate(Ellipse::Application::get().getWindow().mouseOffsets());

   return m_throughLayer ? false : true;
}

bool DemoLayer::onMousePressed(Ellipse::MousePressedEvent& e)
{
    // m_weapon.fire();
    return m_throughLayer ? false : true;
}

bool DemoLayer::onMouseWheel(Ellipse::MouseWheelEvent& e)
{
    return m_throughLayer ? false : true;
}
