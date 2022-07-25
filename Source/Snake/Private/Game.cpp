#include "Game.h"

void Game::Run()
{
	GameLoop();
}

void Game::GameLoop()
{
	uint32_t startTime;

	while (m_state != GameState::Quit)
	{
		startTime = Clock::GetCurrentTime();
		if (m_state == GameState::Running) m_eventHandler->HandleEvent();
		m_gameMode->Update();
		m_renderer->Render();

		Clock::WaitForMs(startTime + (m_state == GameState::GameOver ? GameConstants::msPerFrameDuringGameOver : GameConstants::msPerFrame) - Clock::GetCurrentTime());
	}
}
