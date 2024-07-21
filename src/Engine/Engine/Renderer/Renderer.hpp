#pragma once

#include "RenderPlugin.hpp"

// Use own math library instead
#include <glm/glm.hpp>

class Renderer
{
   public:
    Renderer(std::unique_ptr<RenderPlugin> plugin);
    ~Renderer();

    void render(RenderObj& rObj, RenderShaderObj& sObj);
    void setClearColor(const glm::vec4& col);
    void setViewport(int32_t width, int32_t height);
    std::unique_ptr<RenderObj> createRenderObj();
    std::unique_ptr<RenderShaderObj> createShaderObj();
    static std::unique_ptr<Renderer> createRenderer(std::unique_ptr<RenderPlugin> plugin);

   private:
    std::unique_ptr<RenderPlugin> m_plugin = nullptr;
};
