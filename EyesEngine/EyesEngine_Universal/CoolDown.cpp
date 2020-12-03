/////////////////////////////INCLUDE/////////////////////////
#include "CoolDown.h"
/////////////////////////////////////////////////////////////

/*
** Class CoolDown
*/
CoolDown::CoolDown() : m_timerInstance(0.0f)
{}

CoolDown::~CoolDown()
{}

bool CoolDown::CoolDown_time(float elapsedGameTime, float time)
{
	m_timerInstance -= elapsedGameTime;

	if (m_timerInstance <= -time)
	{
		m_timerInstance = 0.0f;
		return true;
	}
	else
		return false;
}