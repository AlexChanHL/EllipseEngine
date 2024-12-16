
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
    : m_defaultWorld{ModelWorld{"ModelManagerDefaultWorld", 0, 0}},
      m_randomRemoveLast{int32_t(pow(10,2))},
      m_modelOrderCount{0},
      m_modelWorldCount{0},
      m_modelWorldDrawOrder{}
    {
    setName("ModelManagerLayerModule");
    }
  
    ~ModelManagerModuleImpl()
    {

    }
 
    virtual void initLayerModule() override
    {
    m_modelWorldDrawOrder.initModelWorldDrawOrder();
    m_layerTracker.initLayer();
    m_modelWorlds.initLayer();
    m_userWorlds.initLayer();
    m_modelLayers.push_back(ModelLayer{});
    m_modelLayersIterator = m_modelLayers.begin();
    m_previousModelLayersIterator = m_modelLayers.begin();
    }


    // [ Updating the next layer is using after
    //   update call ]

    virtual void onUpdateLayer() override
    {
    onUpdateModelMatrices();

    // for(ModelLayer& modelLayer : m_modelLayers)
    // {
    // for(ModelViewspace& modelViewspace : modelLayer.m_modelViewspaces)
    // {
    // // std::cout << "Model Layer Viewspace posX: " << modelViewspace.m_viewspace.m_posX << '\n'; 
    // }
    // }

    m_layerTracker.updateLayer();
    m_modelWorlds.updateLayer(m_layerTracker);
    m_userWorlds.updateLayer(m_layerTracker);
    m_modelWorldDrawOrder.update();
    concatnateWorlds();

    m_modelLayersIterator++;
    m_previousModelLayersIterator = m_modelLayersIterator - 1;
    if(m_modelLayersIterator == m_modelLayers.end())
    {
    m_modelLayersIterator = m_modelLayers.begin();
    }

    }

    // Render
    // +=======+==================+=============+
    // | 1     | 2                | 1           |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // | 0 | 1 | 2 | 3 | 4 | 5 |  | 6 | 7 | 8 | |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // 
    // Render remove World 2, first model
    // +=======+==================+=============+
    // | 1     | 2                | 1           |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // | 0 | 1 | 2 | 3 | 4 | 5 |  | 6 | 7 | 8 | |
    // +===+===+===+===+===+===+==+===+===+===+=+
    //
    //                    |
    //                   \|/
    //
    // +=======+==================+=============+
    // | 1     | 2                | 1           |
    // +===+===+===+===+===+===+==+===+===+===+=+
    // | 0 | 1 | 2 | 3 | 4 |   |  | 5 | 6 | 7 | |
    // +===+===+===+===+===+===+==+===+===+===+=+
      


    // User world 1
    // +===+===+===+
    // | 1 | 3 |   |
    // +===+===+===+
      
    // User world 2
    // +===+===+===+
    // | 1 | 2 | 3 |
    // +===+===+===+
      
    // 1
    // +===+===+===+
    // | 1 | 3 |   |
    // +===+===+===+
    // | 0 | 1 |   |
    // +===+===+===+
      
    // 2
    // +===+===+===+
    // | 1 | 3 | 2 |
    // +===+===+===+
    // | 0 | 1 | 2 |
    // +===+===+===+



    virtual void addModel(ModelID& modelID,
                          const char* modelName, 
                          String vertexShader,
                          String fragmentShader,
                          VerticiesData verticies,
                          UniformList uniformList
                          ) override
    {
    ModelWorld queryWorld = m_modelWorlds.currentWorld();

    for(u64_t i = 0; i < queryWorld.modelPositionCount(); i++)
    {
    for(u32_t j = queryWorld.start(); j < queryWorld.end(); j++)
    {
    if(modelID == m_modelModuleModels[j].m_modelID)
    {
    std::cout << "Adding already model\n";
    return;
    }

    }
    queryWorld.updateNextSubWorld();
    }

    modelID.m_ID = m_randomRemoveLast.chooseRandomVal();
    // [ Check so don't add two models with the same ID ]
    if(m_subModelMangers.empty() || strcmp(m_modelWorlds.previousWorld().name(), m_modelWorlds.currentWorld().name()) != 0)
        // || strcmp(m_subModelMangers[m_subModelMangers.size() - 1].modelWorldName(), m_modelWorlds.currentWorld().name()) != 0)
    {

    u32_t modelWorldPosition = 0;


    // [ Check if main world is same as default world
    //   and delete all the check here in this ]

    // Comparing to where the world is in the list as well as
    // checking if the world actually exists
    bool modelWorldFound = false;
    MainWorld queryMainWorld = m_modelWorlds.mainWorld(m_modelWorlds.currentMainWorld().name());

    if(strcmp(queryMainWorld.mainWorld().name(), m_modelWorlds.currentWorld().name()) == 0)
    {
    modelWorldPosition = queryMainWorld.mainWorld().orderInList();
    modelWorldFound = true;
    }

    if(!modelWorldFound)
    {
    auto subWorldIt = queryMainWorld.subWorlds().begin();
    for(; subWorldIt != queryMainWorld.subWorlds().end(); subWorldIt++)
    {
    if(strcmp(m_modelWorlds.currentWorld().name(), subWorldIt->name()) == 0)
    {
    modelWorldPosition = subWorldIt->orderInList();
    modelWorldFound = true;
    break;
    }
    }

    // The user has not specified the world to add the model to
    if(!modelWorldFound)
    {
    return;
    }

    }

    // Checking if the world is different and no model has been
    // added to it before
    // [ Remove isDifferentWorld, no need renderModule
    //   uses modelModule worlds and doesn't ]
 //    bool isDifferentWorld = true;
 //    for(u64_t i = 0; i < m_modelWorlds.addWorlds().size(); i++)
 //    {
 //    if(modelWorldPosition == m_modelWorlds.addWorlds()[i])
 //    {
 //    isDifferentWorld = false;
 //    }
 //    }
 // 
 //    if(isDifferentWorld)
 //    {
 //    m_modelWorlds.addModelDifferent(modelWorldPosition);
 //    }

    m_userWorlds.addDrawOrder(modelWorldPosition,
                              m_modelWorlds.currentMainWorld().name(),
                              m_modelWorlds.currentWorld().name());

    m_modelWorlds.addModelBeginPosition(m_modelOrderCount, m_modelWorlds.currentWorld().name());

    m_modelWorlds.addWorldAddOrder(modelWorldPosition, m_modelWorlds.currentMainWorld().name());


    m_modelModuleModels.pushBack(ModelModuleModel{
     modelID,
     modelName
                                                 }
    );

    m_modelOrderCount++;


    m_modelWorlds.addModelEndPosition(m_modelOrderCount, m_modelWorlds.currentWorld().name());

    m_subModelMangers.push_back(
     SubModelManager{
      m_modelWorlds.currentWorld().name(),
      // isDifferentWorld, 
      modelID,
      modelName,
      vertexShader,
      fragmentShader,
      verticies,
      uniformList,
      m_modelModuleModels[m_modelModuleModels.size() - 1].m_model
       }
                              );

    // [ Set the current world end position rather
    //   than copying the new world ]
    ModelWorld worldAfterAddModel = m_modelWorlds.modelWorld(modelWorldPosition);
    m_modelWorlds.setCurrentWorld(worldAfterAddModel);
    if(strcmp(m_modelWorlds.currentWorld().name(), m_modelWorlds.currentMainWorld().name()) == 0)
    {
    m_modelWorlds.setCurrentMainWorld(worldAfterAddModel);
    }

    m_modelWorlds.setPreviousWorld(worldAfterAddModel);

    return; 
    }

    m_modelModuleModels.pushBack(ModelModuleModel{
     modelID,
     modelName
                                                 }
    );

    m_modelOrderCount++;

    m_subModelMangers[m_subModelMangers.size() - 1].addModel(
       modelID,
       modelName,
       vertexShader,
       fragmentShader,
       verticies,
       uniformList,
       m_modelModuleModels[m_modelModuleModels.size() - 1].m_model 
      );

    m_modelWorlds.addModelEndPosition(m_modelOrderCount, m_modelWorlds.currentWorld().name());
    // update current world
    ModelWorld worldAfterAddModel = m_modelWorlds.modelWorld(m_modelWorlds.currentWorld().orderInList());
    m_modelWorlds.setCurrentWorld(worldAfterAddModel);
    if(strcmp(m_modelWorlds.currentWorld().name(), m_modelWorlds.currentMainWorld().name()) == 0)
    {
    m_modelWorlds.setCurrentMainWorld(worldAfterAddModel);
    }
    }

    virtual void translateModel(ModelID modelID, Vec3 translationAmount) override
    {
    // // [ Change the nam ]
      
    ModelWorld queryWorld = m_modelWorlds.currentWorld();


    for(u64_t i = 0; i < queryWorld.modelPositionCount(); i++)
    {
    for(u64_t j = queryWorld.start(); j < queryWorld.end(); j++)
    {
    if(modelID == m_modelModuleModels[j].m_modelID)
    {
    // std::cout << "translate amount\n";
    m_modelModuleModels[j].setTranslationAmount(translationAmount);
    m_modelModuleModels[j].setIsModified(true);
    i = queryWorld.modelPositionCount();
    break;
    }
    }
    queryWorld.updateNextSubWorld();
    }

    }

    virtual void rotateModel(ModelID modelID, float radians, Vec3 rotationAxis) override
    {
    ModelWorld queryWorld = m_modelWorlds.currentWorld();


    for(u64_t i = 0; i < queryWorld.modelPositionCount(); i++)
    {
    for(u64_t j = queryWorld.start(); j < queryWorld.end(); j++)
    {
    if(modelID == m_modelModuleModels[j].m_modelID)
    {
    m_modelModuleModels[j].setRotationAmount(radians, rotationAxis);
    m_modelModuleModels[j].setIsModified(true);
    i = queryWorld.modelPositionCount();
    break;
    }
    }
    queryWorld.updateNextSubWorld();
    }

    }

    virtual void scaleModel(ModelID modelID, Vec3 scalarAmount) override
    {
    ModelWorld queryWorld = m_modelWorlds.currentWorld();


    for(u64_t i = 0; i < queryWorld.modelPositionCount(); i++)
    {
    for(u64_t j = queryWorld.start(); j < queryWorld.end(); j++)
    {
    if(modelID == m_modelModuleModels[j].m_modelID)
    {
    m_modelModuleModels[j].setScalarAmount(scalarAmount);
    m_modelModuleModels[j].setIsModified(true);
    i = queryWorld.modelPositionCount();
    break;
    }
    }
    queryWorld.updateNextSubWorld();
    }

    }

    // Worlds with the same name cannot be added
    // Worlds are drawn independent of what order
    virtual void addWorld(const char* name) override
    {

    // // [ Use current main world to find where the world is and if a
    //      copy already exists ]
    // for(auto& world : m_modelWorlds.modelWorlds())
    // {
    // if(strcmp(name, world.name()) == 0)
    // {
    // return;
    // }
    // }

    m_modelWorlds.addWorld(name, m_modelWorldCount);
    m_modelWorldCount++;
    }

    // [ Check if adding sub world of the same name ]
    virtual void addSubWorld(const char* subWorldName, const char* mainWorldName) override
    {
    for(MainWorld& mainWorld : m_modelWorlds.mainWorlds())
    {
    if(strcmp(mainWorldName, mainWorld.mainWorld().name()))
    {
    for(ModelWorld& world : mainWorld.subWorlds())
    {
    if(strcmp(subWorldName, world.name()) == 0)
    {
    return;
    }
    }
    }
    }

    m_modelWorlds.addSubWorld(subWorldName, m_modelWorldCount, mainWorldName);
    m_modelWorldCount++;
    }

    // [ Check if adding user world of the same name ]
    virtual void addUserWorld(const char* userWorldName, const char* mainWorldName) override
    {
    m_userWorlds.addMainWorld(userWorldName, mainWorldName, m_modelWorlds);
    }

    virtual void addUserSubWorld(const char* subWorldName, const char* userWorldName) override
    {
    m_userWorlds.addUserSubWorld(subWorldName, userWorldName);
    }

    virtual void startWorld(const char* name) override
    {
    for(u32_t i=0;i<m_modelWorlds.mainWorlds().size();i++)
    {
    if(strcmp(name, m_modelWorlds.mainWorlds()[i].mainWorld().name()) == 0)
    {
    m_modelWorlds.setCurrentMainWorld(m_modelWorlds.mainWorlds()[i].mainWorld());
    m_modelWorlds.setCurrentWorld(m_modelWorlds.mainWorlds()[i].mainWorld());
    }
    }
   
    }

    // [ Use a default world ]
    virtual void endWorld() override
    {
    m_modelWorlds.setCurrentMainWorld(m_defaultWorld);
    m_modelWorlds.setCurrentWorld(m_defaultWorld);
    }

    virtual void startSubWorld(const char* name) override
    {
    for(u32_t i = 0; i < m_modelWorlds.mainWorlds().size(); i++)
    {
    if(strcmp(m_modelWorlds.mainWorlds()[i].mainWorld().name(),
              m_modelWorlds.currentMainWorld().name()) == 0)
    {
    for(u32_t j = 0;
         j < m_modelWorlds.mainWorlds()[i].subWorlds().size();
         j++)
    {
    if(strcmp(name,
              m_modelWorlds.mainWorlds()[i].subWorlds()[j].name()) == 0)
    {
    m_modelWorlds.setCurrentWorld(m_modelWorlds.mainWorlds()[i].subWorlds()[j]);
    }
    }
    }
    }

    }
    virtual void endSubWorld() override
    {
    m_modelWorlds.setCurrentWorld(m_modelWorlds.currentMainWorld());
    }

    // [ Remove model is broken and sometimes removed models
    //   function but the user worlds does not update the 
    //   new world and won't show on queryUserWorld ]
    virtual void removeModel(ModelID modelID) override
    {
    ModelWorld queryWorld = m_modelWorlds.currentWorld();
    Pair<u64_t, ModelWorld> modelWorldRemovedPosition;

    for(u64_t i = 0; i < queryWorld.modelPositionCount(); i++)
    {
    for(u32_t j = queryWorld.start(); j < queryWorld.end(); j++)
    {
    if(modelID == m_modelModuleModels[j].m_modelID)
    {
    m_modelModuleModels.erase(m_modelModuleModels.begin() + j);
    m_modelsToBeRemovedIndicies.push_back(j);
    m_modelOrderCount--;
    modelWorldRemovedPosition.first = i;
    modelWorldRemovedPosition.second = queryWorld;


    removeWorldLastPositions();

    for(u64_t k = 0; k < m_modelWorlds.addWorldAddOrder().size(); k++)
    {
    u32_t addWorldPosition = m_modelWorlds.addWorldAddOrder()[k].position();
    ModelWorldQuery modelWorldQuery = modelWorldFind(addWorldPosition, m_modelWorlds.addWorldAddOrder()[k].mainWorldName());

    worldLastPositionAddWorld(addWorldPosition);

    // for(u32_t iterateUpdateWorld = 0; iterateUpdateWorld < modelWorldQuery.updateAmount(); iterateUpdateWorld++)
    // {
    // m_userWorlds.worldLastPositionUpdate(worldPositionQuery);
    // }
              
    // std::cout << modelWorldIndex(modelWorldQuery).modelPosition(worldLastPosition(addWorldPosition)).second << '\n';

    if(modelWorldQuery.isInList())
    {
    if(j < modelWorldIndex(modelWorldQuery).modelPosition(worldLastPosition(addWorldPosition)).second)
    {
    modelWorldIndex(modelWorldQuery).decrementEnd(worldLastPosition(addWorldPosition));
    m_modelWorlds.setCurrentWorld(modelWorldIndex(modelWorldQuery));
    if(strcmp(m_modelWorlds.currentMainWorld().name(), m_modelWorlds.currentWorld().name()) == 0)
    {
    m_modelWorlds.setCurrentMainWorld(modelWorldIndex(modelWorldQuery));
    }
    worldLastPositionUpdate(addWorldPosition);

    for(u64_t worldIteration = k + 1; worldIteration < m_modelWorlds.addWorldAddOrder().size(); worldIteration++)
    {
    addWorldPosition = m_modelWorlds.addWorldAddOrder()[worldIteration].position();
    modelWorldQuery = modelWorldFind(addWorldPosition, m_modelWorlds.addWorldAddOrder()[worldIteration].mainWorldName());
    modelWorldIndex(modelWorldQuery).decrementStart(worldLastPosition(addWorldPosition));
    modelWorldIndex(modelWorldQuery).decrementEnd(worldLastPosition(addWorldPosition));

    worldLastPositionUpdate(addWorldPosition);
    }
    break;

    }
    }

    worldLastPositionUpdate(addWorldPosition);

    }
    break;
            
    }
    }
    queryWorld.updateNextSubWorld();
    }


    // Removing worlds that don't have models inside
    // [ Found the removed model so check the list ]
    for(u64_t i = 0; i < m_modelWorlds.mainWorlds().size(); i++)
    {
    if(strcmp(m_modelWorlds.mainWorlds()[i].mainWorld().name(), m_modelWorlds.currentMainWorld().name()) == 0)
    {
    for(u64_t j = 0; j < m_modelWorlds.mainWorlds()[i].mainWorld().modelPositions().size(); j++)
    {
    if(m_modelWorlds.mainWorlds()[i].mainWorld().modelPositions()[j].first == m_modelWorlds.mainWorlds()[i].mainWorld().modelPositions()[j].second)
    {
    m_modelWorlds.mainWorlds()[i].mainWorld().erasePosition(j);
    m_modelWorlds.eraseAddWorld(modelWorldRemovedPosition.first, modelWorldRemovedPosition.second.orderInList());
    m_userWorlds.eraseWorldOrder(j, m_modelWorlds.mainWorlds()[i].mainWorld().orderInList());
    m_modelWorlds.setPreviousWorld(m_defaultWorld);
    break;
    }
    }


    for(u64_t j = 0; j < m_modelWorlds.mainWorlds()[i].subWorlds().size(); j++)
    {
    for(u64_t k = 0; k < m_modelWorlds.mainWorlds()[i].subWorlds()[j].modelPositions().size(); k++)
    {
    if(m_modelWorlds.mainWorlds()[i].subWorlds()[j].modelPositions()[k].first 
       == m_modelWorlds.mainWorlds()[i].subWorlds()[j].modelPositions()[k].second)
    {
    m_modelWorlds.mainWorlds()[i].subWorlds()[j].erasePosition(k);
    m_modelWorlds.eraseAddWorld(modelWorldRemovedPosition.first, modelWorldRemovedPosition.second.orderInList());
    m_userWorlds.eraseWorldOrder(k, m_modelWorlds.mainWorlds()[i].subWorlds()[j].orderInList());
    m_modelWorlds.setPreviousWorld(m_defaultWorld);
    break;
    }
    }
    }
    }
    }




 
    }

    virtual void setWireframeMode(ModelID modelID, const char* userWorld) override
    {
    for(UserWorld& world : m_userWorlds.userWorlds())
    {
    if(strcmp(world.name(), userWorld) == 0)
    {
    for(u32_t i = 0; i < world.userWorldDraw().size(); i ++)
    {
    for(u64_t j = m_modelWorlds.modelWorld(world.userWorldDraw()[i]).start();
     j < m_modelWorlds.modelWorld(world.userWorldDraw()[i]).end();
     j++)
    {
    if(m_modelModuleModels[j].m_modelID == modelID)
    {
    // Finding model and setting wireframe
    WireFrame wireframe{true};
    world.setEditModel(j, wireframe, m_modelModuleModels[j]);
    }
    }

    break;
    }
    }
    }

    }

    virtual void removeWorldLastPositions() override
    {
    m_userWorlds.removeWorldLastPositions();
    }

    virtual void worldLastPositionAddWorld(u32_t worldPosition) override
    {
    m_userWorlds.worldLastPositionAddWorld(worldPosition);

    }

    virtual void worldLastPositionUpdate(u32_t worldPosition) override
    {
    m_userWorlds.worldLastPositionUpdate(worldPosition);

    }

    virtual u32_t worldLastPosition(u32_t worldPosition) override
    {
    return m_userWorlds.worldLastPosition(worldPosition);

    }

    virtual void setViewspace(Viewspace viewspace) override
    {
    m_currentViewspace = viewspace;
    }

    virtual void setDifferentInViewspace(float viewspaceWidth,
                                         float viewspaceHeight,
                                         float originalWindowWidth,
                                         float originalWindowHeight) override;

    virtual ModelWorldQuery modelWorldFind(u32_t worldPosition, const char* mainWorldName) override
    {
    return m_modelWorlds.modelWorldFind(worldPosition, mainWorldName);
    }
    virtual ModelWorldQuery modelWorldFindPrevious(u32_t worldPosition, const char* mainWorldName) override
    {
    return m_modelWorlds.modelWorldFindPrevious(worldPosition, mainWorldName);
    }

    virtual void clearSubModelManagers() override
    {
    m_subModelMangers.clear();
    }

    virtual void clearModelsToBeRemoved() override
    {
    m_modelsToBeRemovedIndicies.clear();
    }

    virtual void queryUserWorlds() override
    {
    for(u64_t i = 0; i < userWorlds().size(); i++)
    {
    ELLIPSE_ENGINE_LOG_INFO("{}", userWorlds()[i].name());

    removeWorldLastPositions();

    for(u64_t j = 0; j < userWorlds()[i].userWorldDraw().size(); j++)
    {
    u32_t worldPositionIndex = userWorlds()[i].userWorldDraw()[j];

    ELLIPSE_ENGINE_LOG_INFO("{} :", modelWorld(worldPositionIndex, userWorlds()[i].mainWorldName()).name());
    ELLIPSE_ENGINE_LOG_INFO("Start: {} End: {}", modelWorld(worldPositionIndex, userWorlds()[i].mainWorldName()).modelPosition(worldLastPosition(worldPositionIndex)).first, modelWorld(worldPositionIndex, userWorlds()[i].mainWorldName()).modelPosition(worldLastPosition(worldPositionIndex)).second);

    worldLastPositionUpdate(userWorlds()[i].userWorldDraw()[j]);
    }
    }

    }

    virtual void queryMainWorlds() override
    {
    for(u64_t i = 0; i < mainWorlds().size(); i++)
    {
    for(u64_t j = 0; j < mainWorlds()[i].mainWorld().modelPositions().size(); j++)
    {
    // ModelWorld world = mainWorlds()[i].mainWorld();
    // std::cout << world.name() << '\n';
    std::cout << mainWorlds()[i].mainWorld().name() << '\n';
    std::cout << "Start: " << mainWorlds()[i].mainWorld().modelPositions()[j].first << " End: ";
    std::cout << mainWorlds()[i].mainWorld().modelPositions()[j].second << '\n';
    }
    }

    }

    virtual void queryUserWorld(const char*
                                userWorldName) override
    {
    for(u64_t i = 0; i < userWorlds().size(); i++)
    {
    if(strcmp(userWorlds()[i].name(), userWorldName) == 0)
    {

    removeWorldLastPositions();

    ELLIPSE_ENGINE_LOG_INFO("{}", userWorldName);


    ELLIPSE_ENGINE_LOG_INFO("All world names: ");
    ELLIPSE_ENGINE_LOG_INFO("Main world: {}", userWorlds()[i].mainWorldName());
    for(const char* subWorldName : userWorlds()[i].subWorldNames())
    {
    ELLIPSE_ENGINE_LOG_INFO("{}", subWorldName);
    }

    for(u64_t j = 0; j < userWorlds()[i].userWorldDraw().size(); j++)
    {

    u32_t worldPositionIndex = userWorlds()[i].userWorldDraw()[j];
    ModelWorldQuery modelWorldQuery = modelWorldFind(worldPositionIndex, userWorlds()[i].mainWorldName());

    ELLIPSE_ENGINE_LOG_INFO("{}", modelWorldIndex(modelWorldQuery).name());
    ELLIPSE_ENGINE_LOG_INFO("Start: {} End: {}",
                            modelWorldIndex(modelWorldQuery).modelPosition(worldLastPosition(worldPositionIndex)).first,
                            modelWorldIndex(modelWorldQuery).modelPosition(worldLastPosition(worldPositionIndex)).second);


    worldLastPositionUpdate(userWorlds()[i].userWorldDraw()[j]);
    }
    }
    }

    }

    virtual void queryMainWorld(const char* mainWorldName) override
    {
    for(u64_t i = 0; i < mainWorlds().size(); i++)
    {
    if(strcmp(mainWorlds()[i].mainWorld().name(), mainWorldName) == 0)
    {
    for(u64_t j = 0; j < mainWorlds()[i].mainWorld().modelPositions().size(); j++)
    {
    ELLIPSE_ENGINE_LOG_INFO("{}", mainWorlds()[i].mainWorld().name());
    ELLIPSE_ENGINE_LOG_INFO("Start: {} End: {}",
                            mainWorlds()[i].mainWorld().modelPositions()[j].first,
                            mainWorlds()[i].mainWorld().modelPositions()[j].second);
    }
    }
    }

    }

    virtual bool isHiddenModel(u64_t modelPosition) const override
    {
    return m_modelModuleModels[modelPosition].isHidden();
    }

    virtual bool isInWireframeModel(u64_t modelPosition) const override
    {
    return m_modelModuleModels[modelPosition].isInWireframeMode();
    }

    virtual std::vector<SubModelManager> subModelManagers() const override
    {
    return m_subModelMangers;
    }

    virtual Vector<MainWorld> mainWorlds() const override
    {
    return m_modelWorlds.mainWorlds();
    }

    virtual Vector<MainWorld> mainWorldsPrevious() const override
    {
    return m_modelWorlds.mainWorldsPrevious();
    }

    // [ Make the mainWorlds("World") be a
    //   modelManager only ]
    virtual MainWorld mainWorld(const char* name) const override
    {
    return m_modelWorlds.mainWorld(name);
    }
    virtual ModelWorld modelWorld(u32_t modelWorldPosition) const override
    {
    return m_modelWorlds.modelWorld(modelWorldPosition);
    }
    virtual ModelWorld modelWorld(u32_t modelWorldPosition, const char* worldName) const override
    {
    return m_modelWorlds.modelWorld(modelWorldPosition, worldName);
    }
    virtual ModelWorld& modelWorld(u32_t modelWorldPosition, const char* worldName) override
    {
    return m_modelWorlds.modelWorld(modelWorldPosition, worldName);
    }
    virtual ModelWorld& modelWorldPrevious(u32_t modelWorldPosition, const char* worldName) override
    {
    return m_modelWorlds.modelWorldPrevious(modelWorldPosition, worldName);
    }
    virtual ModelWorld& modelWorldIndex(ModelWorldQuery modelWorldQuery) override
    {
    return m_modelWorlds.modelWorldIndex(modelWorldQuery);
    }
    virtual ModelWorld& modelWorldIndexPrevious(ModelWorldQuery modelWorldQuery) override
    {
    return m_modelWorlds.modelWorldIndexPrevious(modelWorldQuery);
    }

    virtual Vector<UserWorld> userWorlds() const override
    {
    return m_userWorlds.userWorlds();
    }

    virtual Vector<UserWorld> userWorldsPrevious() const override
    {
    return m_userWorlds.userWorldsPrevious();
    }

    virtual const VectorSharedIteratorHeap<ModelModuleModel>& modelModuleModels() const override
    {
    return m_modelModuleModels;
    }

    virtual Vector<u32_t> modelsToBeRemovedIndicies() const override
    {
    return m_modelsToBeRemovedIndicies;
    }

    virtual std::vector<ModelLayer>& modelLayers() override
    {
    return m_modelLayers;
    } 

    virtual std::vector<ModelLayer>::iterator previousModelLayersIterator() override
    {
    return m_previousModelLayersIterator;
    }

    virtual ModelWorldDrawOrder modelWorldDrawOrder() const override
    {
    return m_modelWorldDrawOrder;
    }

    SharedPtr<ModelManagerModule> createModelManagerModule();

   private:
    virtual void onUpdateModelMatrices() override
    {
    for(u64_t i = 0; i < m_modelModuleModels.size(); i++)
    {
    if(m_modelModuleModels[i].isModified())
    {
    m_modelModuleModels[i].resetModelMatrix();
          
    translateModelInModelList(m_modelModuleModels[i].model(), m_modelModuleModels[i].translationAmount());
    rotateModelInModelList(m_modelModuleModels[i].model(), m_modelModuleModels[i].rotationAmount().m_radians, m_modelModuleModels[i].rotationAmount().m_rotationAxis);
    scaleModelInModelList(m_modelModuleModels[i].model(), m_modelModuleModels[i].scalarAmount());

    // Math::printMat(m_modelModuleModels[i].model());


    m_modelModuleModels[i].setIsModified(false);
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

    void concatnateWorlds()
    {
    for(u64_t i = 0; i < userWorlds().size(); i++)
    {
    removeWorldLastPositions();

    for(i64_t j = 0; j < static_cast<i64_t>(userWorlds()[i].userWorldDraw().size()) - 1; j++)
    {
    u32_t worldPositionIndex = userWorlds()[i].userWorldDraw()[static_cast<u64_t>(j)];
    u32_t worldPositionNextIndex = userWorlds()[i].userWorldDraw()[static_cast<u64_t>(j + 1)];
    ModelWorldQuery modelWorldQuery = modelWorldFind(worldPositionIndex, userWorlds()[i].mainWorldName());
    ModelWorldQuery modelWorldQueryNext = modelWorldFind(worldPositionNextIndex, userWorlds()[i].mainWorldName());

    worldLastPositionAddWorld(worldPositionIndex);


    if(worldPositionIndex == worldPositionNextIndex &&
       (modelWorldIndex(modelWorldQuery).modelPosition(worldLastPosition(worldPositionIndex)).second == modelWorldIndex(modelWorldQueryNext).modelPosition(worldLastPosition(worldPositionIndex) + 1).first))
    {
    modelWorldIndex(modelWorldQuery).setModelEndPosition(worldLastPosition(worldPositionIndex), modelWorldIndex(modelWorldQuery).modelPosition(worldLastPosition(worldPositionIndex) + 1).second);
    modelWorldIndex(modelWorldQuery).erasePosition(worldLastPosition(worldPositionIndex) + 1);
    m_userWorlds.eraseWorldOrder(static_cast<u64_t>(j), worldPositionIndex);
    }

    worldLastPositionUpdate(worldPositionIndex);
    }
    }

    }

   private: 
    struct LayerTracker
    {
       public:
        LayerTracker()
        : m_layerSize{0},
          m_currentLayer{0},
          m_previousLayer{0}
        {

        }

        void initLayer()
        {
        m_layerSize++;
        }
       
        void updateLayer()
        {
        m_currentLayer++;
        m_previousLayer = m_currentLayer - 1;
        if(m_currentLayer == m_layerSize)
        {
        m_currentLayer = 0;
        }


        }

        u32_t currentLayer() const
        {
        return m_currentLayer;
        }
       
        u32_t previousLayer() const
        {
        return m_previousLayer;
        }
        
       public:
        u32_t m_layerSize;
        u32_t m_currentLayer;
        u32_t m_previousLayer;
    };

    struct ManagerModuleModelWorlds
    {
       public:
        ManagerModuleModelWorlds()
        : m_currentLayer{0},
          m_previousLayer{0},
          m_currentMainWorld{ModelWorld{"ModelManagerDefaultWorld",
                                        0,
                                        0
                                      }
                            },
          m_currentWorld{ModelWorld{"ModelManagerDefaultWorld",
                                    0,
                                    0
                                   }
                        },
          m_previousWorld{ModelWorld{"ModelManagerDefaultWorld",
                                     0,
                                     0
                                    }
                         }
        {

        }

        ~ManagerModuleModelWorlds()
        {

        }

        class AddedWorldQuery
        {
           public:
            AddedWorldQuery()
            : m_mainWorldName{nullptr},
              m_position{0}
            {

            }
            AddedWorldQuery(const char* mainWorldName, u32_t position)
            : m_mainWorldName{mainWorldName},
              m_position{position}
            {

            }
            ~AddedWorldQuery()
            {

            }

            const char* mainWorldName() const
            {
            return m_mainWorldName;
            }

            u32_t position() const
            {
            return m_position;
            }

           private:
            const char* m_mainWorldName;
            u32_t m_position;
        };

        class LayerModelWorlds
        {
           public:
            LayerModelWorlds()
            : m_mainWorlds{Vector<MainWorld>{}},
              m_addModelWorldOrder{Vector<AddedWorldQuery>{}}
              // m_addModelDifferent{Vector<u32_t>{}}
            {

            }
            ~LayerModelWorlds()
            {

            }

            void addMainWorld(ModelWorld modelWorld)
            {
            m_mainWorlds.push_back(MainWorld{modelWorld});

            }
            void addSubWorld(ModelWorld modelWorld, const char* mainWorldName)
            {
            for(MainWorld& mainWorld : m_mainWorlds)
            {
            if(strcmp(mainWorld.mainWorld().name(), mainWorldName) == 0)
            {
            mainWorld.addSubWorld(modelWorld);
            }
            }

            }

            // [ Rename to modelWorld different ]
            // void addModelDifferent(u32_t modelWorldPosition)
            // {
            // m_addModelDifferent.push_back(modelWorldPosition);
            // }

            void addWorldAddOrder(u32_t modelWorldPosition, const char* name)
            {
            m_addModelWorldOrder.push_back(AddedWorldQuery{name, modelWorldPosition});
            }

            void eraseAddWorld(u64_t updateCount, u64_t worldPosition)
            {
            u64_t occuranceWorld = 0;
            for(u64_t i = 0; i < m_addModelWorldOrder.size(); i++)
            {
            if(m_addModelWorldOrder[i].position() == worldPosition)
            {
            if(occuranceWorld == updateCount)
            {
            m_addModelWorldOrder.erase(m_addModelWorldOrder.begin() + static_cast<i64_t>(i));
            }
            occuranceWorld++;
            }
            }
            }

            Vector<MainWorld> mainWorlds() const
            {
            return m_mainWorlds;
            }

            Vector<MainWorld>& mainWorlds()
            {
            return m_mainWorlds;
            }

            Vector<AddedWorldQuery> addModelWorldOrder() const
            {
            return m_addModelWorldOrder;
            }

           public:
            Vector<MainWorld> m_mainWorlds;

            Vector<AddedWorldQuery> m_addModelWorldOrder;
        };

        void initLayer()
        {
        m_modelWorlds.push_back(LayerModelWorlds{});
        }

        void updateLayer(LayerTracker layerTracker)
        {
        m_currentLayer = layerTracker.currentLayer();
        m_previousLayer = layerTracker.previousLayer();
        }

        void addWorld(const char* name,
                      u32_t orderInList)
        {
        m_modelWorlds[m_currentLayer].addMainWorld(ModelWorld{name, orderInList});

        }

        void addSubWorld(const char* name,
                         u32_t orderInList,
                         const char* mainWorldName)
        {
        m_modelWorlds[m_currentLayer].addSubWorld(ModelWorld{name, orderInList}, mainWorldName);
        }
      
        // [ Use world position to check so don't
        //   search through whole char ]
        void addModelBeginPosition(u32_t indexInModelList,
                                   const char* worldName)
        {
        for(MainWorld& mainWorld : m_modelWorlds[m_currentLayer].mainWorlds())
        {
        if(strcmp(mainWorld.mainWorld().name(), worldName) == 0)
        {
        mainWorld.mainWorld().addModelBeginPosition(indexInModelList);
        return;
        }
        for(ModelWorld& modelWorld : mainWorld.subWorlds())
        {
        if(strcmp(modelWorld.name(), worldName) == 0)
        {
        modelWorld.addModelBeginPosition(indexInModelList);
        return;
        }
        }
        }

        }

        void addModelEndPosition(u32_t indexInModelList,
                                 const char* worldName)
        {
        for(MainWorld& mainWorld : m_modelWorlds[m_currentLayer].mainWorlds())
        {
        if(strcmp(mainWorld.mainWorld().name(), worldName) == 0)
        {
        mainWorld.mainWorld().addModelEndPosition(indexInModelList);
        return;
        }

        for(ModelWorld& modelWorld : mainWorld.subWorlds())
        {
        if(strcmp(modelWorld.name(), worldName) == 0)
        {
        modelWorld.addModelEndPosition(indexInModelList);
        return;
        }
        }

        }
        
        }

        void addWorldAddOrder(u32_t modelWorldPosition, const char* name)
        {
        m_modelWorlds[m_currentLayer].addWorldAddOrder(modelWorldPosition, name);
        }

        void eraseAddWorld(u64_t updateCount, u64_t worldPosition)
        {
        m_modelWorlds[m_currentLayer].eraseAddWorld(updateCount, worldPosition);
        }

        void setCurrentMainWorld(ModelWorld world)
        {
        m_currentMainWorld = world;
        }

        void setCurrentWorld(ModelWorld world)
        {
        m_currentWorld = world;
        }

        void setPreviousWorld(ModelWorld world)
        {
        m_previousWorld = world;
        }

        ModelWorld modelWorld(u32_t modelWorldPosition) const
        {
        ModelWorld world;
        for(u32_t i = 0; i < m_modelWorlds[m_currentLayer].mainWorlds().size(); i++)
        {
        if(strcmp(m_currentMainWorld.name(), m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().name()) == 0)
        {
        if(modelWorldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().orderInList())
        {
        world = m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld();
        break;
        }
        for(u32_t j = 0; j < m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds().size(); j++)
        {
        if(modelWorldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j].orderInList())
        {
        world = m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j];
        break;
        }
        }
        }

        }

        return world;
        }

        ModelWorld modelWorld(u32_t worldPosition,
                              const char* mainWorldName) const 
        {
        ModelWorld world;
        for(u32_t i = 0; i < m_modelWorlds[m_currentLayer].mainWorlds().size(); i++)
        {
        if(strcmp(mainWorldName, m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().name()) == 0)
        {
        if(worldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().orderInList())
        {
        world = m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld();
        break;
        }
        for(u32_t j = 0; j < m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds().size(); j++)
        {
        if(worldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j].orderInList())
        {
        world = m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j];
        break;
        }
        }
        break;
        }

        }

        // [ DEBUG ]
        if(world.name() == nullptr)
        {
        std::cout << "Returning invalid world\n";
        }

        return world;
        }

        // [ Accesses out of bounds and crashes if cannot find
        //   the modelWorld ]
        ModelWorld& modelWorld(u32_t worldPosition,
                               const char* mainWorldName)
        {
        for(u32_t i = 0; i < m_modelWorlds[m_currentLayer].mainWorlds().size(); i++)
        {

        if(strcmp(mainWorldName, m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().name()) == 0)
        {
        if(worldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().orderInList())
        {
        return m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld();
        }
        for(u32_t j = 0; j < m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds().size(); j++)
        {
        if(worldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j].orderInList())
        {
        return m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j];
        }
        }
        }
        }

        // [ DEBUG ]
        // [ Returning invalid
        //   world ]

        return m_modelWorlds[m_currentLayer].mainWorlds()[
        m_modelWorlds[m_currentLayer].mainWorlds().size() - 1
        ].subWorlds()[m_modelWorlds[m_currentLayer].mainWorlds()[
        m_modelWorlds[m_currentLayer].mainWorlds().size() - 1
        ].subWorlds().size()];
   
        }

        ModelWorldQuery modelWorldFind(u32_t worldPosition,
                                       const char* mainWorldName)
        {
        for(u32_t i = 0; i < m_modelWorlds[m_currentLayer].mainWorlds().size(); i++)
        {
        if(strcmp(mainWorldName, m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().name()) == 0)
        {
        if(worldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].mainWorld().orderInList())
        { 
        return ModelWorldQuery{true, i, 0};
        }
        for(u32_t j = 0; j < m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds().size(); j++)
        {
        if(worldPosition == m_modelWorlds[m_currentLayer].mainWorlds()[i].subWorlds()[j].orderInList())
        {
        return ModelWorldQuery{true, i, j + 1};
        }
        }
        }
        }

        return ModelWorldQuery{false, 0, 0};
        }
        ModelWorldQuery modelWorldFindPrevious(u32_t worldPosition,
                                               const char* mainWorldName)
        {
        for(u32_t i = 0; i < m_modelWorlds[m_previousLayer].mainWorlds().size(); i++)
        {
        if(strcmp(mainWorldName, m_modelWorlds[m_previousLayer].mainWorlds()[i].mainWorld().name()) == 0)
        {
        if(worldPosition == m_modelWorlds[m_previousLayer].mainWorlds()[i].mainWorld().orderInList())
        { 
        return ModelWorldQuery{true, i, 0};
        }
        for(u32_t j = 0; j < m_modelWorlds[m_previousLayer].mainWorlds()[i].subWorlds().size(); j++)
        {
        if(worldPosition == m_modelWorlds[m_previousLayer].mainWorlds()[i].subWorlds()[j].orderInList())
        {
        return ModelWorldQuery{true, i, j + 1};
        }
        }
        }
        }

        return ModelWorldQuery{false, 0, 0};
        }

        ModelWorld& modelWorldPrevious(u32_t worldPosition,
                                       const char* mainWorldName)
        {
        for(u32_t i = 0; i < m_modelWorlds[m_currentLayer].mainWorlds().size(); i++)
        {

        if(strcmp(mainWorldName, m_modelWorlds[m_previousLayer].mainWorlds()[i].mainWorld().name()) == 0)
        {
        if(worldPosition == m_modelWorlds[m_previousLayer].mainWorlds()[i].mainWorld().orderInList())
        {
        return m_modelWorlds[m_previousLayer].mainWorlds()[i].mainWorld();
        }
        for(u32_t j = 0; j < m_modelWorlds[m_previousLayer].mainWorlds()[i].subWorlds().size(); j++)
        {
        if(worldPosition == m_modelWorlds[m_previousLayer].mainWorlds()[i].subWorlds()[j].orderInList())
        {
        return m_modelWorlds[m_previousLayer].mainWorlds()[i].subWorlds()[j];
        }
        }
        }
        }
        return m_modelWorlds[m_previousLayer].mainWorlds()[
        m_modelWorlds[m_previousLayer].mainWorlds().size() - 1
        ].subWorlds()[m_modelWorlds[m_previousLayer].mainWorlds()[
        m_modelWorlds[m_previousLayer].mainWorlds().size() - 1
        ].subWorlds().size()];
   
        }

        ModelWorld& modelWorldIndex(ModelWorldQuery modelWorldQuery)
        {
        if(modelWorldQuery.index() == 0)
        {
        return m_modelWorlds[m_currentLayer].mainWorlds()[modelWorldQuery.mainWorldIndex()].mainWorld();
        }
        return m_modelWorlds[m_currentLayer].mainWorlds()[modelWorldQuery.mainWorldIndex()].subWorlds()[modelWorldQuery.index() - 1];

        }
        ModelWorld& modelWorldIndexPrevious(ModelWorldQuery modelWorldQuery)
        {
        if(modelWorldQuery.index() == 0)
        {
        return m_modelWorlds[m_previousLayer].mainWorlds()[modelWorldQuery.mainWorldIndex()].mainWorld();
        }
        return m_modelWorlds[m_previousLayer].mainWorlds()[modelWorldQuery.mainWorldIndex()].subWorlds()[modelWorldQuery.index() - 1];

        }

        MainWorld mainWorld(const char* mainWorldName) const
        {
        for(MainWorld& mainWorld : m_modelWorlds[m_currentLayer].mainWorlds())
        {
        if(strcmp(mainWorld.mainWorld().name(), mainWorldName) == 0)
        {
        return mainWorld;
        }
        }

        return MainWorld{ModelWorld{}, Vector<ModelWorld>{}};
        }

        ModelWorld currentWorld() const
        {
        return m_currentWorld;
        }

        ModelWorld currentMainWorld() const
        { 
        return m_currentMainWorld;
        }

        ModelWorld previousWorld() const
        {
        return m_previousWorld;
        }

        Vector<MainWorld> mainWorlds() const
        {
        return m_modelWorlds[m_currentLayer].mainWorlds();
        }

        Vector<MainWorld>& mainWorlds()
        {
        return m_modelWorlds[m_currentLayer].mainWorlds();
        }

        Vector<MainWorld> mainWorldsPrevious() const
        {
        return m_modelWorlds[m_previousLayer].mainWorlds();
        }

        Vector<MainWorld>& mainWorldsPrevious()
        {
        return m_modelWorlds[m_previousLayer].mainWorlds();
        }

        Vector<AddedWorldQuery> addWorldAddOrder() const
        {
        return m_modelWorlds[m_currentLayer].addModelWorldOrder();
        }
        Vector<AddedWorldQuery> addWorldAddOrder(u64_t currentLayer) const
        {
        return m_modelWorlds[currentLayer].addModelWorldOrder();
        }
        // Vector<u32_t> addWorldAddOrderPositions() const
        // {
        // return m_modelWorlds[m_currentLayer].addWorldAddOrderPositions();
        // }
        // Vector<const char*> addWorldAddOrderNames() const
        // {
        // return m_modelWorlds[m_currentLayer].addWorldAddOrderNames();
        // }
      
        // Vector<u32_t> addWorlds()
        // {
        // return m_addModelWorlds;
        // }

       private:
        u32_t m_currentLayer;
        u32_t m_previousLayer;
        Vector<LayerModelWorlds> m_modelWorlds;
        // Vector<u32_t> m_addModelWorlds;
        ModelWorld m_currentMainWorld;
        ModelWorld m_currentWorld;
        ModelWorld m_previousWorld;
    };

    // [ Should not have worldLastPosition 
    //   in user world ]
    struct ManagerModuleUserWorlds
    {
       public:
        ManagerModuleUserWorlds()
        : m_currentLayer{0},
          m_previousLayer{0}
        {

        }
      
        ~ManagerModuleUserWorlds()
        {

        }

        void initLayer()
        {
        m_managerModuleUserWorlds.push_back(Vector<UserWorld>{});
        }

        void updateLayer(LayerTracker layerTracker)
        {
        m_currentLayer = layerTracker.currentLayer();
        m_previousLayer = layerTracker.previousLayer();
        }

        void addMainWorld(const char* mainWorldName,
                          const char* userWorldName,
                          ManagerModuleModelWorlds modelWorlds)
        {
        userWorlds().push_back(UserWorld{mainWorldName, 
                                         userWorldName
                                        }
                                     );

        }

        void addUserSubWorld(const char* subWorldName,
                             const char* userWorldName)
        {
        for(UserWorld& world : userWorlds())
        {
        if(strcmp(userWorldName, world.name()) == 0)
        {
        world.addUserSubWorld(subWorldName);
        }
        }
        }

        void addDrawOrder(u32_t modelWorldPosition, 
                          const char* mainWorldName,
                          const char* worldName)
        {
        // [ Will add draw order twice when a main world and
        //   sub world have the same name ]
        for(UserWorld& world : userWorlds())
        {
        if((strcmp(world.mainWorldName(), mainWorldName) == 0) 
            && (strcmp(mainWorldName, worldName) == 0))
        {
        world.addUserWorldDrawOrder(modelWorldPosition);
        }
        if(!(strcmp(worldName, mainWorldName) == 0))
        {
        for(const char* subWorldName : world.subWorldNames())
        {
        if(strcmp(subWorldName, worldName) == 0)
        {
        // std::cout << world.name() << " add sub world draw order ";
        world.addUserWorldDrawOrder(modelWorldPosition);
        }
        }
        }
        }

        }

        void eraseWorldOrder(u64_t positionIndex, u64_t orderInList)
        {
        for(u64_t i = 0; i < userWorlds().size(); i++)
        {
        userWorlds()[i].eraseWorld(positionIndex, orderInList);
        }

        }

        void removeWorldLastPositions()
        {
        m_worldLastPositions.clear();
        }

        void worldLastPositionAddWorld(u32_t worldPosition)
        {
        if(m_worldLastPositions.find(worldPosition) == m_worldLastPositions.end())
        {
        m_worldLastPositions[worldPosition] = 0;
        }
        }

        void worldLastPositionUpdate(u32_t worldPosition)
        {
        m_worldLastPositions[worldPosition]++;
        }

        u32_t worldLastPosition(u32_t worldPosition)
        {
        return m_worldLastPositions[worldPosition];
        }

        Vector<UserWorld> userWorlds() const
        {
        return m_managerModuleUserWorlds[m_currentLayer];
        }

        Vector<UserWorld>& userWorlds()
        {
        return m_managerModuleUserWorlds[m_currentLayer];
        }

        Vector<UserWorld> userWorldsPrevious() const
        {
        return m_managerModuleUserWorlds[m_previousLayer];
        }

        Vector<UserWorld>& userWorldsPrevious()
        {
        return m_managerModuleUserWorlds[m_previousLayer];
        }

       private:
        u32_t m_currentLayer;
        u32_t m_previousLayer;
        Vector<Vector<UserWorld>> m_managerModuleUserWorlds;
        Map<u32_t, u32_t> m_worldLastPositions;
    };

    Vector<SubModelManager> m_subModelMangers;
    
    VectorSharedIteratorHeap<ModelModuleModel> m_modelModuleModels;
    Vector<u32_t> m_modelsToBeRemovedIndicies;

    LayerTracker m_layerTracker;

    // Shared between user worlds
    ManagerModuleModelWorlds m_modelWorlds;

    // [ Delete these ]
    Vector<ModelLayer> m_modelLayers;
    Vector<ModelLayer>::iterator m_modelLayersIterator;
    Vector<ModelLayer>::iterator m_previousModelLayersIterator;

    ManagerModuleUserWorlds m_userWorlds;
    Vector<u32_t> m_addedWorlds;

    ModelWorld m_defaultWorld;
    Viewspace m_currentViewspace;

    // [ Layers that are higher or added last have higher priority 
    //   renderering than layers added earilier ]
    
    // [ Layers cannot access worlds in other layers and are therefore
    //   separate when drawing the layers to the engine ]

    // [ Rename to m_uniqueIDGenerator ]
    EllipseMath::RandomRemoveLast m_randomRemoveLast;
    u32_t m_modelOrderCount;
    u32_t m_modelWorldCount;

    // [ Unused, delete this when possible ]
    ModelWorldDrawOrder m_modelWorldDrawOrder;
};

