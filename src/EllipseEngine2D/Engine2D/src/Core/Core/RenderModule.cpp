
#include "RenderModule.hpp"


namespace Ellipse
{

RenderModule2D::RenderModule2D(Engine& engine)
: m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))},
  m_modelManager{static_cast<ModelManagerModule&>(engine.getModule("ModelModule"))},
  m_camera{Camera{}}
{
    m_name = "RenderModule";
}

RenderModule2D::~RenderModule2D()
{

}

void RenderModule2D::init()
{
    m_view = EllipseMath::lookAt(m_camera.position(),
	   	                 m_camera.position() + m_camera.front(),
                                 m_camera.upDirection()
                                );

    m_proj = EllipseMath::ortho(-1.0f,
                                 1.0f,
                                -1.0f,
                                 1.0f,
                                 0.1f,
                                 100.0f
                               );

    // setProjPerspective();

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

    m_objects["Quad"] = quadData;

    setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});
}

void RenderModule2D::onUpdate()
{

}

void RenderModule2D::render(RenderObj* renderObj,
                            RenderShaderObj* shaderObj,
                            const UniformList& uniformList
                           ) 
{
    m_renderer.render(*renderObj, *shaderObj, uniformList);
}

void RenderModule2D::setViewCamera(Ellipse::Camera camera) 
{

}

void RenderModule2D::setCameraFront(float amount) 
{

}

void RenderModule2D::setCameraBackward(float amount) 
{

}
void RenderModule2D::setCameraRight(float amount) 
{

}
void RenderModule2D::setCameraLeft(float amount) 
{

}

void RenderModule2D::setViewport(Ellipse::Viewspace viewspace) 
{

}
void RenderModule2D::setClearColor(Vec4 col) 
{
    m_renderer.setClearColor(col);
}

Ellipse::Camera& RenderModule2D::camera() 
{
    return m_camera;
}

void RenderModule2D::configureCameras()
{

}

}       // namespace Ellipse


SharedPtr<Ellipse::RenderModule> Ellipse::RenderModule::createRenderModule(Ellipse::Engine& engine)
{
  	return createShared<Ellipse::RenderModule2D>(engine);
}

