#include "GameMode.h"
#include "EventHandler.h"
#include "Game.h"
#include <stdlib.h>

GameMode::GameMode(const uint16_t gridWidth, const uint16_t gridHeight, GameState& gameState) :
	m_gridWidth(gridWidth),
	m_gridHeight(gridHeight),
	m_gameState(gameState),
	m_snake(std::make_shared<Snake>()),
	m_food(std::make_shared<Food>()),
	m_snakeTargetSize(GameConstants::initialSnakeSize)
{
	srand(static_cast<unsigned int>(time(nullptr))); //Seed srand

	m_PlaceFood();
}

void GameMode::Update()
{
	// Check game states
	if(m_gameState == GameState::GameOver)
	{
		if (m_snake->m_snakeHeadVisible)
			m_snake->m_snakeHeadVisible = false;
		else if (!m_snake->GetBody().empty())
			m_snake->m_body.pop_front();
		else
		{
			m_gameState = GameState::Running;
			m_snakeTargetSize = GameConstants::initialSnakeSize;
			m_snake->Reset();
			m_PlaceFood();
		}
		return;
	}
	else if(m_gameState == GameState::GameWon)
	{
		m_gameState = GameState::Quit;
		return;
	}

	// Handle snake direction
	SnakeDirection snakeDirection = m_snake->GetDirection();
	uint16_t newSnakeX = m_snake->m_headPositionX;
	uint16_t newSnakeY = m_snake->m_headPositionY;

	switch (snakeDirection)
	{
	case SnakeDirection::Up:
		if (newSnakeY == 0)
			newSnakeY = m_gridHeight - 1;
		else
			newSnakeY--;
		break;

	case SnakeDirection::Left:
		if (newSnakeX == 0)
			newSnakeX = m_gridWidth - 1;
		else
			newSnakeX--;
		break;

	case SnakeDirection::Down:
		newSnakeY = (newSnakeY + 1) % m_gridHeight;
		break;

	case SnakeDirection::Right:
		newSnakeX = (newSnakeX + 1) % m_gridWidth;
		break;
	}

	// Check snake collision
	const std::deque<Snake::BodySection>& snakeBody = m_snake->GetBody();
	for(Snake::BodySection bs : snakeBody)
	{
		if (bs.GetPositionX() == newSnakeX && bs.GetPositionY() == newSnakeY)
		{
			m_gameState = GameState::GameOver;
			break;
		}
	}

	// Eat food
	if(m_food->GetPositionX() == newSnakeX && m_food->GetPositionY() == newSnakeY)
	{
		m_snakeTargetSize += GameConstants::growthPerFood;
		m_PlaceFood();
	}

	if(m_snake->m_body.size() == m_gridWidth * m_gridHeight)
	{
		m_gameState = GameState::GameWon;
	}

	// Move snake if the game is still running
	if(m_gameState == GameState::Running)
		m_snake->Move(newSnakeX, newSnakeY, m_snake->GetBody().size() < m_snakeTargetSize);
}

void GameMode::m_PlaceFood()
{

startOver:
	uint16_t newX = rand() % m_gridWidth;
	uint16_t newY = rand() % m_gridHeight;

	if (m_snake->GetHeadPositionX() == newX && m_snake->GetHeadPositionY() == newY)
		goto startOver;

	std::deque<Snake::BodySection> snakeBody = m_snake->GetBody();
	for(Snake::BodySection bs : snakeBody)
	{
		if (bs.GetPositionX() == newX && bs.GetPositionY() == newY)
			goto startOver;
	}

	m_food->SetPosition(newX, newY);
}
