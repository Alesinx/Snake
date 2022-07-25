#pragma once

#include <deque>

enum class SnakeDirection { Up, Left, Down, Right };

class Snake
{
	friend class GameMode;

public:
	class BodySection
	{
	public:
		BodySection(const uint16_t& positionX, const uint16_t& positionY) : 
			m_positionX(positionX),
			m_positionY(positionY)
		{}

		const uint16_t& GetPositionX() { return m_positionX; }
		const uint16_t& GetPositionY() { return m_positionY; }

	private:
		uint16_t m_positionX;
		uint16_t m_positionY;
	};

public:
	Snake();

	void Move(uint16_t newHeadPositionX, uint16_t newHeadPositionY, const bool& grow);
	void ChangeDirection(SnakeDirection direction) { m_currentDirection = direction; }
	void Reset();

	const SnakeDirection& GetDirection() const { return m_currentDirection; }
	const uint16_t& GetHeadPositionX() const { return m_headPositionX; }
	const uint16_t& GetHeadPositionY() const { return m_headPositionY; }
	const std::deque<BodySection>& GetBody() const { return m_body; }
	const bool& GetSnakeHeadVisible() const { return m_snakeHeadVisible; }

private:
	SnakeDirection m_currentDirection;
	uint16_t m_headPositionX;
	uint16_t m_headPositionY;
	std::deque<BodySection> m_body;
	bool m_snakeHeadVisible = true;
};
