#include "EventHandler.h"
#include "Game.h"
#include "GameMode.h"
#include "Renderer.h"

EventHandler::EventHandler(GameState& gameState, std::shared_ptr<GameMode> gameMode, std::shared_ptr<Renderer> renderer) :
	m_gameState(gameState),
	m_gameMode(gameMode),
	m_renderer(renderer)
{
	m_event = new SDL_Event();
}

EventHandler::~EventHandler()
{
	delete(m_event);
}

void EventHandler::HandleEvent()
{
	//Handle events on queue
	while (SDL_PollEvent(m_event) != 0)
	{
		switch (m_event->type)
		{
		case SDL_QUIT: 
			m_gameState = GameState::Quit; break;
		case SDL_WINDOWEVENT_MOVED: 
			m_renderer->OnWindowMoved(m_event->window.data1, m_event->window.data2); break;
		case SDL_KEYDOWN:
			switch (m_event->key.keysym.sym)
			{
			case SDLK_w: 
				m_gameMode->OnArrowUpInputEvent(); break;
			case SDLK_a: 
				m_gameMode->OnArrowLeftInputEvent(); break;
			case SDLK_s: 
				m_gameMode->OnArrowDownInputEvent(); break;
			case SDLK_d: 
				m_gameMode->OnArrowRightInputEvent(); break;
			}
			break;
		}
	}
}
