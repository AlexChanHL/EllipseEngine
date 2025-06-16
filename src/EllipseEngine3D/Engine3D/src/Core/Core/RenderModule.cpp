
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

   // [ Remove this ]
   setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});

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

   m_proj = EllipseMath::perspective(EllipseMath::Radian(45.0f).radians(),
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

void RenderModule3D::setViewport(Viewspace viewspace)
{
   // [ Casting causes the lost of precision 
   //    in viewspace saved position ]
   m_renderer.setViewport(static_cast<i32_t>(viewspace.m_posX),
                          static_cast<i32_t>(viewspace.m_posY),
                          static_cast<i32_t>(viewspace.m_width),
                          static_cast<i32_t>(viewspace.m_height)
                         );
}

// void RenderModule3D::renderModels()
// {
//     for(u64_t i=0;i<m_modelManager.models().size();i++)
//     {
//     const Model& renderModelModel = m_modelManager.models()[i];
//     if(renderModelModel.renderObject() != nullptr)
//     {
//     renderModel(renderModelModel.renderObject(), renderModelModel.shaderObject(), renderModelModel.uniformList());
//     }
//
//     }
//
// }

void RenderModule3D::render(RenderObj* renderObj,
                            RenderShaderObj* shaderObj,
                            const UniformList& uniformList)
{
    m_renderer.render(*renderObj, *shaderObj, uniformList);
    // UniformList a = uniformList; 
    // a.getMat4UniformFromListByName("model").printUniforms(); 
}

}       // namespace Ellipse

// }       // namespace Ellipse3D


SharedPtr<Ellipse::RenderModule> Ellipse::RenderModule::createRenderModule(Ellipse::Engine& engine)
{
  	return createShared<Ellipse::RenderModule3D>(engine);
}

