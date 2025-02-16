#pragma once

#include "Engine/Module.hpp"
#include "Renderer/UniformVarible.hpp"
#include "Core/Utils/VectorSharedIteratorHeap.hpp"
#include "Math/Random/Random.hpp"
#include "Math/TrigonometricUnits.hpp"
#include "Math/Matrix.hpp"
#include "Core/Base.hpp"

namespace Ellipse
{

struct Viewspace
{
   public:
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
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
  
   private: 
};

struct RotateAmount
{
   public:
    float m_radians;
    Vec3 m_rotationAxis;
};

// [ -1 is a invalid state for id ]
struct ModelID
{
   public:
    ModelID()
    : m_ID{-1}
    {

    }
    ModelID(i32_t modelID)
    : m_ID{modelID}
    {

    }
    ~ModelID()
    {

    }

    i32_t id() const
    {
    return m_ID;
    }

    
    bool operator==(ModelID modelID)
    {
    return m_ID == modelID.m_ID;
    }

   public:
    i32_t m_ID;
};


class ObjectID
{
   public:
    ObjectID()
    : m_ID{0}
    {

    }
    ObjectID(u32_t ID)
    : m_ID{ID}
    {

    }
    ~ObjectID()
    {

    }

    bool operator==(ObjectID objectID)
    {
    return m_ID == objectID.id();
    }
    bool operator!=(ObjectID objectID)
    {
    return m_ID != objectID.id();
    }

    u32_t id() const
    {
    return m_ID;
    }

   private:
    u32_t m_ID;
};

class ModelData
{
   public:

   private:
    Vector<float> m_positions;
    Vector<float> m_normals;
    Vector<float> m_textureCoords;
};

// class A
// {
//    public:
//     i32_t m_num;
//     i32
// };


struct ModelModuleModel
{
   public:
    // [ Invalid only used by vector ]
    ModelModuleModel()
    : m_modelID{ModelID{}},
      m_modelName{nullptr},
      m_modelTranslationAmount{Vec3{0.0f}},
      m_modelRotationAmount{RotateAmount{0.0f, Vec3{1.0f, 1.0f, 1.0f}}},
      m_modelScalarAmount{Vec3{0.0f}},
      m_model{0.0f},
      m_isModified{false},
      m_isHidden{false},
      m_isInWireframeMode{false},
      m_isRemoved{false}
    {

    }
    ModelModuleModel(ModelID modelID, const char* modelName)
    : m_modelID{modelID},
      m_modelName{modelName},
      m_modelTranslationAmount{Vec3{0.0f, 0.0f, 0.0f}},
      m_modelRotationAmount{RotateAmount{0.0f, Vec3{1.0f, 1.0f, 1.0f}}},
      m_modelScalarAmount{Vec3{1.0f, 1.0f, 1.0f}},
      m_model{1.0f},
      m_isModified{false},
      m_isHidden{false},
      m_isInWireframeMode{false},
      m_isRemoved{false}
    {

    }
    ~ModelModuleModel()
    {

    }


    void setTranslationAmount(Vec3 translationAmount)
    {
    m_modelTranslationAmount = translationAmount;
    }

    void setRotationAmount(float radians, Vec3 rotationAxis)
    {
    m_modelRotationAmount.m_radians = radians;
    m_modelRotationAmount.m_rotationAxis = rotationAxis;
    }

    void setScalarAmount(Vec3 scalarAmount)
    {
    m_modelScalarAmount = scalarAmount;
    }

    void setIsModified(bool isModified)
    {
    m_isModified = isModified;
    }

    void setIsHidden(bool isHidden)
    {
    m_isHidden = isHidden;
    }

    void setIsInWireframe(bool isInWireframe)
    {
    m_isInWireframeMode = isInWireframe;
    }

    void resetModelMatrix()
    {
    m_model = Mat4(1.0f);
    }

    const char* name() const
    {
    return m_modelName;
    }

    Mat4& model()
    {
    return m_model;
    }

    bool isModified() const
    {
    return m_isModified;
    }

    Vec3 translationAmount() const
    {
    return m_modelTranslationAmount;
    }

    RotateAmount rotationAmount() const
    {
    return m_modelRotationAmount;
    }

    Vec3 scalarAmount() const
    {
    return m_modelScalarAmount;
    }

    bool isHidden() const
    {
    return m_isHidden;
    }

    bool isInWireframeMode() const
    {
    return m_isInWireframeMode; 
    }

   public:
    ModelID m_modelID;
    const char* m_modelName;

    Vec3 m_modelTranslationAmount;
    RotateAmount m_modelRotationAmount;
    Vec3 m_modelScalarAmount;
    Mat4 m_model;
    bool m_isModified;
    
