#pragma once

#include "Base.hpp"
#include "Engine/Engine.hpp"
#include "Engine/System.hpp"


namespace Ellipse {
 struct FontSheet {
    public:
 };
 class TextRenderSystem {
    public:
     struct TextQuad{
        public:
         u32_t m_width;
         u32_t m_height;
     };
     TextRenderSystem() = default;
     virtual ~TextRenderSystem() = default;

     virtual void loadFontSheet(String texturePath) = 0;
     virtual TextQuad createQuad(u32_t w, u32_t h, u32_t fontIdx) = 0;
     virtual void renderQuad(TextQuad& quad, EllipseMath::Vec2 pos) = 0;

    private:
 };
 
 class TextSystem :public ISystem {
    public:
      TextSystem() = default;
      ~TextSystem() = default;
 
      virtual void displayText(String Message, EllipseMath::Vec2 pos) = 0;
      virtual TextRenderSystem* textRenderSystem() = 0;
      static SharedPtr<ISystem> createTextSystem(Engine& engine);
     
    private:
 };
 
}

