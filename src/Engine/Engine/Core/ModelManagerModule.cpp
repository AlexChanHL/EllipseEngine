
// [ UniformVariable.hpp ]
#include "Renderer/UniformVarible.hpp"
#include "Renderer/VerticiesData.hpp"
#include "ModelManagerModule.hpp"

namespace Ellipse
{

class ModelManagerModuleImpl : public ModelManagerModule
{
   public:
    ModelManagerModuleImpl()
    : m_randomRemoveLast{int32_t(pow(10,2))},
      m_modelOrderCount{0}
    {
    setName("ModelManagerLayerModule");
    }
  
    ~ModelManagerModuleImpl()
    {

    }
 
    virtual void initLayerModule() override
    {
    m_modelLayers.push_back(ModelLayer{});
    m_modelLayersIterator = m_modelLayers.begin();
    m_previousModelLayersIterator = m_modelLayers.begin();
    }

    virtual void onUpdateLayer() override
    {
    onUpdateModelMatrices();

    // for(ModelLayer& modelLayer : m_modelLayers)
    // {
    // for(ModelViewspace& modelViewspace : modelLayer.m_modelViewspaces)
    // {
    // // std::cout << "Model Layer Viewspace posX: " << modelViewspace.m_viewspace.m_posX << '\n';
    //
    // }
    // }

    m_modelLayersIterator++;
    m_previousModelLayersIterator = m_modelLayersIterator - 1;
    if(m_modelLayersIterator == m_modelLayers.end())
    {
    m_modelLayersIterator = m_modelLayers.begin();
    }

    }


    virtual void addModel(ModelID& modelID,
                          const char* modelName, 
                          String vertexShader,
                          String fragmentShader,
                          VerticiesData verticies,
                          UniformList uniformList
                          ) override
    {
    // modelID.m_ID = m_randomRemoveLast.chooseRandomVal();
    // if(m_subModelMangers.empty() || m_subModelMangers[m_subModelMangers.size() - 1].m_viewSpace != m_currentViewspace)
    // // if(m_subModelMangers.empty() || m_subModelMangers[m_subModelMangers.size() - 1].m_world != m_currentWorld)
    // {
    // // m_modelLayersIterator->m_worlds.push_back(ModelWorld{
    // // m_currentWorld,
    // // m_currentViewspace,
    // // ModelLayerModel{
    // //   modelID,
    // //   modelName
    // //                }
    // // }
    // //
    // // )
    // m_modelLayersIterator->m_modelViewspaces.push_back(ModelViewspace{
    //       m_currentViewspace,
    //       ModelLayerModel{
    //         modelID,
    //         modelName
    //                      }
    //                   }
    //                                                    );
    //
    // m_subModelMangers.push_back(
    //  SubModelManager{
    //   m_currentViewspace,
    //   modelID,
    //   modelName,
    //   vertexShader,
    //   fragmentShader,
    //   verticies,
    //   uniformList,
    //   m_modelLayersIterator->m_modelViewspaces[m_modelLayersIterator->m_modelViewspaces.size() - 1].m_models[0].m_model
    //    }
    //                           );
    //
    // m_modelOrderCount++;
    //
    // return; 
    // }
    //
    // m_modelLayersIterator->m_modelViewspaces[m_modelLayersIterator->m_modelViewspaces.size() - 1].m_models.pushBack(
    // // m_modelLayersIterator->m_worlds[m_modelLayersIterator->m_worlds.size() - 1].m_models.pushBack(
    //     ModelLayerModel{
    //     modelID, modelName
    //                    }
    //                                               );
    // m_subModelMangers[m_subModelMangers.size() - 1].addModel(
    //    modelID,
    //    modelName,
    //    vertexShader,
    //    fragmentShader,
    //    verticies,
    //    uniformList,
    //    m_modelLayersIterator->m_modelViewspaces[m_modelLayersIterator->m_modelViewspaces.size() - 1].m_models[m_modelLayersIterator->m_modelViewspaces[m_modelLayersIterator->m_modelViewspaces.size() - 1].m_models.size() - 1].m_model);
    //
    // m_modelOrderCount++;
    }

    virtual void translateModel(ModelID modelID, Vec3 translationAmount) override
    {
    // [ Change the nam ]
    for(unsigned long i=0;i<m_modelLayersIterator->m_modelViewspaces.size();i++)
    {
    if(m_modelLayersIterator->m_modelViewspaces[i].m_viewspace  == m_currentViewspace)
    {
    for(unsigned long j=0;j<m_modelLayersIterator->m_modelViewspaces[i].m_models.size();j++)
    {
    if(m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelID.m_ID == modelID.m_ID)
    {
    // [ Editing removed model is allowed, fix this problem ]
    m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelTranslationAmount = translationAmount;
    m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_isModified = true; 
    }
    }
    } 
    }

    }