    bool m_isHidden;
    bool m_isInWireframeMode;
    bool m_isRemoved;
};

// [ There should be main worlds and sub worlds , the
//   sub worlds reside inside main worlds and only one 
//   main world in each layer ]
//
// [ Worlds and subworlds should be different and have
//   different implementations ]
//
// [ Segments of world are added ]
//
// +-------+------------+----------------+
// | World | User world |                |
// +-------+------------+----------------+
// |       |            |                |
// +-------+------------+----------------+
// |       |            |                |
// |       |            |                |
// |       |            |                |
// |       |            |                |
// |       |            |                |
// +-------+------------+----------------+
//
//                 +------------+
//                 | User world |
//                 +------------+

struct ModelWorld
{
   public:
    ModelWorld()
    : m_name{nullptr},
      m_orderInList{0},
      m_modelPositions{Vector<Pair<u32_t, u32_t>>{}},
      m_currentModelPosition{0}
    {

    }
    ModelWorld(const char* name, u32_t orderInList)
    : m_name{name},
      m_orderInList{orderInList},
      m_modelPositions{Vector<Pair<u32_t, u32_t>>{}},
      m_currentModelPosition{0}
    {

    }
    ModelWorld(const char* name, u32_t orderInList, u32_t modelOrderCount)
    : m_name{name},
      m_orderInList{orderInList},
      m_modelPositions{Pair<u32_t, u32_t>{modelOrderCount, 0}},
      m_currentModelPosition{0}
    {

    }
    ~ModelWorld()
    {

    }

    ModelWorld(const ModelWorld& modelWorld)
    : m_name{modelWorld.name()},
      m_orderInList{modelWorld.orderInList()},
      m_modelPositions{modelWorld.modelPositions()},
      m_currentModelPosition{modelWorld.currentModelPosition()}
    {

    }

    void operator=(const ModelWorld& modelWorld)
    {
    m_name = modelWorld.name();
    m_orderInList = modelWorld.orderInList();
    m_modelPositions = modelWorld.modelPositions();
    m_currentModelPosition = modelWorld.currentModelPosition();
    }

    bool operator==(const ModelWorld& modelWorld)
    {
    return strcmp(m_name, modelWorld.name()) == 0;
    }

    bool operator!=(const ModelWorld& modelWorld)
    {
    return strcmp(m_name, modelWorld.name()) != 0;
    }

    void addModelBeginPosition(u32_t indexInModelList)
    {
    m_modelPositions.push_back(Pair<u32_t, u32_t>{indexInModelList, 0});
    }

    void addModelEndPosition(u32_t indexInModelList)
    {
    m_modelPositions[m_modelPositions.size() - 1].second = indexInModelList;
    }

    void setModelEndPosition(u32_t positionIndex,  u32_t indexInModelList)
    {
    m_modelPositions[positionIndex].second = indexInModelList;
    }

    void decrementStart()
    {
    m_modelPositions[m_currentModelPosition].first -= 1;

    }

    void decrementEnd()
    {
    m_modelPositions[m_currentModelPosition].second -= 1;

    }

    void decrementStart(u32_t position)
    {
    m_modelPositions[position].first -= 1;

    }

    void decrementEnd(u32_t position)
    {
    m_modelPositions[position].second -= 1;

    }


    void erasePosition(u64_t positionIndex)
    {
    m_modelPositions.erase(m_modelPositions.begin() + static_cast<i64_t>(positionIndex));
    }

    void updateNextSubWorld()
    {
    m_currentModelPosition++;
    if(m_currentModelPosition == m_modelPositions.size())
    {
    resetCurrentPosition();
    }
    }

    void update(u32_t maxLayerCount)
    {
    // if(m_layerCount + 1 == maxLayerCount)
    // {
    // m_layerCount = 0;
    // return;
    // }
    // m_layerCount++;
    }

    void resetCurrentPosition()
    {
    m_currentModelPosition = 0;
    }

    // u64_t layerCount() const
    // {
    // return m_layerCount;
    // }

    const char* name() const
    {
    return m_name;
    }

    u32_t orderInList() const
    {
    return m_orderInList;
    }

    u32_t start() const
    {
    // std::cout << currentModelPosition << '\n';
    return m_modelPositions[m_currentModelPosition].first;
    }

    u32_t end() const
    {
    return m_modelPositions[m_currentModelPosition].second;
    }

    u64_t modelPositionCount() const
    {
    return m_modelPositions.size();
    }

    Pair<u32_t, u32_t> modelPosition(u32_t queryPosition) const
    {
    return m_modelPositions[queryPosition];
    }

    Vector<Pair<u32_t, u32_t>> modelPositions() const
    {
    return m_modelPositions;
    }

