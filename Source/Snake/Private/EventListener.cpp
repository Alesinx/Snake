#include "EventListener.h"

void EventListener::HandleEvent()
{
	event = std::make_unique<SDL_Event>(SDL_Event());
}
