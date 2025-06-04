#pragma once

#include "Core/ScanCodes.hpp"
#include "Core/KeyCodes.hpp"

#include "Core/MouseCodes.hpp"


namespace Ellipse
{

class Input
{
   public:
    static bool isKeyPressed(const KeyCode& key);
    static bool isMousePressed(u64_t key);
   private:
};

}       // namespace Ellipse

