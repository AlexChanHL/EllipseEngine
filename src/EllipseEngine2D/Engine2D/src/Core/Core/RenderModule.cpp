
#include "RenderModule.hpp"


namespace Ellipse
{

RenderModule2D::RenderModule2D(Engine& engine)
: m_renderer{static_cast<Renderer&>(engine.getSystem("Renderer"))},
  m_modelManager{static_cast<ModelManagerModule&>(engine.getModule("ModelModule"))}
{
  	m_name = "RenderModule";
}
RenderModule2D::~RenderModule2D()
{

}

void RenderModule2D::init()
{
    m_camera.setPosition(Vec3{0.0f, 0.0f, 1.0f});

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

    setClearColor(Vec4{1.0f, 1.0f, 0.0f, 1.0f});
}

void RenderModule2D::onUpdate()
{
  //   for(u64_t i=0;i<m_modelManager.models().size();i++)
  //   {
  //   const Model& model = m_modelManager.models()[i];
		// renderModel(model.renderObject(), model.shaderObject(), model.uniformList());
  //   }
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

Mat4& RenderModule2D::proj() 
{
    return m_proj;
}
Mat4& RenderModule2D::view() 
{
    return m_view;
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

