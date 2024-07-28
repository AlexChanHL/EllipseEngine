#include "Input/Input.hpp"

#include <SDL3/SDL.h>

bool Input::isKeyPressed(const KeyCode& key)
{
   auto state = SDL_GetKeyboardState(NULL);
   ScanCode scanCode = keyCodeToScanCode(key);
   return state[scanCode];
}
