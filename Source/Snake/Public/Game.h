#pragma once

#include "Clock.h"
#include "EventHandler.h"
#include "GameMode.h"
#include "Renderer.h"
#include "Snake.h"

#include <SDL.h>
#include <stdint.h>
#include <memory>

namespace GameConstants
{
	constexpr uint16_t msPerFrame = 100;
	constexpr uint16_t initialSnakeSize = 3;
	constexpr uint16_t growthPerFood = 5;
	constexpr uint16_t initialSnakePositionX = 0;
	constexpr uint16_t initialSnakePositionY = 0;
	constexpr SnakeDirection initialSnakeDirection = SnakeDirection::Down;
	constexpr uint16_t msPerFrameDuringGameOver = 25;
}

namespace Variables
{
	static uint16_t gridWidth;
	static uint16_t gridHegith;
	
}

struct GameProperties
{
	uint16_t screenWidth;
	uint16_t screenHeight;
	uint16_t gridWidth;
	uint16_t gridHeight;

	GameProperties(
		uint16_t screenWidth = 704,
		uint16_t screenHeigth = 704,
		uint16_t gridWidth = 32,
		uint16_t gridHeight = 32) :
		screenWidth(screenWidth),
		screenHeight(screenHeigth),
		gridWidth(gridWidth),
		gridHeight(gridHeight)
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
	Game(const GameProperties& properties = GameProperties()) :
		m_properties(properties),
		m_gameMode(std::make_shared<GameMode>(m_properties.gridWidth, m_properties.gridHeight, m_state)),
		m_renderer(std::make_shared<Renderer>(m_properties, m_gameMode->GetSnake(), m_gameMode->GetFood())),
		m_eventHandler(std::make_unique<EventHandler>(m_state, m_gameMode, m_renderer)),
		m_state(GameState::Running)
	{}

	void Run();

	void OnQuitEvent() { m_state = GameState::Quit; }

private:
	const GameProperties m_properties;
	GameState m_state;
	std::shared_ptr<GameMode> m_gameMode;
	std::shared_ptr<Renderer> m_renderer;
	std::shared_ptr<EventHandler> m_eventHandler;

private:
	void GameLoop();
};
