#pragma once

#include "EventListener.h"
#include "GameMode.h"
#include "Renderer.h"

#include <stdint.h>
#include <memory>

namespace defaults
{
	constexpr uint16_t screenWidth		= 704;
	constexpr uint16_t screenHeigth		= 704;
	constexpr uint16_t gridWidth		= 32;
	constexpr uint16_t gridHeight		= 32;
	constexpr uint16_t targetFPS		= 10;
}

struct GameProperties
{
	uint16_t screenWidth;
	uint16_t screenHeigth;
	uint16_t gridWidth;
	uint16_t gridHeight;
	uint16_t msPerFrame;

	GameProperties(uint16_t screenWidth = defaults::screenWidth,
				uint16_t screenHeigth = defaults::screenHeigth,
		uint16_t gridWidth = defaults::gridWidth,
		uint16_t gridHeight = defaults::gridHeight,
		uint16_t targetFPS = defaults::targetFPS) :
		screenWidth(screenWidth),
		screenHeigth(screenHeigth),
		gridWidth(gridWidth),
		gridHeight(gridHeight),
		msPerFrame(static_cast<uint16_t>((1.f / targetFPS) * 1000))
	{}
};

enum class GameState
{
	Running,
	GameOver,
	GameWon,
	Quit
};

class Game
{
public:
	Game(const GameProperties& gameProperties = GameProperties()) : 
		m_gameProperties(gameProperties)
	{}

	void Run();
	
private:
	const GameProperties m_gameProperties;

	std::shared_ptr<EventListener> m_eventListener;
	std::shared_ptr<GameMode> m_GamemMode;
	std::shared_ptr<Renderer> m_renderer;

	GameState m_gameState = GameState::Running;

private:
	void GameLoop();
};