    u32_t currentModelPosition() const
    {
    return m_currentModelPosition;
    }
    
    
   private:
    const char* m_name;
    u32_t m_orderInList;
    Vector<Pair<u32_t, u32_t>> m_modelPositions;
    u32_t m_currentModelPosition;
};

// Indexing uses mainworld as 0th, and subworlds 1, 2, ...
class ModelWorldQuery
{
   public:
    ModelWorldQuery()
    : m_isInList{false},
      m_mainWorldIndex{0},
      m_index{0}
    {
    
    }
    ModelWorldQuery(bool isInList,
                    u32_t mainWorldIndex,
                    u32_t index)
    : m_isInList{isInList},
      m_mainWorldIndex{mainWorldIndex},
      m_index{index}
    {
    
    }
    ModelWorldQuery(const ModelWorldQuery& modelWorldQuery)
    : m_isInList{modelWorldQuery.isInList()},
      m_mainWorldIndex{modelWorldQuery.mainWorldIndex()},
      m_index{modelWorldQuery.index()}
    {

    }
    void operator=(const ModelWorldQuery& modelWorldQuery)
    {
    m_isInList = modelWorldQuery.isInList();
    m_mainWorldIndex = modelWorldQuery.mainWorldIndex();
    m_index = modelWorldQuery.index();
    }
    ~ModelWorldQuery()
    {

    }

    bool isInList() const
    {
    return m_isInList;
    }

    u32_t mainWorldIndex() const
    {
    return m_mainWorldIndex;
    }
    u32_t index() const
    {
    return m_index;
    }
    
   private:
    bool m_isInList;
    u32_t m_mainWorldIndex;
    u32_t m_index;
};

struct MainWorld
{
   public:
    MainWorld(ModelWorld mainWorld)
    : m_mainWorld{mainWorld},
      m_subWorlds{Vector<ModelWorld>{}}
    {

    }
    MainWorld(ModelWorld mainWorld, Vector<ModelWorld> subWorlds)
    : m_mainWorld{mainWorld},
      m_subWorlds{subWorlds}
    {

    }
    ~MainWorld()
    {

    }

    void addSubWorld(ModelWorld world)
    {
    m_subWorlds.push_back(world);
    }

    ModelWorld& mainWorld()
    {
    return m_mainWorld;
    }

    Vector<ModelWorld>& subWorlds()
    {
    return m_subWorlds;
    }

   public:
    ModelWorld m_mainWorld;
    Vector<ModelWorld> m_subWorlds;
};

enum class EditType
{
   None = 0,
   IsWireframe = 1,
   IsHidden  = 2
};

class EditSetting
{
   public:
    EditSetting()
    {

    }
    virtual ~EditSetting()
    {

    }

    virtual EditType getType() = 0;

   private:
};

class WireFrame : public EditSetting
{
   public:
    WireFrame(bool isWireFrame)
    : m_isWireFrame{isWireFrame}
    {

    }
    ~WireFrame()
    {

    }

    virtual EditType getType()
    {
    return EditType::IsWireframe;
    }

    bool isWireFrame() const
    {
    return m_isWireFrame;
    }

   private:
    bool m_isWireFrame;
};

class Hidden : public EditSetting
{
   public:
    Hidden(bool isHideModel)
    : m_isHidden{isHideModel}
    {

    }
    ~Hidden()
    {

    }

    virtual EditType getType() override
    {
    return EditType::IsHidden;
    }

    bool isHidden() const
    {
    return m_isHidden;
    }

   private:
    bool m_isHidden;
};

// [ Stores own copy of the models ]
struct UserWorld
{
   public:
    UserWorld()
    : m_layerCount{0},
      m_mainWorldName{nullptr},
      m_name{nullptr},
      m_subWorldNames{Vector<const char*>{}},
      m_editModels{Vector<EditModel>{}},
      m_currentEditModel{0},
      m_cameraName{nullptr}
    {

    }
    UserWorld(const char* mainWorldName,
              const char* userWorldName)
    : m_layerCount{0},
      m_mainWorldName{mainWorldName},
      m_name{userWorldName},
      m_subWorldNames{Vector<const char*>{}},
      m_editModels{Vector<EditModel>{}},
      m_currentEditModel{0},
      m_cameraName{nullptr}
    {

    }
    ~UserWorld()
    {

    }

    class EditModel
    {
       public:
        EditModel()
        : m_positionInRenderList{0},
          m_positionInUserList{0},
          m_model{ModelModuleModel{ModelID{}, "NoModel"}}
        {

        }
        EditModel(u64_t modelPosition,
                  EditSetting& setting,
                  const ModelModuleModel& model)
        : m_positionInRenderList{modelPosition},
          m_positionInUserList{0},
          m_model{model}
        {
        switch(setting.getType())
        {
        case EditType::IsWireframe:
        m_model.setIsInWireframe(static_cast<WireFrame&>(setting).isWireFrame());
        break;
        case EditType::IsHidden:
        m_model.setIsHidden(static_cast<Hidden&>(setting).isHidden());
        break;
        default:
        break;
        }

        }
        ~EditModel()
        {

        }