    virtual void rotateModel(ModelID modelID, float radians, Vec3 rotationAxis) override
    {
    // for(unsigned long i=0;i<m_modelLayersIterator->m_modelViewspaces.size();i++)
    // {
    // if(m_modelLayersIterator->m_modelViewspaces[i].m_viewspace == m_currentViewspace)
    // {
    // for(unsigned long j=0;j<m_modelLayersIterator->m_modelViewspaces[i].m_models.size();j++)
    // {
    // if(m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelID.m_ID == modelID.m_ID)
    // {
    // // [ Editing removed model is allowed, fix this problem ]
    //           
    // m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelRotationAmount.m_rotationAxis = rotationAxis;
    // m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelRotationAmount.m_radians = radians;
    // m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_isModified = true; 
    // }
    // }
    // } 
    // }
    }

    virtual void scaleModel(ModelID modelID, Vec3 scalarAmount) override
    {
    // for(unsigned long i=0;i<m_modelLayersIterator->m_modelViewspaces.size();i++)
    // {
    // if(m_modelLayersIterator->m_modelViewspaces[i].m_viewspace  == m_currentViewspace)
    // {
    // for(unsigned long j=0;j<m_modelLayersIterator->m_modelViewspaces[i].m_models.size();j++)
    // {
    // if(m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelID.m_ID == modelID.m_ID)
    // {
    // // [ Editing removed model is allowed, fix this problem ]
    // m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelScalarAmount = scalarAmount;
    // m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_isModified = true; 
    // }
    // }
    // } 
    // }
    }

    virtual void removeModel(ModelID modelID) override
    {
    // bool found = false;
    // // [ Loop through model list inside m_modelLayerIterator and mark model to be removed ]
    // for(unsigned long i = 0; i < m_modelLayersIterator->m_modelViewspaces.size(); i++)
    // {
    // if(m_currentViewspace == m_modelLayersIterator->m_modelViewspaces[i].m_viewspace)
    // {
    // for(unsigned long j = 0; j < m_modelLayersIterator->m_modelViewspaces[i].m_models.size(); j++)
    // {
    // // [ Need to remove model from model view space so that can't remove twice ]
    // if(m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelID.m_ID == modelID.m_ID)
    // {
    // m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_isRemoved = true;
    // found = true;
    // }
    // }
    // }
    // }
    // if(!found)
    // {
    // std::cout << "Couldn't find using model ID model in model list\n";
    // }

    ModelWorld queryWorld = m_currentWorld;

    for(unsigned long i = 0; i < m_currentWorld.worldCount(); i++)
    {

    for(unsigned long j = queryWorld.start(); j < queryWorld.end(); j++)
    {
    if(modelID == modelModels[j].m_ID)
    {
    modelModels.erase(modelModels.begin() + j);
    m_modelsToBeRemoved.push_back(modelID);
    }
    
    }

    }


    }

    virtual void setDifferentInViewspace(float viewspaceWidth,
                                         float viewspaceHeight,
                                         float originalWindowWidth,
                                         float originalWindowHeight) override;

    virtual void clearSubModelManagers() override
    {
    m_subModelMangers.clear();
    }

    virtual std::vector<SubModelManager> subModelManagers() override
    {
    return m_subModelMangers;
    }

    virtual std::vector<ModelLayer>& modelLayers() override
    {
    return m_modelLayers;
    } 

    virtual std::vector<ModelLayer>::iterator previousModelLayersIterator() override
    {
    return m_previousModelLayersIterator;
    }

    virtual void setWorld(const char* worldName) override
    {

    }

    virtual void setViewspace(Viewspace viewspace) override
    {
    m_currentViewspace = viewspace;
    }

    SharedPtr<ModelManagerModule> createModelManagerModule();

