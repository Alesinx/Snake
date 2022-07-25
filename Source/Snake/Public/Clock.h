#include <SDL.h>

namespace Clock
{
	inline uint32_t GetCurrentTime() { return SDL_GetTicks(); }
	inline void WaitForMs(uint32_t miliseconds) { return SDL_Delay(miliseconds); };
};