void ModelManagerModuleImpl::setDifferentInViewspace(float viewspaceWidth,
      float viewspaceHeight,
      float originalWindowWidth,
      float originalWindowHeight)
{
    m_currentViewspace.m_width += (static_cast<float>(m_currentViewspace.m_width) / static_cast<float>(originalWindowWidth) ) * static_cast<float>(viewspaceWidth);

    m_currentViewspace.m_height += (static_cast<float>(m_currentViewspace.m_height) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceHeight);

    m_currentViewspace.m_posX += (static_cast<float>(m_currentViewspace.m_posX) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceWidth);

    m_currentViewspace.m_posY += (static_cast<float>(m_currentViewspace.m_posY) / static_cast<float>(originalWindowHeight)) * static_cast<float>(viewspaceHeight);


    // for(ModelLayer& modelLayer : m_modelLayers)
    // {
    // for(ModelViewspace& modelViewspace : modelLayer.m_modelViewspaces)
    // {
    // float viewspaceWindowWidthRatio = 
    // static_cast<float>(modelViewspace.m_viewspace.m_width)
    // / 
    // static_cast<float>(originalWindowWidth);
    //
    // float viewspaceWindowHeightRatio = 
    // static_cast<float>(modelViewspace.m_viewspace.m_height)
    // / 
    // static_cast<float>(originalWindowHeight);
    //
    // float viewspaceWindowPosXRatio = 
    // static_cast<float>(modelViewspace.m_viewspace.m_posX)
    // / 
    // static_cast<float>(originalWindowWidth);
    //
    // float viewspaceWindowPosYRatio = 
    // static_cast<float>(modelViewspace.m_viewspace.m_posY)
    // / 
    // static_cast<float>(originalWindowHeight);
    //
    // // [ This ratio solution is heavily hackish, need to find
    // //   a better solution for resolving multiple viewspaces 
    // //   adjust to the new window size ]
    //
    // float viewspaceRatioWidth = static_cast<float>(viewspaceWidth) * viewspaceWindowWidthRatio;
    // float viewspaceRatioHeight = static_cast<float>(viewspaceHeight) * viewspaceWindowHeightRatio;
    // float viewspaceRatioPosX = static_cast<float>(viewspaceWidth) * viewspaceWindowPosXRatio;
    // float viewspaceRatioPosY = static_cast<float>(viewspaceHeight) * viewspaceWindowPosYRatio;
    //
    // // std::cout << "Window difference " <<  viewspaceWidth << '\n';
    // // std::cout << "Window ratio " << viewspaceWindowWidthRatio << '\n';
    //
    // if(modelViewspace.m_viewspace.m_posX != 0 
    //    || modelViewspace.m_viewspace.m_posY != 0)
    // {
    // modelViewspace.m_viewspace.m_posX += viewspaceRatioPosX;
    // modelViewspace.m_viewspace.m_posY += viewspaceRatioPosY;
    // }
    //
    // modelViewspace.m_viewspace.m_width += viewspaceRatioWidth;
    // modelViewspace.m_viewspace.m_height += viewspaceRatioHeight;
    // }
    // }
}

SharedPtr<ModelManagerModule> ModelManagerModule::createModelManagerModule()
{
    return createShared<ModelManagerModuleImpl>();
}

}   // namespace Ellipse
