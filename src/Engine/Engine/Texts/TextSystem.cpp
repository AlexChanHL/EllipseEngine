
#include "TextSystem.hpp"


namespace Ellipse{
 class TextRenderSystemImpl : TextRenderSystem {
    public:
     TextRenderSystemImpl() = default;
     virtual ~TextRenderSystemImpl() = default;

     virtual void loadFontSheet(String texturePath) override {}
     virtual TextQuad createQuad(u32_t w, u32_t h, u32_t fontIdx) override { return TextQuad{}; }
     virtual void renderQuad(TextQuad& quad, EllipseMath::Vec2 pos) override {}

    private:
     
 };

 class TextSystemImpl : public TextSystem {
    public:
      TextSystemImpl() = default;
      TextSystemImpl(Engine& engine) {
       m_textRenderSystem->loadFontSheet("BasicFonts.ttf");
      };
      ~TextSystemImpl() = default;
 
      virtual void onInit() override {}
      virtual void onUpdate() override {}
      virtual void displayText(String message, EllipseMath::Vec2 pos) override {
       auto quad = m_textRenderSystem->createQuad(10, 10, 0);
       m_textRenderSystem->renderQuad(quad, pos);
      }
      virtual TextRenderSystem* textRenderSystem() override { return m_textRenderSystem; }
     
    private:
      TextRenderSystem* m_textRenderSystem;
 };

 SharedPtr<ISystem> TextSystem::createTextSystem(Engine& engine) {
     return createShared<TextSystemImpl>(engine);
 }
}
 

