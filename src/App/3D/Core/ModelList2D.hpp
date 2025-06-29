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
         m_renderModule.setProjOrtho();

         addAmounts();

         for(Pair<String, u64_t> index : m_modelIndicies)
         {
             Ellipse::Model model = m_modelModule.models()[index.second];

             String name = findModelName(model.id());
             m_renderModule.render(model.renderObject().get(), model.shaderObject().get(), model.uniformList());
         }

         m_renderModule.setProjPerspective();
     }
     
     virtual void addAmounts() override
     {
         for(Pair<const Ellipse::ModelID, ModelVal>& model : m_models)
         {
             model.second.model() = Mat4{1.0f};

             Vec3 zAxis{0.0f, 0.0f, -1.0f};
             Vec3 yAxis{0.0f, 1.0f, 0.0f};

             float yAxisAngle = 0.0f;
             if(m_camera.front().y != 0.0f)
             {
                 yAxisAngle = static_cast<float>(acos(Ellipse::EllipseMath::dot(Vec3{0.0f, m_camera.front().y, 0.0f}, yAxis)));
                 yAxisAngle = Ellipse::EllipseMath::radians(90.0f) - yAxisAngle;
             }
          
             float yRotateAngle = yAxisAngle;
             if(yAxisAngle < 0)
             {
                 yRotateAngle = Ellipse::EllipseMath::radians(360.0f) - yAxisAngle;
             }
             
             Vec3 cameraFrontAxisOrtho{1.0f};
             Vec3 cameraAxis{0.0f};
             float zAxisAngle = 0.0f;
             if(m_camera.front().y != 0.0f)
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

             model.second.model() = Ellipse::EllipseMath::translate(model.second.model(), (m_camera.position() + m_camera.front() * 2.0f));
             Vec3 translateVec = model.second.translationAmount();
             translateVec = Ellipse::EllipseMath::rotate(translateVec, zAxisAngle, yAxis);
             translateVec = Ellipse::EllipseMath::rotate(translateVec, yAxisAngle, cameraFrontAxisOrtho);
             ELLIPSE_APP_LOG_INFO("translate vector x {} y {} z {}", translateVec.x, translateVec.y, translateVec.z); 
             model.second.model() = Ellipse::EllipseMath::translate(model.second.model(), translateVec);


             model.second.model() = Ellipse::EllipseMath::rotate(model.second.model(), model.second.rotationAmount().second, m_camera.front());
             model.second.model() = Ellipse::EllipseMath::rotate(model.second.model(), yAxisAngle, cameraFrontAxisOrtho);
             model.second.model() = Ellipse::EllipseMath::rotate(model.second.model(), zAxisAngle, yAxis);


             model.second.model() = Ellipse::EllipseMath::scale(model.second.model(), model.second.scaleAmount());

             setModelVal(model.first);
         }
     
     }

     void translate(const char* name, Vec2 vec)
     {
     model(name).setTranslateAmount(Vec3{vec, 0.0f});
     }

     void rotate(const char* name,  float theta)
     {
     model(name).setRotateAmount(theta, Vec3{0.0f, 0.0f, 1.0f});
     }

     void scale(const char* name, Vec2 vec)
     {
     model(name).setScaleAmount(Vec3{vec, 1.0f});
     }

    private:
     Ellipse::Camera& m_camera;
};

