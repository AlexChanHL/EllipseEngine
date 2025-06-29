#pragma once

#include "Renderer.hpp"
#include "Core/ModelManagerModule.hpp"
#include "Math/Matrix.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Module.hpp"
#include "Core/Base.hpp"


namespace Ellipse
{

struct RotationAmount
{
    public:
     float m_radians;
     Vec3 m_vec3;
};

class Camera
{
   public:
    Camera()
    : m_name{nullptr},
      m_id{-1},
      m_yaw{0},
      m_pitch{0},
      m_roll{0},
      m_cameraSpeed{0.025f},
      m_sensitivity{0.25f},
      m_position{Vec3{0.0f, 0.0f, 3.0f}},
      m_front{Vec3{0.0f, 0.0f, -1.0f}},
      m_upDirection{Vec3{0.0f, 1.0f, 0.0f}}
    {

    }
    Camera(const char* name)
    : m_name{name},
      m_id{-1},
      m_yaw{0},
      m_pitch{0},
      m_roll{0},
      m_cameraSpeed{0.025f},
      m_sensitivity{0.25f},
      m_position{Vec3{0.0f, 0.0f, 1.0f}},
      m_front{Vec3{1.0f, 1.0f, 1.0f}},
      m_upDirection{Vec3{1.0f, 1.0f, 1.0f}}
    {
      m_front = Vec3{0.0f, 0.0f, -1.0f};
      m_upDirection = Vec3{0.0f, 1.0f, 0.0f};
    }
    ~Camera()
    {

    }

    void registerMouseUpdate(Pair<float, float> mouseOffsets)
    {
    setCameraYawValues(mouseOffsets);
    setCameraFront();
    }

    void setCameraYawValues(Pair<float, float> mouseOffsets)
    {
    float offsetX = mouseOffsets.first * m_sensitivity;
    float offsetY = -mouseOffsets.second * m_sensitivity;
    // 80 = 320 * 0.25f

    // ELLIPSE_ENGINE_LOG_INFO("Offset x: {} Offset y: {}", offsetX, offsetY);

    m_yaw += offsetX;

    if((m_pitch + offsetY  <= 90.0f) && (m_pitch + offsetY >= -90.0f))
    {
    m_pitch += offsetY;
    }

    // ELLIPSE_ENGINE_LOG_INFO("Pitch: {} Yaw: {}", m_yaw, m_pitch);
    // ELLIPSE_ENGINE_LOG_INFO("Offset x: {} Offset y: {}", offsetX, offsetY);

    }

    // [ Whenever user sets relative mouse mode off and refocuses
    //   the window will use the new position and calculate a large offset ]
    void setCameraFront()
    {
    Vec3 cameraDirection = Vec3{1.0f};
      
    float yawRadians = EllipseMath::radians(m_yaw);
    float pitchRadians = EllipseMath::radians(m_pitch);

    cameraDirection.x = static_cast<float>(sin(yawRadians) * cos(pitchRadians));
    cameraDirection.y = static_cast<float>(sin(pitchRadians));
    cameraDirection.z = static_cast<float>(-cos(yawRadians) * cos(pitchRadians));


    m_front = EllipseMath::normalize(cameraDirection);

    }

    void setCameraSpeed(float cameraSpeed)
    {
    m_cameraSpeed = cameraSpeed;
    }

    void setPosition(Vec3 position)
    {
    m_position = position;
    }

    void setFront(Vec3 front)
    {
    m_front = front;
    }

    float cameraSpeed() const
    {
    return m_cameraSpeed;
    }

    Vec3 position() const
    {
    return m_position;
    }

    Vec3& position()
    {
    return m_position;
    }

    Vec3 front() const
    {
    return m_front;
    }

    Vec3 upDirection() const
    {
    return m_upDirection;
    }

    const char* name() const
    {
    return m_name;
    }

   private:
    const char* m_name;
    i64_t m_id;

    float m_yaw;
    float m_pitch;
    float m_roll;

    float m_cameraSpeed;
    float m_sensitivity;

    Vec3 m_position;
    Vec3 m_front;
    Vec3 m_upDirection;
};

class RenderModule : public IModule
{
   public:
    RenderModule()
    {

    }
    virtual ~RenderModule()
    {

    }


    virtual void init() override = 0;
    virtual void onUpdate() override = 0;

    virtual void render(RenderObj* renderObj, RenderShaderObj* shaderObj, const UniformList& uniformList) = 0;
    
    virtual void setViewCamera(Camera camera) = 0;

    virtual void setCameraFront(float amount) = 0;
    virtual void setCameraBackward(float amount) = 0;
    virtual void setCameraRight(float amount) = 0;
    virtual void setCameraLeft(float amount) = 0;
    virtual void updateCamera(Pair<float, float> offsets)
    {
    camera().registerMouseUpdate(offsets);
    updateView();
    }

    virtual void setViewport(Viewspace viewspace) = 0;
    virtual void setClearColor(Vec4 col) = 0;

    void setProjPerspective()
    {
    i32_t winWidth = renderer().getWindowFrameSize().first;
    i32_t winHeight = renderer().getWindowFrameSize().second;
 
    float aspectRatio = float(winWidth) / float(winHeight);
 
    m_proj = EllipseMath::perspective(EllipseMath::radians(45.0f),
                                      aspectRatio,
                                      0.1f,
                                      100.0f
                                     );
    }
    void setProjOrtho()
    {
    m_proj = EllipseMath::ortho(-1.0f,
                                 1.0f,
                                -1.0f,
                                 1.0f,
                                 0.1f,
                                 100.0f
                               );
    }

    virtual Renderer& renderer() = 0;

    virtual Mat4& proj() = 0;
    virtual Mat4& view() = 0;

    virtual Camera& camera() = 0;
    Map<String, RenderObjData>& preDefinedObjects()
    {
    return m_objects;
    }

    static SharedPtr<RenderModule> createRenderModule(Engine& engine);

   protected:
    void updateView()
    {
    m_view = EllipseMath::lookAt(camera().position(),
                                 camera().front() + camera().position(),
                                 camera().upDirection()
                                );
    }
    virtual void configureCameras() = 0;

   protected:
    Mat4 m_proj;
    Mat4 m_view;
    Map<String, RenderObjData> m_objects;
};

}    // namespace Ellipse
