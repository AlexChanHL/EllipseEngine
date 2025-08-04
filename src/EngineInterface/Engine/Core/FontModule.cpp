
#include "FontModule.hpp"


namespace Ellipse
{

class FontModuleImpl : public FontModule
{
   public:
    FontModuleImpl(Engine& engine)
    : FontModule{},
      m_engine{engine}
    {

    }
    virtual ~FontModuleImpl()
    {

    }

    virtual void init() override 
    {
        String commonChars = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
        Vector<char> commonGlyphs;
        for(char ch : commonChars)
        {
             commonGlyphs.push_back(ch);
        }

        // m_fonts["TimesNewRoman"] = FontCollection{"Assets/Fonts/Font.png", Vec2{0.0f}, 0.1f, 0.1f, commonGlyphs}; 
        m_fonts["TimesNewRoman"] = FontCollection{"Assets/Fonts/Text.png", Vec2{0.0f}, 0.1f, 0.1f, commonGlyphs}; 
        // m_fonts["TimesNewRoman"] = FontCollection{"Assets/Fonts/Solar.jpeg", Vec2{0.0f}, 0.1f, 0.1f, commonGlyphs}; 
    }
    virtual void onUpdate() override 
    {

    }

    FontCollection getFont(String font)
    {
        return m_fonts[font];   
    }

   private:
    Engine& m_engine;
    Map<String, FontCollection> m_fonts;
};

SharedPtr<IModule> FontModule::createFontModule(Engine& engine)
{
    return createShared<FontModuleImpl>(engine);
}

}     // namespace Ellipse