        void addSetting(EditSetting& setting)
        {
        switch(setting.getType())
        {
        case EditType::IsWireframe:
        m_model.setIsInWireframe(static_cast<WireFrame&>(setting).isWireFrame());
        break;
        case EditType::IsHidden:
        m_model.setIsHidden(static_cast<Hidden&>(setting).isHidden());
        break;
        default:
        break;
        }
        }

        bool isHidden() const
        {
        return m_model.isHidden();
        }

        bool isInWireframeMode() const
        {
        return m_model.isInWireframeMode();
        }

        u64_t positionInRenderList() const
        {
        return m_positionInRenderList;
        }

        u64_t positionInUserList() const
        {
        return m_positionInUserList;
        }

       private:
        u64_t m_positionInRenderList;
        u64_t m_positionInUserList;
        ModelModuleModel m_model;
    };

    void addUserSubWorld(const char* subWorldName)
    {
    m_subWorldNames.push_back(subWorldName);
    }

    void setEditModel(u64_t modelPosition,
                      EditSetting& setting,
                      const ModelModuleModel& model)
    {
    // settingModel
    for(EditModel& editModel : m_editModels)
    {
    if(editModel.positionInRenderList() ==modelPosition)
    {
    editModel.addSetting(setting);
    return;
    }
    }

    m_editModels.push_back(EditModel{
                                      modelPosition,
                                      setting,
                                      model
                                    });


    }

    void addUserWorldDrawOrder(u32_t modelWorldPosition)
    {
    m_userWorldDrawOrder.push_back(modelWorldPosition);
    }

    void eraseWorld(u64_t positionIndex, u64_t orderInList)
    {
    u64_t timesWorldCheck = 0;
    for(i64_t j = 0; j < static_cast<i64_t>(m_userWorldDrawOrder.size()); j++)
    {
    if(orderInList == m_userWorldDrawOrder[static_cast<u64_t>(j)])
    {
    if(positionIndex == timesWorldCheck)
    {
    // std::cout << "erase order\n";
    m_userWorldDrawOrder.erase(m_userWorldDrawOrder.begin() + j);
    }
    timesWorldCheck++;
    }
    }

    }

    void setUserWorldModels(MainWorld mainWorld,
                            const VectorSharedIteratorHeap<ModelModuleModel>& models)
    {
    // [ Search through main world and find the models to set using
    //   the editModels positions ]
    
    // u32_t modelIteration = 0;
    // for(EditAddModel editModel : m_editModelsToBeAdded)
    // {
    // for(ModelWorld world : mainWorld.mainWorld())
    // {
    // for(u32_t i = world.start(); i < world.end(); i++)
    // {
    // if(models[i].m_ID == editModel.id());
    // {
    // // [ Can't create a copy without changing model, 
    // //   copys pointer ]
    // m_editModels.push_back(EditModel{model[i]});
    // modelIteration++;
    // }
    // }
    // }
    // }

    }

    void updateNextEditModel()
    {
    m_currentEditModel++;
    if(m_currentEditModel <= m_editModels.size())
    {
    m_currentEditModel = 0;
    }
    }

    void setCamera(const char* cameraName)
    {
    m_cameraName = cameraName;
    }

    const char* name() const
    {
    return m_name;
    }

    const char* mainWorldName() const
    {
    return m_mainWorldName;
    }

    Vector<const char*> subWorldNames() const
    {
    return m_subWorldNames;
    }

    Vector<u32_t> userWorldDraw() const
    {
    return m_userWorldDrawOrder;
    }

    Vector<EditModel> editModels() const
    {
    return m_editModels;
    }

    EditModel editModel() const
    {
    return m_editModels[m_currentEditModel];
    }

    const char* cameraName() const
    {
    return m_cameraName; 
    }

   public:
    u32_t m_layerCount;
    const char* m_mainWorldName;
    const char* m_name;
    Vector<const char*> m_subWorldNames;
    Vector<u32_t> m_userWorldDrawOrder;

    Vector<EditModel> m_editModels;
    u32_t m_currentEditModel;

    const char* m_cameraName;
};

class UserWorldQuery
{
    UserWorldQuery()
    : m_isInList{false},
      m_index{0}
    {
    
    }
    UserWorldQuery(bool isInList,
                   u32_t index)
    : m_isInList{isInList},
      m_index{index}
    {
    
    }
    UserWorldQuery(const UserWorldQuery& modelWorldQuery)
    : m_isInList{modelWorldQuery.isInList()},
      m_index{modelWorldQuery.index()}
    {

    }
    void operator=(const UserWorldQuery& modelWorldQuery)
    {
    m_isInList = modelWorldQuery.isInList();
    m_index = modelWorldQuery.index();
    }
    ~UserWorldQuery()
    {

    }

    bool isInList() const
    {
    return m_isInList;
    }
    u32_t index() const
    {
    return m_index;
    }
    