   private:
    virtual void onUpdateModelMatrices() override
    {

    for(unsigned long i = 0; i < m_modelLayersIterator->m_modelViewspaces.size(); i++)
    {
    for(unsigned long j = 0; j < m_modelLayersIterator->m_modelViewspaces[i].m_models.size(); j++)
    {
    if(m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_isModified)
    {
    m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_model = Mat4(1.0f); 

    translateModelInModelList(
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_model,
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelTranslationAmount
                             );
    rotateModelInModelList(
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_model,
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelRotationAmount.m_radians,
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelRotationAmount.m_rotationAxis
                          );
    scaleModelInModelList(
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_model,
              m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_modelScalarAmount
                         );

    m_modelLayersIterator->m_modelViewspaces[i].m_models[j].m_isModified = false;
    }

    }

    }
    
    }

    virtual void translateModelInModelList(Mat4& model, Vec3 translationAmount) override
    {
    model = EllipseMath::translate(model, translationAmount);
    }
    virtual void rotateModelInModelList(Mat4& model, float radians, Vec3 rotationAxis) override
    {
    model = EllipseMath::rotate(model, radians, rotationAxis);
    }
    virtual void scaleModelInModelList(Mat4& model, Vec3 scalarAmount) override
    {
    model = EllipseMath::scale(model, scalarAmount);
    }

   private: 
    std::vector<SubModelManager> m_subModelMangers;
    
    std::vector<ModelLayer> m_modelLayers;
    std::vector<ModelLayer>::iterator m_modelLayersIterator;
    std::vector<ModelLayer>::iterator m_previousModelLayersIterator;

    Viewspace m_currentViewspace;

    // [ Rename to m_uniqueIDGenerator ]
    EllipseMath::RandomRemoveLast m_randomRemoveLast;
    u32_t m_modelOrderCount;
};

void ModelManagerModuleImpl::setDifferentInViewspace(float viewspaceWidth,
      float viewspaceHeight,
      float originalWindowWidth,
      float originalWindowHeight)
{
    m_currentViewspace.m_width += ( static_cast<float>(m_currentViewspace.m_width) / static_cast<float>(originalWindowWidth) ) * static_cast<float>(viewspaceWidth);

    m_currentViewspace.m_height += (static_cast<float>(m_currentViewspace.m_height) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceHeight);

    m_currentViewspace.m_posX += (static_cast<float>(m_currentViewspace.m_posX) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceWidth);

    m_currentViewspace.m_posY += (static_cast<float>(m_currentViewspace.m_posY) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceHeight);


    for(ModelLayer& modelLayer : m_modelLayers)
    {
    for(ModelViewspace& modelViewspace : modelLayer.m_modelViewspaces)
    {
    float viewspaceWindowWidthRatio = 
    static_cast<float>(modelViewspace.m_viewspace.m_width)
    / 
    static_cast<float>(originalWindowWidth);

    float viewspaceWindowHeightRatio = 
    static_cast<float>(modelViewspace.m_viewspace.m_height)
    / 
    static_cast<float>(originalWindowHeight);

    float viewspaceWindowPosXRatio = 
    static_cast<float>(modelViewspace.m_viewspace.m_posX)
    / 
    static_cast<float>(originalWindowWidth);

    float viewspaceWindowPosYRatio = 
    static_cast<float>(modelViewspace.m_viewspace.m_posY)
    / 
    static_cast<float>(originalWindowHeight);

    // [ This ratio solution is heavily hackish, need to find
    //   a better solution for resolving multiple viewspaces 
    //   adjust to the new window size ]

    float viewspaceRatioWidth = static_cast<float>(viewspaceWidth) * viewspaceWindowWidthRatio;
    float viewspaceRatioHeight = static_cast<float>(viewspaceHeight) * viewspaceWindowHeightRatio;
    float viewspaceRatioPosX = static_cast<float>(viewspaceWidth) * viewspaceWindowPosXRatio;
    float viewspaceRatioPosY = static_cast<float>(viewspaceHeight) * viewspaceWindowPosYRatio;

    // std::cout << "Window difference " <<  viewspaceWidth << '\n';
    // std::cout << "Window ratio " << viewspaceWindowWidthRatio << '\n';

    if(modelViewspace.m_viewspace.m_posX != 0 
       || modelViewspace.m_viewspace.m_posY != 0)
    {
    modelViewspace.m_viewspace.m_posX += viewspaceRatioPosX;
    modelViewspace.m_viewspace.m_posY += viewspaceRatioPosY;
    }

    modelViewspace.m_viewspace.m_width += viewspaceRatioWidth;
    modelViewspace.m_viewspace.m_height += viewspaceRatioHeight;
    }
    }
}

SharedPtr<ModelManagerModule> ModelManagerModule::createModelManagerModule()
{
    return createShared<ModelManagerModuleImpl>();
}

}   // namespace Ellipse
