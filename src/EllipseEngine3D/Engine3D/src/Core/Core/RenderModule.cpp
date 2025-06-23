
#include "RenderModule.hpp"

// namespace Ellipse3D
// {

namespace Ellipse
{

RenderModule3D::RenderModule3D(Engine& engine)
: m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))},
  m_objectIDGenerator{i32_t(pow(10,3))}
{
   setName("RenderModule");
   setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});

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

   m_objects["Cube"] = cubeData;
   m_objects["Quad"] = quadData;

   m_view = Mat4(1.0f);

   m_view = EllipseMath::lookAt(m_camera.position(),
                                m_camera.position() + m_camera.front(),
                                m_camera.upDirection()
                                );

   m_proj = Mat4{1.0f};

   i32_t winWidth = m_renderer.getWindowFrameSize().first;
   i32_t winHeight = m_renderer.getWindowFrameSize().second;

   float aspectRatio = float(winWidth) / float(winHeight);


   //                              aspectRatio,
   // [ Maybe should set to aspect ratio ]
   // m_proj = EllipseMath::ortho(-1.0f,
   //                              1.0f,
   //                             -1.0f,
   //                              1.0f,
   //                              0.1f,
   //                              100.0f
   //                            );

   m_proj = EllipseMath::perspective(EllipseMath::radians(45.0f),
                                     aspectRatio,
                                     0.1f,
                                     100.0f
                                    );
}

RenderModule3D::~RenderModule3D()
{

}

void RenderModule3D::init()
{
   m_renderer.plugin()->enable(0);
}

void RenderModule3D::onUpdate()
{
    m_view = EllipseMath::lookAt(m_camera.position(),
                                 m_camera.front() + m_camera.position(),
                                 m_camera.upDirection()
                                );
}

void RenderModule3D::setViewCamera(Camera camera)
{
    m_view = EllipseMath::lookAt(camera.position(),
                                 camera.front() + camera.position(),
                                 camera.upDirection()
                                );


    // ELLIPSE_ENGINE_LOG_INFO("{}, {}, {}", camera.position(),
    //                                       camera.front(),
    //                                       camera.upDirection()
    //                        );
}

void RenderModule3D::setCameraFront(float amount)
{
    m_camera.setPosition(m_camera.position() + EllipseMath::normalize(m_camera.front()) * amount);
}
void RenderModule3D::setCameraBackward(float amount)
{
    m_camera.setPosition(m_camera.position() - EllipseMath::normalize(m_camera.front()) * amount);
}
void RenderModule3D::setCameraRight(float amount)
{
    m_camera.setPosition(m_camera.position() - EllipseMath::normalize(EllipseMath::cross(m_camera.upDirection(), m_camera.front())) * amount);
}
void RenderModule3D::setCameraLeft(float amount)
{
    m_camera.setPosition(m_camera.position() + EllipseMath::normalize(EllipseMath::cross(m_camera.upDirection(), m_camera.front())) * amount);
}

void RenderModule3D::setClearColor(Vec4 col)
{
   m_renderer.setClearColor(col);
}

void RenderModule3D::setProjPerspective()
{
   i32_t winWidth = m_renderer.getWindowFrameSize().first;
   i32_t winHeight = m_renderer.getWindowFrameSize().second;

   float aspectRatio = float(winWidth) / float(winHeight);

   m_proj = EllipseMath::perspective(EllipseMath::radians(45.0f),
                                     aspectRatio,
                                     0.1f,
                                     100.0f
                                    );
}
void RenderModule3D::setProjOrtho()
{
    m_proj = EllipseMath::ortho(-1.0f,
                                 1.0f,
                                -1.0f,
                                 1.0f,
                                 0.1f,
                                 100.0f
                               );
}

void RenderModule3D::setViewport(Viewspace viewspace)
{
   m_renderer.setViewport(static_cast<i32_t>(viewspace.m_posX),
                          static_cast<i32_t>(viewspace.m_posY),
                          static_cast<i32_t>(viewspace.m_width),
                          static_cast<i32_t>(viewspace.m_height)
                         );
}

void RenderModule3D::render(RenderObj* renderObj,
                            RenderShaderObj* shaderObj,
                            const UniformList& uniformList)
{
    m_renderer.render(*renderObj, *shaderObj, uniformList);
}

}       // namespace Ellipse

// }       // namespace Ellipse3D


SharedPtr<Ellipse::RenderModule> Ellipse::RenderModule::createRenderModule(Ellipse::Engine& engine)
{
  	return createShared<Ellipse::RenderModule3D>(engine);
}