   private:
    bool m_isInList;
    u32_t m_index;

};


class CameraID
{
   public:
    CameraID()
    : m_ID{0}
    {

    }
    ~CameraID()
    {

    }


   private:
    i32_t m_ID;
};

class Camera
{
   public:
    Camera()
    : m_name{nullptr},
      m_ID{CameraID{}},
      m_yaw{0},
      m_pitch{0},
      m_roll{0},
      m_cameraSpeed{0.025f},
      m_sensitivity{0.25f},
      m_position{Vec3{1.0f, 1.0f, 1.0f}},
      m_front{Vec3{1.0f, 1.0f, 1.0f}},
      m_upDirection{Vec3{1.0f, 1.0f, 1.0f}}
    {

    }
    Camera(const char* name)
    : m_name{name},
      m_ID{CameraID{}},
      m_yaw{0},
      m_pitch{0},
      m_roll{0},
      m_cameraSpeed{0.025f},
      m_sensitivity{0.25f},
      m_position{Vec3{1.0f, 1.0f, 1.0f}},
      m_front{Vec3{1.0f, 1.0f, 1.0f}},
      m_upDirection{Vec3{1.0f, 1.0f, 1.0f}}
    {
      m_position = Vec3{0.0f, 0.0f, 0.0f};
      m_front = Vec3{0.0f, 0.0f, -1.0f};
      m_upDirection = Vec3{0.0f, 1.0f, 0.0f};
    }
    ~Camera()
    {

    }


    void setCameraYawValues(Pair<float, float> mouseOffsets)
    {
    float offsetX = mouseOffsets.first * m_sensitivity;
    float offsetY = -mouseOffsets.second * m_sensitivity;
    // 80 = 320 * 0.25f

    // ELLIPSE_ENGINE_LOG_INFO("Offset x: {} Offset y: {}", offsetX, offsetY);

    m_yaw += offsetX;

    if((m_pitch + offsetY  <= 90.0f) && (m_pitch + offsetY >= -90.0f))
    {
    m_pitch += offsetY;
    }

    // ELLIPSE_ENGINE_LOG_INFO("Pitch: {} Yaw: {}", m_yaw, m_pitch);
    // ELLIPSE_ENGINE_LOG_INFO("Offset x: {} Offset y: {}", offsetX, offsetY);

    }

    // [ Whenever user sets relative mouse mode off and refocuses
    //   the window will use the new position and calculate a large offset ]
    void setCameraFrontFromOffsets()
    {
    Vec3 cameraDirection = Vec3{1.0f};
      
    float yawRadians = EllipseMath::Radian{m_yaw}.radians();
    float pitchRadians = EllipseMath::Radian{m_pitch}.radians();

    cameraDirection.x = sin(yawRadians) * cos(pitchRadians);
    cameraDirection.y = sin(pitchRadians);
    cameraDirection.z = -cos(yawRadians) * cos(pitchRadians);


    m_front = EllipseMath::normalize(cameraDirection);

    }

    void setCameraSpeed(float cameraSpeed)
    {
    m_cameraSpeed = cameraSpeed;
    }

    void setPosition(Vec3 position)
    {
    m_position = position;
    }

    void setFront(Vec3 front)
    {
    m_front = front;
    }

    float cameraSpeed() const
    {
    return m_cameraSpeed;
    }

    Vec3 position() const
    {
    return m_position;
    }

    Vec3 front() const
    {
    return m_front;
    }

    Vec3 upDirection() const
    {
    return m_upDirection;
    }

    const char* name() const
    {
    return m_name;
    }

   private:
    const char* m_name;
    CameraID m_ID;

    float m_yaw;
    float m_pitch;
    float m_roll;

    float m_cameraSpeed;
    float m_sensitivity;

    Vec3 m_position;
    Vec3 m_front;
    Vec3 m_upDirection;
};

// [ Cannot add cameras of the same name ]
class CameraManager
{
   public:
    CameraManager()
    {

    }
    ~CameraManager()
    {

    }


    void addCamera(const char* name)
    {
    m_cameras.push_back(Camera{name});
    }

    void translateForward(u64_t index)
    {
    Camera camera = m_cameras[index];

    m_cameras[index].setPosition(camera.position() + (camera.front() * camera.cameraSpeed()));
    }
    
    void translateBackward(u64_t index)
    {
    Camera camera = m_cameras[index];

    m_cameras[index].setPosition(camera.position() - (camera.front() * camera.cameraSpeed()));
    
    }
    void translateLeft(u64_t index)
    {
    Camera camera = m_cameras[index];

    m_cameras[index].setPosition(camera.position() - (EllipseMath::cross(camera.front(), camera.upDirection()) * camera.cameraSpeed()));
    
    }
    void translateRight(u64_t index)
    {
    Camera camera = m_cameras[index];

    m_cameras[index].setPosition(camera.position() + (EllipseMath::cross(camera.front(), camera.upDirection()) * camera.cameraSpeed()));
    
    }

