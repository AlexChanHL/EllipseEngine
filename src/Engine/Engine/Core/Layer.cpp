
#include "Base.hpp"
#include "Layer.hpp"
#include "Application.hpp"

namespace Ellipse
{

class LayerPlaceHolder : public ILayer
{
    public:
     LayerPlaceHolder();
     virtual ~LayerPlaceHolder() = default;

     virtual void init() override;
     virtual void onEvent(Event& event) override;
     virtual void onUpdate(float dt) override;

     virtual bool isHidden() override { return true; }

     virtual void hideLayer() override {}
     virtual void showLayer() override {}

    protected:
    
    protected: 

    private:
     
};

LayerPlaceHolder::LayerPlaceHolder()
{

}

void LayerPlaceHolder::init()
{

}

void LayerPlaceHolder::onEvent(Event& event)
{
  
}
void LayerPlaceHolder::onUpdate(float dt)
{

}

SharedPtr<ILayer> Layer::createDefaultLayer()
{
    return createShared<LayerPlaceHolder>(); 
}

} // namespace Ellipse
