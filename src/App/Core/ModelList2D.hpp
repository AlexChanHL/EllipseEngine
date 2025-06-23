#pragma once

#include "ModelList.hpp"

#include "Ellipse.hpp"


class ModelList2D : public ModelList
{
    public:
     ModelList2D(Ellipse::Engine& engine)
     : ModelList{engine},
       m_camera{static_cast<Ellipse::RenderModule&>(engine.getModule("RenderModule")).camera()}
     {
     
     }
     
     ~ModelList2D()
     {
     
     }
     
     virtual void onUpdate() override
     {
         // m_renderModule.setProjOrtho();
         setToCameraFront();

         // addAmounts();

         for(Pair<String, u64_t> index : m_modelIndicies)
         {
         Ellipse::Model model = m_modelModule.models()[index.second];

         String name = findModelName(model.id());
         m_renderModule.render(model.renderObject().get(), model.shaderObject().get(), model.uniformList());
         }

         m_renderModule.setProjPerspective();
     }
     
     void setToCameraFront()
     {
         for(Pair<const Ellipse::ModelID, ModelVal>& model : m_models)
         {
             model.second.model() = Mat4{1.0f};
             translateModel(model.second.model(), (m_camera.position() + m_camera.front() * 2.0f));
             Vec3 zAxis{0.0f, 0.0f, -1.0f};
             Vec3 yAxis{0.0f, 1.0f, 0.0f};

             float yAxisAngle = 0.0f;
             if(m_camera.front().y != 0.0f)
             {
             yAxisAngle = static_cast<float>(acos(Ellipse::EllipseMath::dot(Vec3{0.0f, m_camera.front().y, 0.0f}, yAxis)));
             }
             yAxisAngle = Ellipse::EllipseMath::radians(90.0f) - yAxisAngle;
          
             float yRotateAngle = yAxisAngle;
             if(yAxisAngle < 0)
             {
                 yRotateAngle = Ellipse::EllipseMath::radians(360.0f) - yAxisAngle;
             }
             
             Vec3 cameraFrontAxisOrtho{0.0f};
             Vec3 cameraAxis{0.0f};
             float zAxisAngle = 0.0f;
             if(m_camera.front() != Vec3{0.0f})
             {
             cameraFrontAxisOrtho = Ellipse::EllipseMath::cross(m_camera.front(), Vec3{m_camera.front().x, 0.0f, m_camera.front().z});
             cameraAxis = Ellipse::EllipseMath::rotate(m_camera.front(), yRotateAngle, cameraFrontAxisOrtho);
             zAxisAngle = static_cast<float>(acos(
                                              Ellipse::EllipseMath::dot(cameraAxis, zAxis)
                                             )
                                            );
             }
             if(m_camera.front().x > 0)
             {
             zAxisAngle = Ellipse::EllipseMath::radians(360.0f) - zAxisAngle;
             }
             cameraFrontAxisOrtho = Ellipse::EllipseMath::normalize(cameraFrontAxisOrtho);
             if(yAxisAngle > 0)
             {
             cameraFrontAxisOrtho *= -1;
             }

             ELLIPSE_APP_LOG_INFO("camera vec: x {} y {} z {}", m_camera.front().x, m_camera.front().y, m_camera.front().z); 
             ELLIPSE_APP_LOG_INFO("rotated camera vec: x {} y {} z {}", cameraAxis.x, cameraAxis.y, cameraAxis.z); 
             ELLIPSE_APP_LOG_INFO("camera ortho vec: x {} y {} z {}", cameraFrontAxisOrtho.x, cameraFrontAxisOrtho.y, cameraFrontAxisOrtho.z); 
             ELLIPSE_APP_LOG_INFO("z Degrees {}", Ellipse::EllipseMath::degrees(zAxisAngle)); 
             ELLIPSE_APP_LOG_INFO("y Degrees {}", Ellipse::EllipseMath::degrees(yAxisAngle)); 
             ELLIPSE_APP_LOG_INFO("y rotate Degrees {}", Ellipse::EllipseMath::degrees(yRotateAngle)); 

             rotateModel(model.second.model(), yAxisAngle, cameraFrontAxisOrtho);
             rotateModel(model.second.model(), zAxisAngle, yAxis);

             // zAxis.x = (Ellipse::EllipseMath::radians(90.0f) - zAxisAngle) / Ellipse::EllipseMath::radians(90.0f);
             // zAxis.z = zAxisAngle / Ellipse::EllipseMath::radians(90.0f);
             // ELLIPSE_APP_LOG_INFO("zAxis manual x: {} z: {}", zAxis.x, zAxis.z);

             // rotateModel(model.second.model(), yAxisAngle, Ellipse::EllipseMath::normalize(zAxis));
             // rotateModel(model.second.model(), yAxisAngle, Ellipse::EllipseMath::normalize(Vec3{1.0f, 0.0f, 0.0f}));

             // model.second.setRotateAmount(zAxisAngle, Vec3{0.0f, 1.0f, 0.0f});
             // model.second.setRotateAmount(yAxisAngle, Vec3{1.0f, 0.0f, 0.0f});
             // model.second.setRotateAmount(yAxisAngle, Vec3{1.0f, 0.0f, 0.0f});
             // model.second.setRotateAmount(Ellipse::EllipseMath::radians(135.0f), Vec3{1.0f, 0.0f, 0.0f});
             // model.second.setRotateAmount(Ellipse::EllipseMath::radians(90.0f), Vec3{0.0f, 1.0f, 0.0f});

             setModelVal(model.first);
         }
     
     }

    private:
     Ellipse::Camera& m_camera;
};