    void registerMouseUpdate(Pair<float, float> mouseOffsets)
    {
    for(u32_t i = 0; i < m_cameras.size(); i++)
    {
    m_cameras[i].setCameraYawValues(mouseOffsets);
    m_cameras[i].setCameraFrontFromOffsets();
    }

    }

    void setFronts()
    {
    // for(u32_t i = 0; i < m_cameras.size(); i++)
    // {
    // m_cameras[i].setFront(m_cameras[i].position() + Vec3{4.0f, 0.0f, 0.0f});
    // }
    }

    void setCameraPosition(u64_t index,
                           Vec3 position)
    {
    m_cameras[index].setPosition(position);
    }

    Vec3 front(u64_t index) const
    {
    return m_cameras[index].front();
    }

    Camera findCamera(const char* cameraName) const
    {
    for(u32_t i = 0; i < m_cameras.size(); i++)
    {
    if(strcmp(cameraName, m_cameras[i].name()) == 0)
    {
    return m_cameras[i];
    }
    }

    ELLIPSE_ENGINE_LOG_WARN("Camera not in list, returning invaild camara");

    return Camera{};

    }

    u64_t findCameraIndex(const char* cameraName) const
    {
    for(u64_t i = 0; i < m_cameras.size(); i++)
    {
    if(strcmp(cameraName, m_cameras[i].name()) == 0)
    {
    return i;
    }
    }

    ELLIPSE_ENGINE_LOG_WARN("Camera not in list, returning cameras size");

    return m_cameras.size();

    }

    Camera& cameraIndex(u64_t index)
    {
    return m_cameras[index];
    }

   private:
    Vector<Camera> m_cameras;
};


// [ ModelManager shouldn't set cameras logic ]

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

    struct ModelAddCollection
    {
       public:
        // [ Use imported model ]
        ModelAddCollection(
        const char* modelWorldName,
        ModelID modelID,
        const char* modelName, 
        const char* objectName,
        String vertexShader,
        String fragmentShader,
        ModelData modelData,
        UniformList uniformList,
        Mat4& model
                       )
        : m_modelWorldName{modelWorldName},
          m_models{Model{
                   modelID,
                   modelName,
                   objectName,
                   vertexShader,
                   fragmentShader,
                   modelData,
                   uniformList,
                   model
                        }
                  }
        {

        }
        ModelAddCollection(
        const char* modelWorldName,
        ModelID modelID,
        const char* modelName, 
        const char* objectName, 
        UniformList uniformList,
        Mat4& model)
        : m_modelWorldName{modelWorldName},
          m_models{Model{modelID,
                         modelName,
                         objectName,
                         uniformList,
                         model
                        }
                  }
        {

        }
        ~ModelAddCollection()
        {

        }

        struct Model
        {
          public:
           Model(ModelID modelID,
                 const char* name,
                 const char* objectName,
                 String vertexShader,
                 String fragmentShader,
                 ModelData modelData,
                 UniformList uniformList,
                 Mat4& model
                 )
           : m_modelID{modelID},
             m_name{name},
             m_objectName{objectName},
             m_vertexShader{vertexShader},
             m_fragmentShader{fragmentShader},
             m_modelData{modelData},
             m_uniformList{uniformList},
             m_model{model}
           {

           }
           Model(ModelID modelID,
                 const char* name,
                 const char* objectName,
                 UniformList uniformList,
                 Mat4& model
                 )
           : m_modelID{modelID},
             m_name{name},
             m_objectName{objectName},
             m_vertexShader{""},
             m_fragmentShader{""},
             m_modelData{ModelData{}},
             m_uniformList{uniformList},
             m_model{model}
           {
           if(objectName == nullptr)
           {
           m_objectName = "No name";

           }

           }

           ~Model()
           {

           }

           ModelID modelID() const
           {
           return m_modelID;
           }

           const char* objectName() const
           {
           return m_objectName;
           }

           String vertexShader() const
           {
           return m_vertexShader;
           }

           String fragmentShader() const
           {
           return m_fragmentShader;
           }

           ModelData modelData() const
           {
           return m_modelData;
           }

           UniformList uniformList() const
           {
           return m_uniformList;
           }

           UniformList& uniformList()
           {
           return m_uniformList;
           }

           Mat4& model()
           {
           return m_model;
           }

          private:
           ModelID m_modelID;
           const char* m_name;
           const char* m_objectName;
           String m_vertexShader;
           String m_fragmentShader;
           ModelData m_modelData;
           UniformList m_uniformList;
           Mat4& m_model;
        };


        void addModel(
        ModelID modelID,
        const char* modelName, 
        const char* objectName,
        String vertexShader,
        String fragmentShader,
        ModelData modelData,
        UniformList uniformList,
        Mat4& model
                     )
        {
        m_models.push_back(Model{modelID,
                                 modelName,
                                 objectName,
                                 vertexShader,
                                 fragmentShader,
                                 modelData,
                                 uniformList,
                                 model}
                          );
        }

