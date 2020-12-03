#ifndef COOLDOWN_H_INCLUDED
#define COOLDOWN_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <Windows.h>
#include "GameTime.h"
/////////////////////////////////////////////////////////////

class CoolDown
{
public:
	CoolDown();
	~CoolDown();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Calculate time
	/// </summary>
	/// <returns>
	///		return TRUE when the time elapsed, else FALSE
	/// </returns>
	/////////////////////////////////////////////////////////////
	bool CoolDown_time(float elapsedGameTime, float time);

private:
	float m_timerInstance;
};

#endif