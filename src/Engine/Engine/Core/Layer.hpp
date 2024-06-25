#pragma once

#include "Event/Event.hpp"

class Layer
{
   public:
     Layer() = default;
     virtual void onEvent(Event& event) = 0;
     virtual ~Layer() = default;
   private:
};