        void addModel(ModelID modelID,
                      const char* modelName, 
                      const char* objectName,
                      UniformList uniformList,
                      Mat4& model)
        {
        m_models.push_back(Model{modelID,
                                 modelName,
                                 objectName,
                                 uniformList,
                                 model}
                          );
        }

        void setWorldName(const char* name)
        {
        m_modelWorldName = name;
        }

        const char* modelWorldName() const
        {
        return m_modelWorldName;
        }

        Vector<Model> models() const
        {
        return m_models;
        }

        Vector<Model>& models()
        {
        return m_models;
        }

       private:
        const char* m_modelWorldName;
        Vector<Model> m_models;
    };


    virtual void initLayerModule() override = 0;
    virtual void onUpdateLayer() override = 0;

    virtual void addModel(ModelID& modelID,
                          const char* modelName,
                          const char* objectName,
                          String vertexShader,
                          String fragmentShader,
                          String importPath,
                          UniformList uniformList
                          ) = 0;

    // virtual void addCube(ModelID& modelID,
    //                      const char* modelName,
    //                      UniformList uniformList) = 0;
    
    virtual void translateModel(ModelID modelID, Vec3 translationAmount) = 0;

    virtual void rotateModel(ModelID modelID, float radians, Vec3 rotationAxis) = 0;

    virtual void scaleModel(ModelID modelID, Vec3 scalarAmount) = 0;

    virtual void addWorld(const char* name) = 0;

    virtual void addSubWorld(const char* subWorldName, const char* mainWorldName) = 0;

    virtual void addUserWorld(const char* userWorldName, const char* mainWorldName) = 0;
    virtual void addUserSubWorld(const char* subWorldName, const char* userWorldName) = 0;

    virtual void startWorld(const char* name) = 0;
    virtual void endWorld() = 0;

    virtual void startSubWorld(const char* name) = 0;
    virtual void endSubWorld() = 0;

    virtual void removeModel(ModelID modelID) = 0;

    virtual void setWireframeMode(ModelID modelID, const char* userWorld) = 0;

    virtual void removeWorldLastPositions() = 0;

    virtual void worldLastPositionAddWorld(u32_t worldPosition) = 0;

    virtual void worldLastPositionUpdate(u32_t worldPosition) = 0;

    virtual u32_t worldLastPosition(u32_t worldPosition) = 0;


    virtual void addUserCamera(const char* userWorldName,
                               const char* cameraName) = 0;

    virtual void registerMouseUpdate(Pair<float, float> mouseOffsets) = 0;

    virtual void translateCameraForward(const char* cameraName) = 0;
    virtual void translateCameraBackward(const char* cameraName) = 0;
    virtual void translateCameraLeft(const char* cameraName) = 0;
    virtual void translateCameraRight(const char* cameraName) = 0;
    virtual void setCameraPosition(const char* cameraName,
                                   Vec3 position) = 0;

    virtual Camera retrieveCamera(const char* cameraName) = 0;
    // virtual Camera& retrieveCameraIndex(const char* cameraName) = 0;

    virtual u64_t findCameraIndex(const char* cameraName) = 0;
    virtual Camera& cameraIndex(u64_t index) = 0;

    virtual void setViewspace(Viewspace viewspace) = 0;

    virtual void setDifferentInViewspace(float viewspaceWidth,
                                         float viewspaceHeight,
    float originalWindowWidth,
    float originalWindowHeight) = 0;
    
    virtual ModelWorldQuery modelWorldFind(u32_t worldPosition, const char* mainWorldName) = 0;
    virtual ModelWorldQuery modelWorldFindPrevious(u32_t worldPosition, const char* mainWorldName) = 0;

    // virtual UserWorldQuery userWorldFind(const char* userWorldName, const char* mainWorldName) = 0;

    virtual void clearModelAddCollection() = 0;

    virtual void clearModelsToBeRemoved() = 0;

    virtual void queryUserWorlds() = 0;
    virtual void queryMainWorlds() = 0;

    virtual void queryUserWorld(const char* userWorldName) = 0;
    virtual void queryMainWorld(const char* mainWorldName) = 0;

