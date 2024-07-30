
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
     virtual void onUpdate() override;

     virtual bool isHidden() override { return true; }

     virtual void hideLayer() override {}
     virtual void showLayer() override {}

    protected:
     // virtual void addM
    
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
void LayerPlaceHolder::onUpdate()
{

}

SharedPtr<ILayer> Layer::createDefaultLayer()
{
    return createShared<LayerPlaceHolder>(); 
}

} // namespace Ellipse
