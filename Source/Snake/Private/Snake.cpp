#include "Snake.h"
#include "Game.h"

Snake::Snake() :
	m_currentDirection(GameConstants::initialSnakeDirection),
	m_headPositionX(GameConstants::initialSnakePositionX),
	m_headPositionY(GameConstants::initialSnakePositionY)
{}

void Snake::Move(uint16_t newHeadPositionX, uint16_t newHeadPositionY, const bool& grow)
{
	// Handle body and growth
	m_body.push_front(BodySection(m_headPositionX, m_headPositionY));
	if (!grow) m_body.pop_back();

	// Move head
	m_headPositionX = newHeadPositionX;
	m_headPositionY = newHeadPositionY;
}

void Snake::Reset()
{
	m_currentDirection = GameConstants::initialSnakeDirection;
	m_headPositionX = GameConstants::initialSnakePositionX;
	m_headPositionY = GameConstants::initialSnakePositionY;
	m_snakeHeadVisible = true;
	m_body.clear();
}
