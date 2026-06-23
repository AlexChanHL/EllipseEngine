#pragma once


namespace Ellipse {
 class RenderComponent2D : public RenderComponent {
    public:
     RenderComponent2D() {} 
     RenderComponent2D(RenderModule& renderModule, RenderObjData& data) 
     : RenderComponent{renderModule, data} {
      m_modelData = createShared<ModelData2D>(renderModule.camera());
     };
     ~RenderComponent2D() {
     };

    private:
 };

}

