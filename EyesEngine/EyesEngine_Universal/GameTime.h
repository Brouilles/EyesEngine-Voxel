#ifndef GAMETIME_H_INCLUDED
#define GAMETIME_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <Windows.h>

#include <string>
#include <vector>
/////////////////////////////////////////////////////////////

class GameTime
{
public:
	GameTime();
	~GameTime();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initiazed GameTime
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool GameTime_initialized();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update value of member variable: m_elapsedGameTime, m_totalGameTime
	/// </summary>
	/////////////////////////////////////////////////////////////
	void GameTime_update();

	//Methods
	float GameTime_getFrequencySeconds() const;
	float GameTime_getElapsedGameTime() const;
	float GameTime_getTotalGameTime() const;

private:
	LONGLONG m_start;
	float m_frequencySeconds, m_elapsedGameTime, m_totalGameTime;
};

#endif