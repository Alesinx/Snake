#pragma once

#include <SDL.h>
#include <memory>

class EventListener
{
public:
	void HandleEvent();

private:
	std::unique_ptr<SDL_Event> event;
};

