#pragma once

#include "RenderObj.hpp"

// Use own math library instead
#include <glm/glm.hpp>

enum class GraphicsSpec : uint32_t
{
    OpenGL
};

class RenderPlugin
{
   public:
    virtual ~RenderPlugin() {}
    virtual void render(RenderObj& rObj, RenderShaderObj& sObj) = 0;
    virtual void setClearColor(const glm::vec4& col) = 0;
    virtual void setViewport(int width, int height) = 0;
    virtual std::unique_ptr<RenderObj> createRenderObj() = 0;
    virtual std::unique_ptr<RenderShaderObj> createShaderObj() = 0;

    static std::unique_ptr<RenderPlugin> createRenderPlugin(GraphicsSpec spec);

   private:

};
