
#include "RenderModule.hpp"

// namespace Ellipse3D
// {

namespace Ellipse {
 RenderModule3D::RenderModule3D(Engine& engine)
 : m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))},
   m_objectIDGenerator{i32_t(pow(10,3))} {
    setName("RenderModule");
    setClearColor(EllipseMath::Vec4{1.0f, 1.0f, 0.0f, 1.0f});
 
    Ellipse::RenderObjData cubeData;
    std::vector<std::array<float,3>> points{
     std::array<float,3>{-0.5f,0.5f,0.5f}, 
     std::array<float,3>{-0.5f,-0.5f,0.5f},
     std::array<float,3>{-0.5f,-0.5f,-0.5f},
     std::array<float,3>{-0.5f,0.5f,-0.5f},
     std::array<float,3>{0.5f,0.5f,-0.5f},
     std::array<float,3>{0.5f,-0.5f,-0.5f},
     std::array<float,3>{0.5f,-0.5f,0.5f},
     std::array<float,3>{0.5f,0.5f,0.5f}
    };
    std::vector<float> positions;
    uint32_t current = 0;
    for(uint32_t i=0;i<4;i++) {
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[current][j]);
     }
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[current+1][j]);
     }
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[(current+2)%8][j]);
     }
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[(current+3)%8][j]);
     }
     current += 2;
    }
    current = 0;
    for(uint32_t i=0;i<2;i++) {
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[current][j]);
     }
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[current+3][j]);
     }
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[current+4][j]);
     }
     for(uint32_t j=0;j<3;j++) {
      positions.push_back(points[(current+7) % 8][j]);
     }
     current = 2;
    }
    current = 0;
    std::vector<uint32_t> indicies;
    for(uint32_t i=0;i<6;i++) {
     for(uint32_t j=0;j<2;j++) {
      indicies.push_back(current);
      indicies.push_back(current+(j+1));
      indicies.push_back(current+(j+2));
     }
     current += 4;
    }

    // -x, -z, x, z, y, -y in this order
    float x=-1, y=0, z=0;
    std::vector<float> normals;
    for(uint32_t i=0;i<6;i++) {
     switch(i) {
      case 1: { z=-1; } break;
      case 2: { x=1; } break;
      case 3: { z=1; } break;
      case 4: { y=1; } break;
      case 5: { y=-1; } break;
      default: break;
     }
     for(uint32_t j=0;j<4;j++) {
      normals.push_back(x);
      normals.push_back(y);
      normals.push_back(z);
     }
     x=0, y=0, z=0;
    }
    std::vector<float> texCoords;
    std::vector<float> sides{
     0.0f, 1.0f,
     0.0f, 0.0f,
     1.0f, 0.0f,
     1.0f, 1.0f
    };
    for(uint32_t i=0;i<6;i++) {
     for(uint32_t j=0;j<8;j++) {
      texCoords.push_back(sides[j]);
     }
    }
    cubeData.setIndicies(indicies);
    cubeData.setPositions(positions);
    cubeData.setNormals(normals);
    cubeData.setTexCoords(texCoords);
    cubeData.textureData() = loadTexture("Assets/Images/Solar.jpeg", false);
 
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
    quadData.setTexCoords(Vector<float>{0.0f, 0.0f,
                                        1.0f, 0.0f,
                                        0.0f, 1.0f,
                                        1.0f, 1.0f
                                       }
                         );
    quadData.textureData() = loadTexture("Assets/Images/Solar.jpeg", false);
 
    m_objects["Cube"] = cubeData;
    m_objects["Quad"] = quadData;
 
    m_view = EllipseMath::Mat4(1.0f);
 
    m_view = EllipseMath::lookAt(m_camera.position(),
                                 m_camera.position() + m_camera.front(),
                                 m_camera.upDirection()
                                 );
 
    m_proj = EllipseMath::Mat4{1.0f};
 
    i32_t winWidth = m_renderer.getWindowFrameSize().first;
    i32_t winHeight = m_renderer.getWindowFrameSize().second;
 
    float aspectRatio = float(winWidth) / float(winHeight);
 
    m_proj = EllipseMath::perspective(EllipseMath::radians(45.0f),
                                      aspectRatio,
                                      0.1f,
                                      100.0f
                                     );
 }
 
 RenderModule3D::~RenderModule3D() {
 }
 
 void RenderModule3D::init() {
  m_renderer.plugin()->enable(0);
 }
 
 void RenderModule3D::onUpdate() {
     m_view = EllipseMath::lookAt(m_camera.position(),
                                  m_camera.front() + m_camera.position(),
                                  m_camera.upDirection()
                                 );

     // renderAll();
 }
 
 void RenderModule3D::setViewport(i32_t posX, i32_t posY, i32_t width, i32_t height) {
  m_renderer.setViewport(posX, posY, width, height);
 }
 
 void RenderModule3D::setViewCamera(Camera camera) {
     m_view = EllipseMath::lookAt(camera.position(),
                                  camera.front() + camera.position(),
                                  camera.upDirection()
                                 );
 }
 
 void RenderModule3D::setCameraFront(float amount) {
     m_camera.setPosition(m_camera.position() + EllipseMath::normalize(m_camera.front()) * amount);
     updateView();
 }
 void RenderModule3D::setCameraBackward(float amount) {
     m_camera.setPosition(m_camera.position() - EllipseMath::normalize(m_camera.front()) * amount);
     updateView();
 }
 void RenderModule3D::setCameraRight(float amount) {
     m_camera.setPosition(m_camera.position() - EllipseMath::normalize(EllipseMath::cross(m_camera.upDirection(), m_camera.front())) * amount);
     updateView();
 }
 void RenderModule3D::setCameraLeft(float amount) {
     m_camera.setPosition(m_camera.position() + EllipseMath::normalize(EllipseMath::cross(m_camera.upDirection(), m_camera.front())) * amount);
     updateView();
 }
 
 void RenderModule3D::setClearColor(EllipseMath::Vec4 col) {
    m_renderer.setClearColor(col);
 }
 
 void RenderModule3D::render(RenderObj* renderObj,
                             RenderShaderObj* shaderObj,
                             const UniformList& uniformList) {
     // double precedence = 0;
     // if(m_renderables.contains(id)) {
     //  m_renderables[precedence] = createShared<Renderable>();
    //  }
    
     m_renderer.plugin()->enable(DEPTH_TEST);
     m_renderer.render(*renderObj, *shaderObj, uniformList);
 }
 
 void RenderModule3D::render2D(RenderObj* renderObj,
                               RenderShaderObj* shaderObj,
                               const UniformList& uniformList,
                               EllipseMath::Vec3 translate,
                               EllipseMath::Vec3 rotateAxis,
                               float rotateAngle,
                               EllipseMath::Vec3 scale
                              ) {
     EllipseMath::Mat4 model = EllipseMath::Mat4{1.0f};
     EllipseMath::Vec3 zAxis{0.f, 0.f, -1.0f};
     EllipseMath::Vec3 yAxis{0.f, 1.f,  0.0f};
 
     float yAxisAngle = 0.0f;
     if(m_camera.front().y != 0.0f) {
      yAxisAngle = static_cast<float>(acos(EllipseMath::dot(EllipseMath::Vec3{0.0f, m_camera.front().y, 0.0f}, yAxis)));
      yAxisAngle = EllipseMath::radians(90.0f) - yAxisAngle;
     }
 
     float yRotateAngle = yAxisAngle;
     if(yAxisAngle < 0) {
      yRotateAngle = EllipseMath::radians(360.0f) - yAxisAngle;
     }
 
     EllipseMath::Vec3 cameraFrontAxisOrtho{1.0f};
     EllipseMath::Vec3 cameraAxis{0.0f};
     float zAxisAngle = 0.0f;
     if(m_camera.front().y != 0.0f) {
      cameraFrontAxisOrtho = EllipseMath::cross(m_camera.front(), EllipseMath::Vec3{m_camera.front().x, 0.0f, m_camera.front().z});
      cameraAxis = EllipseMath::rotate(m_camera.front(), yRotateAngle, cameraFrontAxisOrtho);
      zAxisAngle = static_cast<float>(acos(EllipseMath::dot(cameraAxis, zAxis)));
 
      // zAxisAngle = static_cast<float>(acos(EllipseMath::dot(EllipseMath::Vec3{m_camera.front().x, 0.0f, m_camera.front().z}, zAxis)));
     }
     if(m_camera.front().x > 0) {
      zAxisAngle = EllipseMath::radians(360.0f) - zAxisAngle;
     }
     if(yAxisAngle > 0) {
      cameraFrontAxisOrtho *= -1;
     }
     translate = EllipseMath::rotate(translate, yAxisAngle, EllipseMath::Vec3(1.0f, 0.f, 0.f));
     translate = EllipseMath::rotate(translate, zAxisAngle, yAxis);
 
     model = EllipseMath::translate(model, m_camera.position() + m_camera.front() * 2.0f);
     model = EllipseMath::translate(model, translate);
 
     model = EllipseMath::rotate(model, yAxisAngle, cameraFrontAxisOrtho);
     model = EllipseMath::rotate(model, zAxisAngle, yAxis);
     model = EllipseMath::rotate(model, rotateAngle, EllipseMath::Vec3(0.f, 0.0f, 1.f));
 
     model = EllipseMath::scale(model, scale);
     shaderObj->uniformList().setUniform("model", model);
 
     m_renderer.plugin()->disable(DEPTH_TEST);
     m_renderer.render(*renderObj, *shaderObj, uniformList);
     m_renderer.plugin()->enable(DEPTH_TEST);
 }

 void RenderModule3D::render3D(RenderObj* renderObj,
                               RenderShaderObj* shaderObj,
                               const UniformList& uniformList,
                               EllipseMath::Vec3 translate,
                               EllipseMath::Vec3 rotateAxis,
                               float rotateAngle,
                               EllipseMath::Vec3 scale
                              ) {
     EllipseMath::Mat4 model{1.0f};
     model = EllipseMath::translate(model, translate);
     model = EllipseMath::rotate(model, rotateAngle, EllipseMath::Vec3(0.f, 0.0f, 1.f));
     model = EllipseMath::scale(model, scale);
     shaderObj->uniformList().setUniform("model", model);
 
     m_renderer.plugin()->enable(DEPTH_TEST);
     m_renderer.render(*renderObj, *shaderObj, uniformList);
     m_renderer.plugin()->disable(DEPTH_TEST);
 }

 // void RenderModule3D::render(RenderObj* renderObj,
 //                             RenderShaderObj* shaderObj,
 //                             const UniformList& uniformList,
 //                             double precedence) {
 //  // u64_t id = randIntDist(0, 10000);
 //  // m_renderables[id] =createShared<Renderable>(id,renderObj, shaderObj);
 //  // m_renderablesInPrecedence.push_back(id, precedence);
 // }

}       // namespace Ellipse
// }       // namespace Ellipse3D

SharedPtr<Ellipse::RenderModule> Ellipse::RenderModule::createRenderModule(Ellipse::Engine& engine) {
  	return createShared<Ellipse::RenderModule3D>(engine);
}

