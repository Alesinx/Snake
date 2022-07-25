#pragma once

#include <SDL.h>
#include <memory>
#include <functional>

enum class GameState;
class GameMode;
class Renderer;

class EventHandler
{
public:
	EventHandler(GameState& gameState, std::shared_ptr<GameMode> gameMode, std::shared_ptr<Renderer> renderer);
	~EventHandler();

	void HandleEvent();

private:
	SDL_Event* m_event;
	GameState& m_gameState;
	std::shared_ptr<GameMode> m_gameMode;
	std::shared_ptr<Renderer> m_renderer;
};
