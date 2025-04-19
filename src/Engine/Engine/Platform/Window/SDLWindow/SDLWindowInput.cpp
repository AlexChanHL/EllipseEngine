
#include "Input/Input.hpp"

#include <SDL3/SDL.h>


namespace Ellipse
{

bool Input::isKeyPressed(const KeyCode& key)
{
   auto state = SDL_GetKeyboardState(NULL);
   ScanCode scanCode = keyCodeToScanCode(key);

   return state[scanCode];
}

bool Input::isMousePressed(u64_t key)
{
   u64_t state = SDL_GetMouseState(NULL, NULL);

   return key == state;
}

}       // namespace Ellipse

