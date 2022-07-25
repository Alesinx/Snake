#pragma once

#include <stdint.h>

class Food
{
public:
	void SetPosition(const uint16_t& newX, const uint16_t& newY) { m_gridPositionX = newX; m_gridPositionY = newY; }
	const uint16_t& GetPositionX() { return m_gridPositionX; }
	const uint16_t& GetPositionY() { return m_gridPositionY; }

private:
	uint16_t m_gridPositionX;
	uint16_t m_gridPositionY;
};
