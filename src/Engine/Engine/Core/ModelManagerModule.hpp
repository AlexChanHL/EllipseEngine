#pragma once

#include "Engine/Module.hpp"
#include "Core/Utils/VectorSharedIteratorHeap.hpp"
#include "Math/Random/Random.hpp"
#include "Core/Base.hpp"
namespace Ellipse
{

struct Viewspace
{
   public:
    // Viewspace(int32_t posX, int32_t posY, int32_t width, int32_t height)
    Viewspace(float posX,
              float posY,
              float width,
              float height)
     : m_posX{posX},
       m_posY{posY},
       m_width{width},
       m_height{height}
     {

     }
    Viewspace(i32_t posX,
              i32_t posY,
              i32_t width,
              i32_t height)
     : m_posX{static_cast<float>(posX)},
       m_posY{static_cast<float>(posY)},
       m_width{static_cast<float>(width)},
       m_height{static_cast<float>(height)}
    {

    }
    Viewspace()
    : m_posX{0},
      m_posY{0},
      m_width{0},
      m_height{0}
    {

    }
   
    Viewspace(const Viewspace& viewspace)
    : m_posX{viewspace.m_posX},
      m_posY{viewspace.m_posY},
      m_width{viewspace.m_width},
      m_height{viewspace.m_height}
    {

    }

    void operator=(const Viewspace& viewspace)
    {
    m_posX = viewspace.m_posX;
    m_posY = viewspace.m_posY;
    m_width = viewspace.m_width;
    m_height = viewspace.m_height;
    }

    bool operator==(Viewspace viewspace)
    {
    return m_posX == viewspace.m_posX
           && m_posY == viewspace.m_posY
           && m_width == viewspace.m_width 
           && m_height == viewspace.m_height;
    }
    bool operator!=(Viewspace viewspace)
    {
    return m_posX != viewspace.m_posX
           || m_posY != viewspace.m_posY
           || m_width != viewspace.m_width 
           || m_height != viewspace.m_height;
    }

   public:
    // int32_t m_posX;
    // int32_t m_posY;
    // int32_t m_width;
    // int32_t m_height;
  
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
  
   private: 
};

struct ModelID
{
   public:
    ModelID()
    : m_ID{0}
    {

    }

    ~ModelID()
    {

    }

   public:
    int32_t m_ID;
};

struct RotateAmount
{
   public:
    float m_radians;
    Vec3 m_rotationAxis;
};

struct ModelLayerModel
{
   public:
    // [ Invalid only used by vector ]
    ModelLayerModel()
    : m_modelID{ModelID{}},
      m_modelName{nullptr},
      m_modelTranslationAmount{Vec3{0.0f}},
      m_modelRotationAmount{RotateAmount{0.0f, Vec3{1.0f, 1.0f, 1.0f}}},
      m_modelScalarAmount{Vec3{0.0f}},
      m_model{0.0f},
      m_isModified{false},
      m_isRemoved{false}
    {

    }
    ModelLayerModel(ModelID modelID, const char* modelName)
    : m_modelID{modelID},
      m_modelName{modelName},
      m_modelTranslationAmount{Vec3{0.0f, 0.0f, 0.0f}},
      m_modelRotationAmount{RotateAmount{0.0f, Vec3{1.0f, 1.0f, 1.0f}}},
      m_modelScalarAmount{Vec3{1.0f, 1.0f, 1.0f}},
      m_model{1.0f},
      m_isModified{false},
      m_isRemoved{false}
    {

    }
    ~ModelLayerModel()
    {
    }

   public:
    ModelID m_modelID;
    const char* m_modelName;

    Vec3 m_modelTranslationAmount;
    RotateAmount m_modelRotationAmount;
    Vec3 m_modelScalarAmount;
    Mat4 m_model;
    bool m_isModified;

    bool m_isRemoved;
};

struct ModelViewspace
{
   public:
    ModelViewspace(Viewspace viewspace, ModelLayerModel modelLayerModel)
    : m_viewspace{viewspace},
      m_models{ModelLayerModel{modelLayerModel}}
    {

    }
    ~ModelViewspace()
    {

    }

   public:
    Viewspace m_viewspace;
    // [ m_models is a exact copy of models in render modules
    //   render layer models, some problems may arise if these
    //   two differ ]
    VectorSharedIteratorHeap<ModelLayerModel> m_models;
};

struct ModelWorld
{
   public:
    ModelWorld(Viewspace viewspace, ModelLayerModel modelLayerModel)
    : m_viewspaces{viewspace},
      m_models{ModelLayerModel{modelLayerModel}}
    {

    }
    ~ModelWorld()
    {

    }

   public:
    Vector<Viewspace> m_viewspaces;
    // [ m_models is a exact copy of models in render modules
    //   render layer models, some problems may arise if these
    //   two differ ]
    VectorSharedIteratorHeap<ModelLayerModel> m_models;
};

struct ModelLayer
{
   public:
    Vector<ModelViewspace> m_modelViewspaces;
    Vector<ModelWorld> m_modelWorlds;
};

struct ModelWorld
{
   public:
    ModelWorld()
    : m_modelPositions{Pair<i32_t, i32_t>{0, 0}}
      m_currentModelPosition{0}
    {

    }

