#pragma once

#include "Core/ScanCodes.hpp"
#include "Core/KeyCodes.hpp"

class Input
{
   public:
     static bool isKeyPressed(const KeyCode& key);
     // static virtual bool isMousePressed(MouseCode key) = 0;
   private:
};
