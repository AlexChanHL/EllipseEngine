#pragma once

#include "Engine/Module.hpp"

struct Model
{
    public:
};

class RenderModule : public IModule
{
   public:
    RenderModule() = default;
    virtual ~RenderModule() = default;
    
    virtual Model createModel() = 0;
    virtual void renderModel(const Model& model) = 0;

    // static void createRenderModule();

   private:

};