    CREATE_FUNC_CALLBACK_INTERFACE(addModel, void(ModelID& modelID,
                                                  const char* modelName,
                                                  const char* objectName,
                                                  String vertexShader,
                                                  String fragmentShader,
                                                  String importPath,
                                                  UniformList uniformList))
    CREATE_FUNC_CALLBACK_INTERFACE(removeModel, void(ModelID modelID))
    CREATE_FUNC_CALLBACK_INTERFACE(translateModel, void(ModelID modelID, Vec3 translationAmount))
    CREATE_FUNC_CALLBACK_INTERFACE(rotateModel, void(ModelID modelID, float radians, Vec3 rotationAxis))
    CREATE_FUNC_CALLBACK_INTERFACE(scaleModel, void(ModelID modelID, Vec3 scalarAmount))
    CREATE_FUNC_CALLBACK_INTERFACE(startWorld, void(const char* name))
    CREATE_FUNC_CALLBACK_INTERFACE(endWorld, void())
    CREATE_FUNC_CALLBACK_INTERFACE(startSubWorld, void(const char* name))
    CREATE_FUNC_CALLBACK_INTERFACE(endSubWorld, void())

    // [ Remove the two functions isHiddenModel, isInWireframeModel ]
    virtual bool isHiddenModel(u64_t modelPosition) const = 0;
    virtual bool isInWireframeModel(u64_t modelPosition) const = 0;


    virtual Vector<ModelAddCollection> modelAddCollection() const = 0;
    virtual Vector<ModelAddCollection>& modelAddCollection() = 0;

    virtual CameraManager& cameraManager() = 0;

    virtual Vector<MainWorld> mainWorlds() const = 0;

    virtual Vector<MainWorld> mainWorldsPrevious() const = 0;

    virtual MainWorld mainWorld(const char* name) const = 0;
    virtual ModelWorld modelWorld(u32_t modelWorldPosition) const = 0;
    virtual ModelWorld modelWorld(u32_t modelWorldPosition, const char* worldName) const = 0;
    // virtual ModelWorld modelWorldPrevious(u32_t modelWorldPosition, const char* worldName) const = 0;
    
    // [ Create a modelWorld& modelWorld() for modelWorldPosition only ]
    virtual ModelWorld& modelWorld(u32_t modelWorldPosition, const char* worldName) = 0;
    virtual ModelWorld& modelWorldPrevious(u32_t modelWorldPosition, const char* worldName) = 0;
    virtual ModelWorld& modelWorldIndex(ModelWorldQuery modelWorldQuery) = 0;
    virtual ModelWorld& modelWorldIndexPrevious(ModelWorldQuery modelWorldQuery) = 0;

    virtual Vector<UserWorld> userWorlds() const = 0;
//
    // [ Might have to define userWorlds()& to find
      // and set user worlds ]
    virtual Vector<UserWorld> userWorldsPrevious() const = 0;

    virtual const VectorSharedIteratorHeap<ModelModuleModel>& modelModuleModels() const = 0;

    virtual Vector<u32_t> modelsToBeRemovedIndicies() const = 0;

    class ModelWorldDrawOrder;

    virtual ModelWorldDrawOrder modelWorldDrawOrder() const = 0;

    static SharedPtr<ModelManagerModule> createModelManagerModule();

   public:
    class ModelWorldDrawOrder
    {
       public:
        ModelWorldDrawOrder()
        : m_layerSize{0},
          m_currentLayer{0}
        {

        }
        ~ModelWorldDrawOrder()
        {

        }

        void initModelWorldDrawOrder()
        {
        m_layerSize++;
        m_modelWorldLayerOrder.addWorld();
        }

        void addWorld(u32_t modelPosition)
        {
        m_modelWorldLayerOrder.m_modelWorldLayerOrder[m_currentLayer].m_modelWorldDrawOrder.push_back(modelPosition);
        }

        void update()
        {
        m_currentLayer++;
        if(m_currentLayer == m_layerSize)
        {
        m_currentLayer = 0;
        }
        }

        u64_t layerSize() const
        {
        return m_layerSize;
        }

        u32_t currentLayer() const
        {
        return m_currentLayer;
        }

        Vector<u32_t> modelWorldDrawOrder() const
        {
        return m_modelWorldLayerOrder.m_modelWorldLayerOrder[m_currentLayer].m_modelWorldDrawOrder;
        }

       private:
        class ModelDrawLayerOrder
        {
           public:
            Vector<u32_t> m_modelWorldDrawOrder;
        };

        struct ModelDrawOrderList
        {
           public:
            void addWorld()
            {
            m_modelWorldLayerOrder.push_back(ModelDrawLayerOrder{});
            }

           public:
            Vector<ModelDrawLayerOrder> m_modelWorldLayerOrder;
        };
        
        u64_t m_layerSize;
        u32_t m_currentLayer;
        ModelDrawOrderList m_modelWorldLayerOrder;
    };

   protected:
    virtual void importModel(String modelImportPath) = 0;

    virtual void onUpdateModelMatrices() = 0;

    virtual void translateModelInModelList(Mat4& model, Vec3 translationAmount) = 0;
    virtual void rotateModelInModelList(Mat4& model, float radians, Vec3 rotationAxis) = 0;
    virtual void scaleModelInModelList(Mat4& model, Vec3 scalarAmount) = 0;
};

}   // namespace Ellipse
