#pragma once

#include "Snake.h"
#include "Food.h"
#include <memory>

class EventHandler;
class Snake;
enum class GameState;

class GameMode
{
public:
	GameMode(const uint16_t m_gridWidth, const uint16_t m_gridHeight, GameState& gameState);

	void Update();

	void OnArrowUpInputEvent() { m_snake->ChangeDirection(SnakeDirection::Up); }
	void OnArrowLeftInputEvent() { m_snake->ChangeDirection(SnakeDirection::Left); }
	void OnArrowDownInputEvent() { m_snake->ChangeDirection(SnakeDirection::Down); }
	void OnArrowRightInputEvent() { m_snake->ChangeDirection(SnakeDirection::Right); }

	const std::shared_ptr<Snake> GetSnake() { return m_snake; }
	const std::shared_ptr<Food> GetFood() { return m_food; }

private:
	const uint16_t m_gridWidth;
	const uint16_t m_gridHeight;
	GameState& m_gameState;
	std::shared_ptr<Snake> m_snake;
	std::shared_ptr<Food> m_food;
	uint16_t m_snakeTargetSize;

private:
	void m_PlaceFood();
};
