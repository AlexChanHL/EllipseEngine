#pragma once

#include "Core/Base.hpp"
#include "Module.hpp"


namespace Ellipse {
 class ISystem {
   public:
    ISystem() = default;
    virtual ~ISystem() = default;
 
    String& name() { return m_name; }
    void setName(const char* name) { m_name = name; }
    virtual void onInit() = 0;
    virtual void onUpdate() = 0;
 
   protected:
    String m_name;
 
   private:
 };
 
 class NoSystem : public ISystem {
    public:
     NoSystem() {
      m_name = "No system";
     }
 
    private:
 };
 
}     // namespace Ellipse

