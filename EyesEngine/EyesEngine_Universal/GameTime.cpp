/////////////////////////////INCLUDE/////////////////////////
#include "GameTime.h"
/////////////////////////////////////////////////////////////

/*
** Class GameTime
*/
GameTime::GameTime()
{}

GameTime::~GameTime()
{}

bool GameTime::GameTime_initialized()
{
	LARGE_INTEGER largeInteger;

	//Verify frequency run normaly
	if (!QueryPerformanceFrequency(&largeInteger))
		return false;

	//Get number of ticks per second
	m_frequencySeconds = (float)(largeInteger.QuadPart);

	//Get current value of the counter
	QueryPerformanceCounter(&largeInteger);
	m_start = largeInteger.QuadPart;

	m_totalGameTime = 0.0f;
	m_elapsedGameTime = 0.0f;

	return true;
}

void GameTime::GameTime_update()
{
	LARGE_INTEGER largeInteger;

	QueryPerformanceCounter(&largeInteger);
	m_elapsedGameTime = (float)(largeInteger.QuadPart - m_start) / m_frequencySeconds;

	m_start = largeInteger.QuadPart;
	m_totalGameTime += m_elapsedGameTime;
}

//Methods
float GameTime::GameTime_getFrequencySeconds() const
{
	return m_frequencySeconds;
}

float GameTime::GameTime_getElapsedGameTime() const
{
	return m_elapsedGameTime;
}

float GameTime::GameTime_getTotalGameTime() const
{
	return m_totalGameTime;
}