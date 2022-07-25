#include "Renderer.h"
#include "Snake.h"
#include "Food.h"
#include <iostream>
#include "Game.h"

Renderer::Renderer(const GameProperties& gameProperties,
	std::shared_ptr<Snake> snake,
	std::shared_ptr<Food> food) :
	m_gameProperties(gameProperties),
	m_snake(snake),
	m_food(food)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Failure in SDL initialization: " << SDL_GetError() << std::endl;
	}

	// Create window
	m_sdlWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_gameProperties.screenWidth, m_gameProperties.screenHeight, SDL_WINDOW_SHOWN);

	if (!m_sdlWindow)
	{
		std::cerr << "Failure creating a SDL window: " << SDL_GetError() << std::endl;
	}

	// Create renderer
	m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!m_sdlRenderer)
	{
		std::cerr << "Failure creating SDL renderer: " << SDL_GetError() << std::endl;
	}

	m_blockWidth = m_snakeBlock.w = m_foodBlock.w = m_gameProperties.screenWidth / m_gameProperties.gridWidth;
	m_blockHeight = m_snakeBlock.h = m_foodBlock.h = m_gameProperties.screenHeight / m_gameProperties.gridHeight;
	m_snakeEyeBlock.w = m_blockWidth / 5;
	m_snakeEyeBlock.h = m_blockHeight / 5;
}
//
Renderer::~Renderer()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_DestroyRenderer(m_sdlRenderer);
	SDL_Quit();
}

void Renderer::Render()
{
	// Clear screen
	SDL_SetRenderDrawColor(m_sdlRenderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(m_sdlRenderer);

	// Draw body
	SDL_SetRenderDrawColor(m_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	const std::deque<Snake::BodySection>& snakeBody = m_snake->GetBody();
	for (Snake::BodySection bs : snakeBody)
	{
		m_snakeBlock.x = bs.GetPositionX() * m_blockWidth + (m_blockWidth - m_snakeBlock.w) / 2;
		m_snakeBlock.y = bs.GetPositionY() * m_blockHeight + (m_blockHeight - m_snakeBlock.h) / 2;
		SDL_RenderFillRect(m_sdlRenderer, &m_snakeBlock);
	}

	// Draw food
	SDL_SetRenderDrawColor(m_sdlRenderer, 0xFF, 0x00, 0x00, 0xFF);
	m_foodBlock.x = m_food->GetPositionX() * m_blockWidth;
	m_foodBlock.y = m_food->GetPositionY() * m_blockHeight;
	SDL_RenderFillRect(m_sdlRenderer, &m_foodBlock);

	if(m_snake->GetSnakeHeadVisible())
	{
		// Draw snake head
		SDL_SetRenderDrawColor(m_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		m_snakeBlock.x = m_snake->GetHeadPositionX() * m_blockWidth + (m_blockWidth - m_snakeBlock.w) / 2;
		m_snakeBlock.y = m_snake->GetHeadPositionY() * m_blockHeight + (m_blockHeight - m_snakeBlock.h) / 2;
		SDL_RenderFillRect(m_sdlRenderer, &m_snakeBlock);

		// Draw snake eyes
		SDL_SetRenderDrawColor(m_sdlRenderer, 0x0, 0x0, 0x0, 0xFF);
		SnakeDirection snakeDirection = m_snake->GetDirection();
		if (snakeDirection == SnakeDirection::Left || snakeDirection == SnakeDirection::Up)
		{
			m_snakeEyeBlock.x = m_snakeBlock.x + m_snakeEyeBlock.w;
			m_snakeEyeBlock.y = m_snakeBlock.y + m_snakeEyeBlock.h;
			SDL_RenderFillRect(m_sdlRenderer, &m_snakeEyeBlock);
		}
		if (snakeDirection == SnakeDirection::Up || snakeDirection == SnakeDirection::Right)
		{
			m_snakeEyeBlock.x = m_snakeBlock.x + m_snakeEyeBlock.w * 3;
			m_snakeEyeBlock.y = m_snakeBlock.y + m_snakeEyeBlock.h;
			SDL_RenderFillRect(m_sdlRenderer, &m_snakeEyeBlock);
		}
		if (snakeDirection == SnakeDirection::Down || snakeDirection == SnakeDirection::Left)
		{
			m_snakeEyeBlock.x = m_snakeBlock.x + m_snakeEyeBlock.w;
			m_snakeEyeBlock.y = m_snakeBlock.y + m_snakeEyeBlock.h * 3;
			SDL_RenderFillRect(m_sdlRenderer, &m_snakeEyeBlock);
		}
		if (snakeDirection == SnakeDirection::Right || snakeDirection == SnakeDirection::Down)
		{
			m_snakeEyeBlock.x = m_snakeBlock.x + m_snakeEyeBlock.w * 3;
			m_snakeEyeBlock.y = m_snakeBlock.y + m_snakeEyeBlock.h * 3;
			SDL_RenderFillRect(m_sdlRenderer, &m_snakeEyeBlock);
		}
	}

	// Update screen
	SDL_RenderPresent(m_sdlRenderer);
}
