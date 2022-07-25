#pragma once

#include "SDL.h"
#include <memory>

class Snake;
class Food;
struct GameProperties;

class Renderer
{
public:
	Renderer(const GameProperties& properties, std::shared_ptr<Snake> snake, std::shared_ptr<Food> food);

	~Renderer();

	void Render();

	void OnWindowMoved(int newX, int newY) {}

private:
	const GameProperties& m_gameProperties;
	const std::shared_ptr<Snake> m_snake;
	const std::shared_ptr<Food> m_food;
	SDL_Window* m_sdlWindow;
	SDL_Renderer* m_sdlRenderer;

	SDL_Rect m_snakeBlock;
	SDL_Rect m_foodBlock;
	SDL_Rect m_snakeEyeBlock;

	uint16_t m_blockWidth;
	uint16_t m_blockHeight;
};