    void addModelPosition(i32_t indexInModelList)
    {

    }

    void updateNextSubWorld()
    {
    m_currentModelPosition++;
    }

    unsigned long modelPositionCount()
    {
    return m_modelPositions.size();
    }
  
    i32_t start() const
    {
    return m_modelPositions[m_currentModelPosition].first;
    }

    i32_t end() const
    {
    return m_modelPositions[m_currentModelPosition].second;
    }
    
    
   private:
    Vector<Pair<i32_t, i32_t>> m_modelPositions;
    i32_t m_currentModelPosition;
};

// [ Should rename ModelManagerModule to ModelManagerLayerModule ]
class ModelManagerModule : public ILayerModule
{
   public:
    ModelManagerModule()
    {
    // setName("ModelManagerModule");
    }
    ~ModelManagerModule()
    {

    }

    struct SubModelManager
    {
       public:
        struct Model;

        SubModelManager(
        Viewspace specifiedViewspace,
        ModelID modelID,
        const char* modelName, 
        String vertexShader,
        String fragmentShader,
        VerticiesData verticies,
        UniformList uniformList,
        Mat4& model
                       )
        : m_viewSpace{specifiedViewspace},
          m_models{Model{
                    modelID,
                    modelName,
                    vertexShader,
                    fragmentShader,
                    verticies,
                    uniformList,
                    model
                      }}
        {

        }

        void addViewspace(Viewspace viewspace)
        {
        // m_viewspaces.push_back(viewspace);
        }

        void addModel(
        ModelID modelID,
        const char* modelName, 
        String vertexShader,
        String fragmentShader,
        VerticiesData verticies,
        UniformList uniformList,
        Mat4& model
                     )
        {
        m_models.push_back(Model{modelID,
                                 modelName,
                                 vertexShader,
                                 fragmentShader,
                                 verticies,
                                 uniformList,
                                 model});
        }

        std::vector<Model> models()
        {
        return m_models;
        }

        Viewspace viewspace()
        {
        return m_viewSpace;
        }

       public:
        struct Model
        {
          public:
           Model(ModelID modelID,
                 const char* name,
                 String vertexShader,
                 String fragmentShader,
                 VerticiesData verticies,
                 UniformList uniformList,
                 Mat4& model
                 )
           :
             m_modelID{modelID},
             m_name{name},
             m_vertexShader{vertexShader},
             m_fragmentShader{fragmentShader},
             m_verticies{verticies},
             m_uniformList{uniformList},
             m_model{model}
           {

           }
           ~Model()
           {

           }

          public:
           ModelID m_modelID;
           const char* m_name;
           String m_vertexShader;
           String m_fragmentShader;
           VerticiesData m_verticies;
           UniformList m_uniformList;
           Mat4& m_model;
        };

        // Viewspace m_currentViewspace;
        // ModelWorld m_world;
        // Vector<Viewspace> m_viewspaces;
        Viewspace m_viewSpace;
        // Vector<ModelListLocation> m_modelListLocations;
        Vector<Model> m_models;
    };


    virtual void initLayerModule() override = 0;
    virtual void onUpdateLayer() override = 0;
    // virtual void addModel(ModelID& modelID, const char* modelName) = 0;
    virtual void addModel(ModelID& modelID,
                          const char* modelName,
                          String vertexShader,
                          String fragmentShader,
                          VerticiesData verticies,
                          UniformList uniformList
                          ) = 0;

    virtual void translateModel(ModelID modelID, Vec3 translationAmount) = 0;

    virtual void rotateModel(ModelID modelID, float radians, Vec3 rotationAxis) = 0;

    virtual void scaleModel(ModelID modelID, Vec3 scalarAmount) = 0;

    virtual void removeModel(ModelID modelID) = 0;

    virtual void setDifferentInViewspace(float viewspaceWidth,
                                         float viewspaceHeight,
    float originalWindowWidth,
    float originalWindowHeight) = 0;

    virtual void clearSubModelManagers() = 0;

    virtual std::vector<SubModelManager> subModelManagers() = 0;

    virtual std::vector<ModelLayer>& modelLayers() = 0;

    virtual std::vector<ModelLayer>::iterator previousModelLayersIterator() = 0;

    virtual void setWorld(const char* worldName) = 0;
    virtual void setViewspace(Viewspace viewspace) = 0;

    static SharedPtr<ModelManagerModule> createModelManagerModule();

   protected:
    virtual void onUpdateModelMatrices() = 0;

    virtual void translateModelInModelList(Mat4& model, Vec3 translationAmount) = 0;
    virtual void rotateModelInModelList(Mat4& model, float radians, Vec3 rotationAxis) = 0;
    virtual void scaleModelInModelList(Mat4& model, Vec3 scalarAmount) = 0;
};

}   // namespace Ellipse
