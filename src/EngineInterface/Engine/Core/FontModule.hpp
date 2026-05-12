#pragma once

#include "Engine/Module.hpp"
#include "Engine/Engine.hpp"
#include "Core/Base.hpp"
#include "Renderer/RenderObj.hpp"


namespace Ellipse
{

struct Glyph
{
   public:
    Glyph()
    : m_pos{0.0f},
      m_xMax{0.0f},
      m_yMax{0.0f},
      m_character{' '}
    {

    }
    Glyph(EllipseMath::Vec2 pos, EllipseMath::Vec2 xMax, EllipseMath::Vec2 yMax, char ch)
    : m_pos{pos},
      m_xMax{xMax},
      m_yMax{yMax},
      m_character{ch}
    {

    }
    ~Glyph()
    {

    }

   public:
    EllipseMath::Vec2 m_pos;
    EllipseMath::Vec2 m_xMax;
    EllipseMath::Vec2 m_yMax;
    char m_character;

   private:
};

struct FontCollection
{
   public:
    FontCollection()
    {

    }
    FontCollection(String sheetPath, EllipseMath::Vec2 pos, float hort, float vert, Vector<char> glyphs)
    : m_sheetPath{sheetPath}
    {
        float hortTotal = hort;
        float vertTotal = 1.0f;
        for(char ch : glyphs)
        {
            if(hortTotal > (1.0f + hort))
            {
                hortTotal = hort;
                vertTotal -= vert;
                #ifdef DEBUG
                if(vertTotal < 0.0f)
                {
                    ELLIPSE_ENGINE_LOG_WARN("Over vert");
                }
                #endif
            }
            m_glyphs[ch] = Glyph{EllipseMath::Vec2{hortTotal - hort, vertTotal - vert}, EllipseMath::Vec2{hort, 0.0f}, EllipseMath::Vec2{0.0f, vert}, ch};
            hortTotal += hort;
        }
    }
    ~FontCollection()
    {

    }
    Glyph getGlyph(char c)
    {
        return m_glyphs[c];
    }
    String sheetPath() const
    {
        return m_sheetPath;
    }
    Vector<Glyph> glyphs() const
    {
        Vector<Glyph> glyphs;
        for(auto [key, value] : m_glyphs)
        {
            glyphs.push_back(value);
        }
        return glyphs;
    }

   private:
    String m_sheetPath;
    Map<char, Glyph> m_glyphs;
};

inline RenderObjData createFontQuad(Glyph glyph,
                                    RenderObjData renderObjData,
                                    TextureData textureData
                                   )
{
    RenderObjData fontQuad = renderObjData;
    EllipseMath::Vec2 posRight = glyph.m_pos + glyph.m_xMax;
    EllipseMath::Vec2 posTop = glyph.m_pos + glyph.m_yMax;
    EllipseMath::Vec2 posTopRight = glyph.m_pos + glyph.m_xMax + glyph.m_yMax;
    fontQuad.setTexCoords(Vector<float>{
                                        posTop.x, posTop.y, 
                                        posTopRight.x, posTopRight.y,
                                        glyph.m_pos.x, glyph.m_pos.y,
                                        posRight.x, posRight.y
                                       }
                         );

    fontQuad.textureData() = textureData;

    return fontQuad;
}

template<typename Func>
void addGlyphs(Vector<Glyph> glyphs,
               RenderObjData quad,
               TextureData timesTexture,
               Func func,
               String vert,
               String frag
              ) {
    for(Glyph glyph : glyphs) {
     Ellipse::RenderObjData data = Ellipse::createFontQuad(glyph, quad, timesTexture);
     String name = String{glyph.m_character};
     func(name.c_str(), vert, frag, data);
    }
}

class FontModule : public IModule
{
   public:
    FontModule() {
     m_name = "FontModule";
    }
    virtual ~FontModule() {

    }

    virtual void init() override = 0;
    virtual void onUpdate() override = 0;

    virtual FontCollection getFont(String fontSheet) = 0;

    static SharedPtr<IModule> createFontModule(Engine& engine);

   private:
};

}     // namespace Ellipse

