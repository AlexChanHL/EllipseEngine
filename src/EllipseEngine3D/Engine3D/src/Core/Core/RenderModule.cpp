
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
 
     std::cout << "y-angle: " << yAxisAngle << '\n';
     std::cout << "z-angle: " << zAxisAngle  << '\n';
 
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

 void RenderModule3D::render(RenderObj* renderObj,
                             RenderShaderObj* shaderObj,
                             const UniformList& uniformList,
                             double precedence) {
  // u64_t id = randIntDist(0, 10000);
  // m_renderables[id] =createShared<Renderable>(id,renderObj, shaderObj);
  // m_renderablesInPrecedence.push_back(id, precedence);
 }

}       // namespace Ellipse
// }       // namespace Ellipse3D

SharedPtr<Ellipse::RenderModule> Ellipse::RenderModule::createRenderModule(Ellipse::Engine& engine) {
  	return createShared<Ellipse::RenderModule3D>(engine);
}

