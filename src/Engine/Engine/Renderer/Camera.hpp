#pragma once


namespace Ellipse {
 class Camera {
    public:
     Camera()
     : m_name{nullptr},
       m_id{-1},
       m_yaw{0},
       m_pitch{0},
       m_roll{0},
       m_cameraSpeed{0.025f},
       m_sensitivity{0.25f},
       m_position{EllipseMath::Vec3{0.0f, 0.0f, 3.0f}},
       m_front{EllipseMath::Vec3{0.0f, 0.0f, -1.0f}},
       m_upDirection{EllipseMath::Vec3{0.0f, 1.0f, 0.0f}} {
 
     }
     Camera(const char* name)
     : m_name{name},
       m_id{-1},
       m_yaw{0},
       m_pitch{0},
       m_roll{0},
       m_cameraSpeed{0.025f},
       m_sensitivity{0.25f},
       m_position{EllipseMath::Vec3{0.0f, 0.0f, 1.0f}},
       m_front{EllipseMath::Vec3{1.0f, 1.0f, 1.0f}},
       m_upDirection{EllipseMath::Vec3{1.0f, 1.0f, 1.0f}} {
      m_front = EllipseMath::Vec3{0.0f, 0.0f, -1.0f};
      m_upDirection = EllipseMath::Vec3{0.0f, 1.0f, 0.0f};
     }
     ~Camera() {
     }
 
     void registerMouseUpdate(Pair<float, float> mouseOffsets) {
      setCameraYawValues(mouseOffsets);
      setCameraFront();
     }
 
     void setCameraYawValues(Pair<float, float> mouseOffsets) {
      float offsetX = mouseOffsets.first * m_sensitivity;
      float offsetY = -mouseOffsets.second * m_sensitivity;
      // 80 = 320 * 0.25f
      // ELLIPSE_ENGINE_LOG_INFO("Offset x: {} Offset y: {}", offsetX, offsetY);
      m_yaw += offsetX;
      if((m_pitch + offsetY  <= 90.0f) && (m_pitch + offsetY >= -90.0f)) {
       m_pitch += offsetY;
      }
      // ELLIPSE_ENGINE_LOG_INFO("Pitch: {} Yaw: {}", m_yaw, m_pitch);
      // ELLIPSE_ENGINE_LOG_INFO("Offset x: {} Offset y: {}", offsetX, offsetY);
     }
 
     // [ Whenever user sets relative mouse mode off and refocuses
     //   the window will use the new position and calculate a large offset ]
     void setCameraFront() {
      EllipseMath::Vec3 cameraDirection = EllipseMath::Vec3{1.0f};
      float yawRadians = EllipseMath::radians(m_yaw);
      float pitchRadians = EllipseMath::radians(m_pitch);
      cameraDirection.x = static_cast<float>(sin(yawRadians) * cos(pitchRadians));
      cameraDirection.y = static_cast<float>(sin(pitchRadians));
      cameraDirection.z = static_cast<float>(-cos(yawRadians) * cos(pitchRadians));
      m_front = EllipseMath::normalize(cameraDirection);
     }
 
     void setCameraSpeed(float cameraSpeed) { m_cameraSpeed = cameraSpeed; }
     void setPosition(EllipseMath::Vec3 position) { m_position = position; }
     void setFront(EllipseMath::Vec3 front) { m_front = front; }
     float cameraSpeed() const { return m_cameraSpeed; }
     EllipseMath::Vec3 position() const { return m_position; }
     EllipseMath::Vec3& position() { return m_position; }
     EllipseMath::Vec3 front() const { return m_front; }
     EllipseMath::Vec3 upDirection() const { return m_upDirection; }
     const char* name() const { return m_name; }
 
    private:
     const char* m_name;
     i64_t m_id;
     float m_yaw;
     float m_pitch;
     float m_roll;
     float m_cameraSpeed;
     float m_sensitivity;
     EllipseMath::Vec3 m_position;
     EllipseMath::Vec3 m_front;
     EllipseMath::Vec3 m_upDirection;
 };

}

